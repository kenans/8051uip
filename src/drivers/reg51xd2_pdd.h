#ifndef _REG51_PDD_H_
#define _REG51_PDD_H_
// --------------------------------------------------
//                  Includes
// --------------------------------------------------
#include "51_config.h"
#include "REG51xD2.h"
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
#define Ext0_GetInterruptFlag()          IE0
#define Ext0_SetEdgeTrigger(enable_edge) (enable_edge)?(IT0=1):(IT0=0)
#define Ext1_EnableInterrupt()           EX1=1
#define Ext1_DisableInterrupt()          EX1=0
#define Ext1_IntHighPriority(high_prio)  (high_prio)?(PX1=1):(PX1=0)
#define Ext1_GetInterruptFlag()          IE1
#define Ext1_SetEdgeTrigger(enable_edge) (enable_edge)?(IT1=1):(IT1=0)
// System clock
#ifndef OSC_FREQUENCY_HZ
#define OSC_FREQUENCY_HZ                        12000000
#endif
#define TIMER_FREQUENCY_HZ                  (OSC_FREQUENCY_HZ/12UL)
// TIMER0
#define Timer0_SetMode(mode)                    Timer0_SetMode_##mode()
#define Timer0_SetMode_0()                      TMOD&=0xfcU
#define Timer0_SetMode_1()                      do{TMOD|=0x01U;TMOD&=0xfdU;}while(0)
#define Timer0_SetMode_2()                      do{TMOD|=0x02U;TMOD&=0xfeU;}while(0)
#define Timer0_SetMode_3()                      TMOD|=0x03U
#define Timer0_SetCounter(is_counter)           (is_counter)?(TMOD|=0x04):(TMOD&=(~0x04))
#define Timer0_SetGate(gate_enable)             (gate_enable)?(TMOD|=0x08):(TMOD&=(~0x08))
#if OSC_FREQUENCY_HZ==12000000
#define Timer0_SetPeriodUs_Mode0(period_us)     do{TH0=(8191U-period_us+1U)/32U;TL0=(8191U-period_us+1U)%32U;}while(0)
#define Timer0_SetPeriodUs_Mode1(period_us)     do{TH0=(65535U-period_us+1U)/256U;TL0=(65535U-period_us+1U)%256U;}while(0)
#define Timer0_SetPeriodMs_Mode1(period_ms)     Timer0_SetPeriodUs_Mode1(period_ms*1000U)
#define Timer0_SetPeriodUs_Mode2(period_us)     do{TH0=255U-period_us+1U;TL0=255U-period_us+1U;}while(0)
#define Timer0_SetPeriodUs_Mode3(period_us)
#elif OSC_FREQUENCY_HZ==11059200
#define Timer0_SetPeriodUs_Mode0(period_us)     do{TH0=(8191U-period_us*576L/625L+1U)/32U;TL0=(8191U-period_us*576L/625L+1U)%32U;}while(0)
#define Timer0_SetPeriodUs_Mode1(period_us)     do{TH0=(65535U-period_us*576L/625L+1U)/256U;TL0=(65535U-period_us*576L/625L+1U)%256U;}while(0)
#define Timer0_SetPeriodMs_Mode1(period_ms)     Timer0_SetPeriodUs_Mode1(period_ms*576L/25L*40UL)
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
#define Timer1_SetPeriodUs_Mode0(period_us)     do{TH1=(8191U-period_us+1U)/32;TL1=(8191U-period_us+1U)%32U;}while(0)
#define Timer1_SetPeriodUs_Mode1(period_us)     do{TH1=(65535U-period_us+1U)/256U;TL1=(65535U-period_us+1U)%256U;}while(0)
#define Timer1_SetPeriodMs_Mode1(period_ms)     Timer1_SetPeriodUs_Mode1(period_ms*1000U)
#define Timer1_SetPeriodUs_Mode2(period_us)     do{TH1=255U-period_u+1U;TL1=255U-period_us+1U;}while(0)
#elif OSC_FREQUENCY_HZ==11059200
#define Timer1_SetPeriodUs_Mode0(period_us)     do{TH0=(8191U-period_us*576L/625L+1U)/32U;TL0=(8191U-period_us*576L/625L+1U)%32U;}while(0)
#define Timer1_SetPeriodUs_Mode1(period_us)     do{TH0=(65535U-period_us*576L/625L+1U)/256U;TL0=(65535U-period_us*576L/625L+1U)%256U;}while(0)
#define Timer1_SetPeriodMs_Mode1(period_ms)     Timer0_SetPeriodUs_Mode1(period_ms*576L/25L*40UL)
#define Timer1_SetPeriodUs_Mode2(period_us)     do{TH0=255U-period_us*576L/625L+1U;TL0=255U-period_us*576L/625L+1U;}while(0)
#endif // if OSC_FREQUENCY_HZ==12000000
#define Timer1_EnableInterrupt()                ET1=1
#define Timer1_DisableInterrupt()               ET1=0
#define Timer1_IntHighPriority(high_prio)       (high_prio)?(PT1=1):(PT1=0)
#define Timer1_GetInterruptFlag()               TF1
#define Timer1_ClearInterruptFlag()             TF1=0
#define Timer1_Start()                          TR1=1
#define Timer1_Stop()                           TR1=0
// Timer2

