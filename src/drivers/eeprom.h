#ifndef _EEPROM_H_
#define _EEPROM_H_
// ------------------------  Include  ---------------------------
#include "types.h"
// ---------------------  Configuraion  -------------------------
//  0. 25AA SPI EEPROM
//  1. 24LC I2C EEPROM
#define EEPROM_TYPE 1
// --------------------------  API  -----------------------------
//   These funcitons are implemented as macros.
// --------------------------------------------------------------
// void     EEPROM_Init(void);
// uint8_t  EEPROM_ReadByte(uint16_t addr);
// void     EEPROM_WriteByte(uint16_t addr, uint8_t dat);

// ---------------------  Funcitions  -------------------------
#if EEPROM_TYPE==0      // EEPROM_TYPE == 0 
#include "25AA.h"
#define EEPROM_Init()   EEPROM_25AA_Init()
#define EEPROM_ReadByte(addr)   EEPROM_25AA_ReadByte(addr)
#define EEPROM_WriteByte(addr,dat) EEPROM_25AA_WriteByte(addr, dat)
#define EEPROM_ReadBlock(addr,dat_ptr,count) \
    EEPROM_25AA_ReadBlock(addr, dat_ptr, count)
#define EEPROM_WriteBlock(addr,dat_ptr,count) \
    EEPROM_25AA_WriteBlock(addr, dat_ptr, count)
#elif EEPROM_TYPE==1    // EEPROM_TYPE == 1
#include "24LC.h"
#define EEPROM_Init()   EEPROM_24LC_Init()
#define EEPROM_ReadByte(addr)   EEPROM_24LC_ReadByte(addr)
#define EEPROM_WriteByte(addr,dat) EEPROM_24LC_WriteByte(addr, dat)
#define EEPROM_ReadBlock(addr,dat_ptr,count) \
    EEPROM_24LC_ReadBlock(addr, dat_ptr, count)
#define EEPROM_WriteBlock(addr,dat_ptr,count) \
    EEPROM_24LC_WriteBlock(addr, dat_ptr, count)
#else
#error "Error: EEPROM_TYPE not defined"
#endif // EEPROM_TYPE

#endif // _EEPROM_H_
