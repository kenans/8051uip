#ifndef _UART_H_
#define _UART_H_

// Include
#include "types.h"
#include "ringbuf.h"
#include "51_conifg.h"
// Configurations
#define UART_TRANSMIT_INTTERRUPT 0
// APIs
// UART_Start()

void UART_SendNChar(const char *str, const uint8_t count);
void UART_SendString(const char *str);
char UART_RecvChar(void);
uint8_t UART_GetCharsRcvd(void);

#ifndef UART_OnSentEvent
#define UART_OnSentEvent()
#endif // UART_OnSentEvent
#ifndef UART_OnRecvEvent
#define UART_OnRecvEvent()
#endif // UART_OnRecvEvent
#ifndef UART_OnErrorEvent
#define UART_OnErrorEvent()
#endif // UART_OnErrorEvent
void UART_OnInterruptEvent(void);

#endif // _UART_H_
