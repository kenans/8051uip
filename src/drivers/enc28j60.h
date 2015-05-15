/**
 *  Filename: enc28j60.h
 *      Driver for ENC28J60 Ethernet chip.
 *
 *  kenansun0@gmail.com
 *
 *  Kenan SUN
 *  26/07/2014
 */
#ifndef _ENC28J60_H_
#define _ENC28J60_H_
/**
 *  -----------------------------------------------------------------------
 *                                 Include
 *  -----------------------------------------------------------------------
 */
#include "enc28j60_reg.h"
#include "types.h"
#include "err.h"
/**
 *  -----------------------------------------------------------------------
 *                        Configuration and Port
 *  -----------------------------------------------------------------------
 */
/**
 *  SPI specific functions
 */
#include "spi.h"
#define ENC28_SelectDevice()            SPI_SelectDevice()
#define ENC28_DeselectDevice()          SPI_DeselectDevice()
#define ENC28_SpiReadByte()             SPI_ReadByte()
#define ENC28_SpiWriteByte(dat_byte)    SPI_WriteByte(dat_byte)
/**
 *  MAC address
 */
#if 1
#   define ENC28_MAC_ADDR_5  0x00U
#   define ENC28_MAC_ADDR_4  0x04U
#   define ENC28_MAC_ADDR_3  0xA3U
#   define ENC28_MAC_ADDR_2  0x00U
#   define ENC28_MAC_ADDR_1  0x00U
#   define ENC28_MAC_ADDR_0  0x00U
#else
#   define ENC28_MAC_ADDR_5  0x00U
#   define ENC28_MAC_ADDR_4  0x00U
#   define ENC28_MAC_ADDR_3  0x00U
#   define ENC28_MAC_ADDR_2  0x00U
#   define ENC28_MAC_ADDR_1  0x00U
#   define ENC28_MAC_ADDR_0  0x00U
#endif
/**
 *  Port functions
 */
#include "delay.h"
#define ENC28_Delay10Us()   Delay10Us()
/**
 *  Duplex:
 *      - 1 full duplex;
 *      - 0 half duplex
 */
#define ENC28_FULL_DUPLEX   0

/**
 *  -----------------------------------------------------------------------
 *                           Constant and Types
 *  -----------------------------------------------------------------------
 */
typedef enum {
   ENC28_ControlRegETH,
   ENC28_ControlRegMAC,
   ENC28_ControlRegMII
} ENC28_ControlRegType;
/**
 *  -----------------------------------------------------------------------
 *                              APIs
 *  -----------------------------------------------------------------------
 */
// Initialization
err_t       ENC28_Init(void);
// Reset
#define     ENC28_Reset() do{ENC28_SelectDevice();ENC28_SpiWriteByte(0xffU);ENC28_DeselectDevice();}while(0)
// Ethernet frame
err_t       ENC28_SendFrame(uint8_t *frame, uint16_t count);
uint16_t    ENC28_ReceiveFrame(uint8_t *frame);
// Ethernet connection state
#define     ENC28_IsPhyLinkUp() (((ENC28_MIIReadPhyRegister(ENC28_PHIR))&ENC28_PLNKIF_MASK)?(TRUE):(FALSE))
#define     ENC28_IsMacLinkUp() ((ENC28_ReadControlRegister(ENC28_EIE,ENC28_ControlRegETH))&(ENC28_LINKIF_MASK))
// SPI commands
uint8_t     ENC28_ReadControlRegister(uint8_t addr, ENC28_ControlRegType reg_type);
err_t       ENC28_WriteControlRegister(uint8_t addr, uint8_t dat);
err_t       ENC28_SetBitField(uint8_t addr, uint8_t mask);
err_t       ENC28_ClearBitField(uint8_t addr, uint8_t mask);
uint8_t     ENC28_ReadBufferMemoryByte(void);
err_t       ENC28_ReadBufferMemoryBlock(uint8_t *dat, const uint16_t count);
err_t       ENC28_WriteBufferMemoryByte(uint8_t dat);
err_t       ENC28_WriteBufferMemoryBlock(uint8_t *dat, const uint16_t count);
err_t       ENC28_MIIWritePhyRegister(uint8_t addr, uint16_t val);
uint16_t    ENC28_MIIReadPhyRegister(uint8_t addr);
// Interrupt enable/flag/
#define     ENC28_EnableGlobalInterrupt()  ENC28_SetBitField(ENC28_EIE, ENC28_INTIE_MASK)
#define     ENC28_DisableGlobalInterrupt() ENC28_ClearBitField(ENC28_EIE, ENC28_INTIE_MASK)
// Interrupt events
void        ENC28_OnInterrupt(void);
#endif // _ENC28J60_H_ 