// UART
#if OSC_FREQUENCY_HZ==11059200
#if 0 // Not pass test
#define UART_MultiCommunicationEnable()         SM2=1
#define UART_MultiCommunicationDisable()        SM2=0
#define UART_GetTransmitBit8()                  TB8
#define UART_GetRecvBit8()                      RB8
#define UART_DoubleBaudrate(double_baudrate)    (double_baudrate)?(PCON|=0x80):(PCON&=(~0x80))

#define UART_SetMode(mode)                      do{SM0=mode/2;SM1=mode%2;}while(0)
#define UART_RecvEnable()                       REN=1
#define UART_RecvDisable()                      REN=0

#define UART_EnableInterrupt()                  ES=1
#define UART_DisableInterrupt()                 ES=0
#define UART_IntHighPriority(high_prio)         (high_prio)?(PS=1):(PS=0)
#define UART_GetTransmitIntFlag()               TI
#define UART_GetRecvIntFlag()                   RI
#define UART_ClearTransmitIntFlag()             TI=0
#define UART_ClearRecvIntFlag()                 RI=0

#define UART_SetBaudrate(baudrate)              UART_SetBaudrate_##baudrate()
#define UART_SetBaudrate_115200()               do{BDRCON|=0x02u;PCON&=0x7fu;RL=0xfdU;}while(0)
#define UART_SetBaudrate_57600()                do{BDRCON|=0x02u;PCON&=0x7fu;RL=0xfaU;}while(0)
#define UART_SetBaudrate_38400()                do{BDRCON|=0x02u;PCON&=0x7fu;RL=0xf7U;}while(0)
#define UART_SetBaudrate_19200()                do{PCON|=0x80u;BRL=0xfaU;}while(0)
#define UART_SetBaudrate_9600()                 do{BRL=0xfaU;}while(0)
#define UART_SetBaudrate_4800()                 do{BRL=0xf4U;}while(0)
#define UART_SetBaudrate_2400()                 do{BRL=0xe8U;}while(0)
#define UART_SetBaudrate_1200()                 do{BRL=0xd0U;}while(0)

