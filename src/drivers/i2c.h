#ifndef _I2C_H_
#define _I2C_H_
// Includes
#include "51_config.h"
#include "types.h"
// I2C speed configuration
//      Here we stay at a low speed < 100Kbps. So the clock period should be at least
// 10us, so each level at least 5us.
#define I2C_SPEED
// Port configuration
sbit SCL=P1^0;
sbit SDA=P1^1;
// Type defines
typedef enum {
    I2C_WRITE=0,
    I2C_READ
} I2C_OperationType;
// APIs
#define _NOP4_()            do{_nop_();_nop_();_nop_();_nop_();}while(0)    
#define _NOP2_()            do{_nop_();_nop_();}while(0)
#define I2C_Init()          do{SCL=1;SDA=1;}while(0)
#define I2C_Start()         do{SDA=1;SCL=1;SDA=1;_NOP2_();SDA=0;_NOP2_();SCL=0;}while(0)
#define I2C_Restart()       do{SCL=0;_NOP2_();SDA=1;SCL=1;_NOP2_();SDA=0;}while(0)
#define I2C_End()           do{_NOP2_();SCL=0;SDA=0;SCL=1;_NOP2_();SDA=1;}while(0)
#define I2C_SendAKG()       do{SDA=0;SCL=0;_NOP4_();SCL=1;_NOP4_();SCL=0;}while(0)
#define I2C_SendNoAKG()     do{SDA=1;SCL=0;_NOP4_();SCL=1;_NOP4_();SCL=0;}while(0)
#define I2C_WriteDeviceAddr(addr,is_read) \
    I2C_WriteByte(is_read?((addr<<1)|0x01U):((addr<<1)&0xfeU))
bool    I2C_IsGetAKG(void);
void    I2C_WriteByte(uint8_t dat);
uint8_t I2C_ReadByte(void);

#endif // _I2C_H_
