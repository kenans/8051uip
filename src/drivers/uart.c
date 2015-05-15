#include "uart.h"

#define UART_SendChar(chr) \
  do{\
    for(;_transmitting;){}\
    _transmitting=1;\
    UART_SendByte(chr);\
    }while(0)

#define LOCAL_BUFFER_COUNT 16
static char _local_buf[LOCAL_BUFFER_COUNT];     // Local ring buffer
static uint8_t _size = LOCAL_BUFFER_COUNT;   // ring buffer size
static uint8_t _start=0;
static uint8_t _end=0;

static bool _transmitting = 0;
//void UART_Init()
//{
//    UART_SetMode(1);
//    UART_MultiCommunicationDisable();
//    UART_RecvEnable();
//    UART_InterruptEnable();
//    UART_Start(9600);
//}
//void UART_SendChar(const char chr)
//{
//    UART_SendByte(chr);
//    while (!UART_GetTransmitIntFlag()) {
//        // Wait until transmitted
//    }
//    UART_ClearTransmitIntFlag();
//}

/**
 *
 */
void UART_SendNChar(const char *str, const uint8_t count)
{
  uint8_t i = 0;
  for (i=0; i<count ; i++) {
    UART_SendChar(str[i]);
  }
}
void UART_SendString(const char *str)
{
  while (*str != '\0') {
    UART_SendChar(*str);
    str++;
  }
}
char UART_RecvChar(void)
{
  if (!LocalBuf_IsEmpty()) {
    return LocalBuf_Get();
  } else {
    return 0;
  }
}
uint8_t UART_GetCharsRcvd(void) {
  return LocalBuf_NumOfElements();
}
void UART_OnInterruptEvent(void)
{
  if (UART_GetRecvIntFlag()) {
    UART_ClearRecvIntFlag();
    if (!LocalBuf_IsFull()) {
      LocalBuf_Put(SBUF);
      UART_OnRecvEvent();
    } else {
      UART_OnErrorEvent();
    }
  } else if (UART_GetTransmitIntFlag()) {
    UART_ClearTransmitIntFlag();
    _transmitting = 0;
  }
}
