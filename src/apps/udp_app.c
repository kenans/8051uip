#include "udp_app.h"
#include "uip.h"
#include "string.h"
#include "uart.h"

static struct uip_udp_conn *_udp_conn = NULL;
static const u16_t _local_port = 1234;
static const u16_t _remote_port = 1234;
#define LED2_On()  P1_7=1
#define LED2_Off() P1_7=0
#define LED2_Neg() P1_7=~P1_7

void UDP_AppInit(void)
{
//  uip_ipaddr_t ipaddr;
//  // Set remote ip and port
//  uip_ipaddr(&ipaddr, 192,168,95,1);
//  _udp_conn = uip_udp_new(&ipaddr, _remote_port);

  _udp_conn = uip_udp_new(NULL, 0);
  // Set local ip and port
  uip_udp_bind(_udp_conn, _local_port);
}

void UDP_AppCall(void)
{
  char *udp_buf;
  if (_udp_conn==NULL) return;
  if (uip_newdata()) {
    udp_buf = (char*)uip_appdata;
    if (udp_buf != NULL && uip_datalen()>1) {
      if (!strncmp(udp_buf, "On", 2)) {
        LED2_On();
      } else if (!strncmp(udp_buf, "Off", 3)) {
        LED2_Off();
      }
    }
  }
}
