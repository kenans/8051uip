#ifndef _REG51_PDD_H_
#define _REG51_PDD_H_
// --------------------------------------------------
//                  Includes
// --------------------------------------------------
#include "51_config.h"
#include "REG51.H"
// --------------------------------------------------
//                  51 PDD
// --------------------------------------------------
// Interrupt masks
#define INTERRUPT_ENABLE_GLOBAL     0x80U
#define INTERRUPT_ENABLE_UART       0x10U
#define INTERRUPT_ENABLE_TMR1       0x08U
#define INTERRUPT_ENABLE_EXT1       0x04U
#define INTERRUPT_ENABLE_TMR0       0x02U
#define INTERRUPT_ENABLE_EXT0       0x01U
// Globle Interrupt
#define CPU_EnableGlobalInterrupt()         EA=1
#define CPU_DisableGlobalInterrupt()        EA=0
// Ext Int
#define Ext0_EnableInterrupt()           EX0=1
#define Ext0_DisableInterrupt()          EX0=0
#define Ext0_IntHighPriority(high_prio)  (high_prio)?(PX0=1):(PX0=0)
#define Ext0_GetInterruptFlag()          IE0    // Clear automatically
#define Ext0_SetEdgeTrigger(enable_edge) (enable_edge)?(IT0=1):(IT0=0)
#define Ext1_EnableInterrupt()           EX1=1
#define Ext1_DisableInterrupt()          EX1=0
#define Ext1_IntHighPriority(high_prio)  (high_prio)?(PX1=1):(PX1=0)
#define Ext1_GetInterruptFlag()          IE1    // Clear automatically
#define Ext1_SetEdgeTrigger(enable_edge) (enable_edge)?(IT1=1):(IT1=0)        
// System clock
#ifndef OSC_FREQUENCY_HZ
#define OSC_FREQUENCY_HZ                        12000000UL
#endif
#define TIMER_FREQUENCY_HZ	                (OSC_FREQUENCY_HZ/12UL)
// TIMER0
#define Timer0_SetMode(mode)                    Timer0_SetMode_##mode()
#define Timer0_SetMode_0()                      TMOD&=0xfcU
#define Timer0_SetMode_1()                      do{TMOD|=0x01U;TMOD&=0xfdU;}while(0)
#define Timer0_SetMode_2()                      do{TMOD|=0x02U;TMOD&=0xfeU;}while(0)
#define Timer0_SetMode_3()                      TMOD|=0x03U
#define Timer0_SetCounter(is_counter)           (is_counter)?(TMOD|=0x04):(TMOD&=(~0x04))
#define Timer0_SetGate(gate_enable)             (gate_enable)?(TMOD|=0x08):(TMOD&=(~0x08))
#if OSC_FREQUENCY_HZ==12000000
#define Timer0_SetPeriodUs_Mode0(period_us) 	do{TH0=(8191U-period_us+1U)/32U;TL0=(8191U-period_us+1U)%32U;}while(0)
#define Timer0_SetPeriodUs_Mode1(period_us)  	do{TH0=(65535U-period_us+1U)/256U;TL0=(65535U-period_us+1U)%256U;}while(0)
#define Timer0_SetPeriodMs_Mode1(period_ms)  	Timer0_SetPeriodUs_Mode1(period_ms*1000U)
#define Timer0_SetPeriodUs_Mode2(period_us)     do{TH0=255U-period_us+1U;TL0=255U-period_us+1U;}while(0)
#define Timer0_SetPeriodUs_Mode3(period_us)
#elif OSC_FREQUENCY_HZ==11059200
#define Timer0_SetPeriodUs_Mode0(period_us) 	do{TH0=(8191U-period_us*576L/625L+1U)/32U;TL0=(8191U-period_us*576L/625L+1U)%32U;}while(0)
#define Timer0_SetPeriodUs_Mode1(period_us)  	do{TH0=(65535U-period_us*576L/625L+1U)/256U;TL0=(65535U-period_us*576L/625L+1U)%256U;}while(0)
#define Timer0_SetPeriodMs_Mode1(period_ms)  	Timer0_SetPeriodUs_Mode1(period_ms*576L/25L*40UL)
#define Timer0_SetPeriodUs_Mode2(period_us)     do{TH0=255U-period_us*576L/625L+1U;TL0=255U-period_us*576L/625L+1U;}while(0)
#define Timer0_SetPeriodUs_Mode3(period_us)
#endif // if OSC_FREQUENCY_HZ==12000000
#define Timer0_EnableInterrupt()                ET0=1
#define Timer0_DisableInterrupt()               ET0=0
#define Timer0_IntHighPriority(high_prio)       (high_prio)?(PT0=1):(PT0=0)
#define Timer0_GetInterruptFlag()               TF0
#define Timer0_ClearInterruptFlag()             TF0=0
#define Timer0_Start()                          TR0=1
#define Timer0_Stop()                           TR0=0
// TIMER1
#define Timer1_SetMode(mode)                    Timer1_SetMode_##mode()
#define Timer1_SetMode_0()                      TMOD&=0xcfU
#define Timer1_SetMode_1()                      do{TMOD|=0x10U;TMOD&=0xdfU;}while(0)
#define Timer1_SetMode_2()                      do{TMOD|=0x20U;TMOD&=0xefU;}while(0)
#define Timer1_SetMode_3()                      TMOD|=0x30U
#define Timer1_SetCounter(is_counter)           (is_counter)?(TMOD|=0x40):(TMOD&=(~0x40))
#define Timer1_SetGate(gate_enable)             (gate_enable)?(TMOD|=0x80):(TMOD&=(~0x80))
#if OSC_FREQUENCY_HZ==12000000
#define Timer1_SetPeriodUs_Mode0(period_us) 	do{TH1=(8191U-period_us+1U)/32;TL1=(8191U-period_us+1U)%32U;}while(0)
#define Timer1_SetPeriodUs_Mode1(period_us)  	do{TH1=(65535U-period_us+1U)/256U;TL1=(65535U-period_us+1U)%256U;}while(0)
#define Timer1_SetPeriodMs_Mode1(period_ms)  	Timer1_SetPeriodUs_Mode1(period_ms*1000U)
#define Timer1_SetPeriodUs_Mode2(period_us)     do{TH1=255U-period_u+1U;TL1=255U-period_us+1U;}while(0)
#endif // if OSC_FREQUENCY_HZ==12000000
#define Timer1_EnableInterrupt()                ET1=1
#define Timer1_DisableInterrupt()               ET1=0
#define Timer1_IntHighPriority(high_prio)       (high_prio)?(PT1=1):(PT1=0)
#define Timer1_GetInterruptFlag()               TF1
#define Timer1_ClearInterruptFlag()             TF1=0
#define Timer1_Start()                          TR1=1
#define Timer1_Stop()                           TR1=0
// UART
#define UART_SetMode(mode)                      do{SM0=mode/2;SM1=mode%2;}while(0)
#define UART_MultiCommunicationEnable()         SM2=1
#define UART_MultiCommunicationDisable()        SM2=0
#define UART_RecvEnable()                       REN=1
#define UART_RecvDisable()                      REN=0
#define UART_GetTransmitBit8()                  TB8
#define UART_GetRecvBit8()                      RB8
#define UART_EnableInterrupt()                  ES=1
#define UART_DisableInterrupt()                 ES=0
#define UART_IntHighPriority(high_prio)         (high_prio)?(PS=1):(PS=0)
#define UART_GetTransmitIntFlag()               TI
#define UART_GetRecvIntFlag()                   RI
#define UART_ClearTransmitIntFlag()             TI=0
#define UART_ClearRecvIntFlag()                 RI=0
#define UART_DoubleBaudrate(double_baudrate)    (double_baudrate)?(PCON|=0x80):(PCON&=(~0x80))               
#define UART_SetBaudrate(baudrate)              UART_SetBaudrate_##baudrate()
#define UART_SetBaudrate_9600()                 do{TH1=0xfdU;TL1=0xfdU;}while(0)
#define UART_SetBaudrate_4800()                 do{TH1=0xfaU;TL1=0xfaU;}while(0)
#define UART_SetBaudrate_2400()                 do{TH1=0xf4U;TL1=0xf4U;}while(0)
#define UART_SetBaudrate_1200()                 do{TH1=0xe8U;TL1=0xe8U;}while(0)
#define UART_Start(baudrate)                    do{Timer1_SetMode(2);UART_SetBaudrate(baudrate);TR1=1;}while(0)
#define UART_Stop()                             TR1=0
#define UART_GetByte()                          SBUF
#define UART_SendByte(byte)                     SBUF=byte                      
// Low power
#define CPU_EnterIdleMode()                     PCON|=0x01
#define CPU_EnterPowerDownMode()                PCON|=0x02

#endif // _REG51_PDD_H_
