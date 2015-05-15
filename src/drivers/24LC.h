/**
 *  This is a driver for 24LC512 I2C eeprom 
 */
#ifndef _24LC_H_
#define _24LC_H_
// Includes
#include "i2c.h"
#include "types.h"
#include "delay.h"
// Configurations
#define DEVICE_ADDR 0x50U

// APIs
#define EEPROM_24LC_Init() I2C_Init()
uint8_t EEPROM_24LC_ReadByte(uint16_t addr);
void EEPROM_24LC_WriteByte(uint16_t addr, uint8_t dat);

#endif // _24LC_H_
