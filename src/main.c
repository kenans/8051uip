//
#include "51_config.h"
#include "types.h"
#include "delay.h"
#include "err.h"
#include "eeprom.h"
#include "uart.h"
#include "ethernet.h"
// uip includes
#include "uip.h"
#include "uip_arp.h"
#include "tapdev.h"
#include "timer.h"

#define BUF ((struct uip_eth_hdr *)&uip_buf[0])

void main(void)
{
  // Variables
  // uip
  int i;
  uip_ipaddr_t ipaddr;
  struct timer periodic_timer, arp_timer;
  // shell
  struct timer shell_timer;
  RingBufDeclare(shell_buf, char, uint8_t, 16);
  RingBufInit(&shell_buf);
  /**
   *  CPU Initialization
   */
  // AUXR |= 0x02;   // Only use external ram
  UART_Start(19200);
  EA = 1; // Enable global interrupt
  clock_init();// Timer0 initialization
  UART_SendString("Program begins:\r\n");
  /**
   *  Ethernet Initialization
   */
  timer_set(&periodic_timer, CLOCK_SECOND/2);
  timer_set(&arp_timer, CLOCK_SECOND*10);
  timer_set(&shell_timer, CLOCK_SECOND/50);

  tapdev_init();
  while (!Eth_IsLinkUp()) {
    // Wait for Ethernet link up
    DelayMs(200);
  }
  uip_init();

  uip_ipaddr(ipaddr, 192,168,95,2);
  uip_sethostaddr(ipaddr);
  uip_ipaddr(ipaddr, 192,168,95,1);
  uip_setdraddr(ipaddr);
  uip_ipaddr(ipaddr, 255,255,255,0);
  uip_setnetmask(ipaddr);
  UART_SendString("IP: 192.168.95.2\r\n");
  UART_SendString(">>");

  // App init
  WebServer_Init();
  UDP_AppInit();

  // Main loop
  while (1) {
    uip_len = tapdev_read();
    if(uip_len > 0) {
      if(BUF->type == htons(UIP_ETHTYPE_IP)) {
        uip_arp_ipin();
        uip_input();
        /* If the above function invocation resulted in data that
           should be sent out on the network, the global variable
           uip_len is set to a value > 0. */
        if(uip_len > 0) {
          uip_arp_out();
          tapdev_send();
        }
      } else if(BUF->type == htons(UIP_ETHTYPE_ARP)) {
        uip_arp_arpin();
        /* If the above function invocation resulted in data that
           should be sent out on the network, the global variable
           uip_len is set to a value > 0. */
        if(uip_len > 0) {
          tapdev_send();
        }
      }

    } else if(timer_expired(&periodic_timer)) {
      timer_reset(&periodic_timer);
      for(i = 0; i < UIP_CONNS; i++) {
        uip_periodic(i);
        /* If the above function invocation resulted in data that
           should be sent out on the network, the global variable
           uip_len is set to a value > 0. */
        if(uip_len > 0) {
          uip_arp_out();
          tapdev_send();
        }
      }

#if UIP_UDP
      for(i = 0; i < UIP_UDP_CONNS; i++) {
        uip_udp_periodic(i);
        /* If the above function invocation resulted in data that
           should be sent out on the network, the global variable
           uip_len is set to a value > 0. */
        if(uip_len > 0) {
          uip_arp_out();
          tapdev_send();
        }
      }
#endif /* UIP_UDP */

      /* Call the ARP timer function every 10 seconds. */
      if(timer_expired(&arp_timer)) {
        timer_reset(&arp_timer);
        uip_arp_timer();
      }
    }
    /**
     *  Shell app
     */
    if (timer_expired(&shell_timer)) {
      while (UART_GetCharsRcvd() != 0 && !RingBufIsFull(&shell_buf)) {
        RingBufPut(&shell_buf, UART_RecvChar());
      }
      if (RingBufNumOfElements(&shell_buf)>0) {
        if (RingBufPeek(&shell_buf)=='\r') {
          (void)RingBufGet(&shell_buf);
          UART_SendString(">>");
        }
        while (RingBufNumOfElements(&shell_buf)>=6) {
          if (RingBufPeekIndex(&shell_buf, 0)!='-' ||
              RingBufPeekIndex(&shell_buf, 1)!='h' ||
              RingBufPeekIndex(&shell_buf, 2)!='e' ||
              RingBufPeekIndex(&shell_buf, 3)!='l' ||
              RingBufPeekIndex(&shell_buf, 4)!='p' ||
              RingBufPeekIndex(&shell_buf, 5)!='\r') {
            (void)RingBufGet(&shell_buf);
          } else {
            UART_SendString("This is a shell test\r\n");
            UART_SendString(">>");
            RingBufClear(&shell_buf);
          }
        }
      }
    }
  }
}
/**
 *  Timer0 interrupt routine
 *      - Period = 1ms
 */
void Timer0_Interrupt(void) interrupt 1
{
  extern clock_time_t data tick_count;
  // Reload Timer0 value
  clock_reload();
  // Increment tick
  tick_count++;
}

void UART_Interrupt() interrupt 4
{
  UART_OnInterruptEvent();
}