#define UART_Start(baudrate)                    do{PCON&=0x3fu;SCON=0x50;BDRCON=0xECu;UART_SetBaudrate(baudrate);BDRCON|=0x10u;}while(0)
#define UART_Stop()                             BDRCON&=0xEFu
#define UART_GetByte()                          SBUF
#define UART_SendByte(byte)                     SBUF=byte
#else
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
#define UART_SetBaudrate_19200()                do{PCON|=0x80;TH1=0xfdU;TL1=0xfdU;}while(0)
#define UART_SetBaudrate_9600()                 do{TH1=0xfdU;TL1=0xfdU;}while(0)
#define UART_SetBaudrate_4800()                 do{TH1=0xfaU;TL1=0xfaU;}while(0)
#define UART_SetBaudrate_2400()                 do{TH1=0xf4U;TL1=0xf4U;}while(0)
#define UART_SetBaudrate_1200()                 do{TH1=0xe8U;TL1=0xe8U;}while(0)
#define UART_Start(baudrate)                    do{UART_SetMode(1);TI=0;RI=0;ES=1;Timer1_SetMode(2);UART_SetBaudrate(baudrate);REN=1;TR1=1;}while(0)
#define UART_Stop()                             TR1=0
#define UART_GetByte()                          SBUF
#define UART_SendByte(byte)                     SBUF=byte
#endif // #if 0
#endif
// SPI , not pass test
#if 0
// SPCON
#define SPCON_SFR           0xC3u
#define SPCON_SPR2_MASK     0x80u
#define SPCON_SPEN_MASK     0x40u
#define SPCON_SSDIS_MASK    0x20u
#define SPCON_MSTR_MASK     0x10u
#define SPCON_CPOL_MASK     0x08u
#define SPCON_CPHA_MASK     0x04u
#define SPCON_SPR1_MASK     0x02u
#define SPOCN_SPR0_MASK     0x01u
// SPSTA
#define SPSTA_SFR           0xC4u
#define SPSTA_SPIF_MASK     0x80u
#define SPSTA_WCOL_MASK     0x40u
#define SPSTA_SSERR_MASK    0x20u
#define SPSTA_MODF_MASK     0x10u
// SPDAT
#define SPDAT_SFR           0xC5u
// Initialization
#define SPI_Init(master,cpol,spha) SPI_Init##_master##_cpol##_cpha()
// Start/Stop
#define SPI_Start(master,cpol,spha)   do{SPI_Init(master,cpol,spha);SPCON|=0x40u;}while(0)
#define SPI_Stop()                    SPCON&=0xBFu;
// R/W
#define SPI_WriteBuf(dat)  SPDAT=dat   
#define SPI_ReadBuf()      SPDAT
// Speed (Fclk/2~Fclk/16)
#define SPI_Speed(level)   SPI_Speed##_level() 
// Interrupt
#define SPI_EnableInterrupt()       IEN1|=0x04u
#define SPI_DisableInterrupt()      IEN1&=0xFBu
// Specifications 
#define SPI_Init_0_0_0()    do{SPCON&=0xe3u;}while(0)
#define SPI_Init_0_0_1()    do{SPCON&=0xe7u;SPCON|=0x04u;}while(0)
#define SPI_Init_0_1_0()    do{SPCON&=0xeBu;SPCON|=0x08u;}while(0)
#define SPI_Init_0_1_1()    do{SPCON&=0xefu;SPCON|=0x0Cu;}while(0)
#define SPI_Init_1_0_0()    do{SPCON|=0x10u;SPCON&=0xf3u;}while(0)
#define SPI_Init_1_0_1()    do{SPCON&=0xf7u;SPCON|=0x14u;}while(0)
#define SPI_Init_1_1_0()    do{SPCON&=0xfbu;SPCON|=0x18u;}while(0)
#define SPI_Init_1_1_1()    do{SPCON|=0x1cu;}while(0)
#define SPI_Speed_0()       SPCON&=0xFCu;   // Default: Fclk/2
#define SPI_Speed_1()       do{SPCON&=0xFDu;SPCON|=0x01u;}while(0)
#define SPI_Speed_2()       do{SPCON|=0x02u;SPCON&=0xFEu;}while(0)
#define SPI_Speed_3()       do{SPCON|=0x03u;}while(0)
#endif  
// Intenal XRAM  Default : AUXR=0x08 (enable internal XRAM=768 Bytes)
#define XRAM_Enable()
#define XRAM_Disable()
#define XRAM_SetSize()
// EEPROM

// Low power
#define CPU_EnterIdleMode()                     PCON|=0x01
#define CPU_EnterPowerDownMode()                PCON|=0x02

#endif // _REG51_PDD_H_

