#include "web_server.h"
#include "uip.h"
#include "uart.h"
#include "string.h"

#define WEB_200_OK  "HTTP 1.1/200 OK\r\nContent-Type: text/html\r\n\r\n"
#define WEB_START   "<html><head></head><body>"
#define WEB_END     "</body></html>"
#define WEB_BODY_LED_ON "<h1>LED Control</h1><p><font color=\"green\">Led is ON</font></p><a href=\"/?led=on\">On</a><br><a href=\"/?led=off\">Off</a>"
#define WEB_BODY_LED_OFF "<h1>LED Control</h1><p><font color=\"red\">Led is OFF</font></p><a href=\"/?led=on\">On</a><br><a href=\"/?led=off\">Off</a>"
#define WEB_BODY_404   "<h1>Error<br />404-Page not found</h1>"
#define WEB_PAGE_LED_ON  WEB_START WEB_BODY_LED_ON WEB_END
#define WEB_PAGE_LED_OFF WEB_START WEB_BODY_LED_OFF WEB_END
#define WEB_404     WEB_START WEB_BODY_404 WEB_END
#define WEB_REPLY_LED_ON WEB_200_OK WEB_PAGE_LED_ON
#define WEB_REPLY_LED_OFF WEB_200_OK WEB_PAGE_LED_OFF
#define WEB_REPLY_404   WEB_200_OK WEB_404

/**
 *  Static
 */
//static void WebServer_Handle(const char *, uint16_t len);
#if WEB_SERVER_USE_EEPROM==1
#include "eeprom.h"
static void WebServer_LoadPage(void);
static char _web_buf[256];
#endif // WEB_SERVER_USE_EEPROM==1

#define LED1_On()  P1_6=1
#define LED1_Off() P1_6=0
#define LED1_Neg() P1_6=~P1_6
#define LED1_IsOn() P1_6

/**
 *  WebServer_Appcall
 *    - The application interface of uip
 */
void WebServer_Appcall(void)
{
  char *buf_ptr = NULL;
  if(uip_closed() || uip_aborted()) {
    // Nothing to do here..
  } else if (uip_timedout()) {
    // If got a timeout, we will close the connection
    uip_close();
  } else if (uip_newdata()||uip_connected()) {
    // If we got a new connection or data
    /*
    if (uip_acked()) {
      // We have received an AKG from the client
    }
    if (uip_poll()) {
      // If uip_poll_conn() has been called
    }*/
    if (uip_datalen() > 0) {
      // To make sure we have got tcp data
      buf_ptr = (char*)uip_appdata;
      if (buf_ptr != NULL) {
        if (!strncmp("GET ", buf_ptr, 4)) {
          if (!strncmp("/ ", &buf_ptr[4], 2)) {
#if WEB_SERVER_USE_EEPROM==1
            strcpy(_web_buf, WEB_200_OK);
            WebServer_LoadPage();
            uip_send((void*)_web_buf, strlen(_web_buf));
#else // WEB_SERVER_USE_EEPROM==1
            // Send page according to the LED state
            if (LED1_IsOn())
              uip_send((void*)WEB_REPLY_LED_ON, strlen(WEB_REPLY_LED_ON));
            else
              uip_send((void*)WEB_REPLY_LED_OFF, strlen(WEB_REPLY_LED_OFF));
#endif // WEB_SRVER_USE_EEPROM==1
          } else if (!strncmp("/favicon", &buf_ptr[4], 8)) {
            // Do nothing
            uip_close();
          } else if (!strncmp("/?led=on ", &buf_ptr[4], 9)) {
#if WEB_SERVER_USE_EEPROM==1
            strcpy(_web_buf, WEB_200_OK);
            WebServer_LoadPage();
            uip_send((void*)_web_buf, strlen(_web_buf));
#else // WEB_SERVER_USE_EEPROM==1
            uip_send((void*)WEB_REPLY_LED_ON, strlen(WEB_REPLY_LED_ON));
#endif // WEB_SRVER_USE_EEPROM==1
            LED1_On();
            UART_SendNChar("LED is ON\r\n", 11);
          } else if (!strncmp("/?led=off ", &buf_ptr[4], 10)) {
#if WEB_SERVER_USE_EEPROM==1
            strcpy(_web_buf, WEB_200_OK);
            WebServer_LoadPage();
            uip_send((void*)_web_buf, strlen(_web_buf));
#else // WEB_SERVER_USE_EEPROM==1
            uip_send((void*)WEB_REPLY_LED_OFF, strlen(WEB_REPLY_LED_OFF));
#endif // WEB_SRVER_USE_EEPROM==1
            LED1_Off();
            UART_SendString("LED is OFF\r\n");
          } else {
            uip_send((void*)WEB_REPLY_404, strlen(WEB_REPLY_404));
          }
        }
      }
    }
  } else {
    // Do nothing
    uip_close();
  }
}

/**
 *  WebServer_Handle()
 *    - Parse the type of request (GET/POST) and the url.
 *    - This method is to avoid the invocation of functions of std lib (like sprint())
 */
//static void WebServer_Handle(const char *web_buf, uint16_t len)
//{
//  uint16_t i = 0;
//  for (i = 0; i < len; i++) {
//  }
//}

#if WEB_SERVER_USE_EEPROM==1
static void WebServer_LoadPage(void)
{
  uint8_t i = 0;
  uint8_t len = strlen(_web_buf);
  for (i=0; i<0x7cu; i++) {
    _web_buf[i+len] = EEPROM_ReadByte(i);
  }
  _web_buf[i+len] = '\0';
}
#endif // WEB_SERVER_USE_EEPROM==1
