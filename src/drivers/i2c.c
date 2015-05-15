#include "i2c.h"

/**
 *  Method: I2C_WriteByte
 *      Write a byte to I2C bus
 */
void I2C_WriteByte(uint8_t dat)
{
     uint8_t i = 0;
     for (i = 0; i < 8 ; i++) {
        SCL=0; _NOP2_(); SCL=0;    // low level 5us
        if (dat&0x80) {            // send a bit
            SDA=1;
        } else {
            SDA=0; 
        }
        _NOP2_(); SCL=1; _NOP4_(); SCL=1;    // high level 5us
        dat<<=1;
     }
     SCL=0;                        // back to low level 
}

/**
 *  Method: I2C_ReadByte
 *      Read a byte from I2C bus
 */
uint8_t I2C_ReadByte(void)
{
     uint8_t i = 0, dat = 0;
     for (i = 0; i < 8 ; i++) {
        dat<<=1;
        SCL=0; _NOP4_(); SCL=0;    // low level 5us
        SCL=1; _NOP2_();           // high level 5us
        SDA = 1;  // Set an input port
        if (SDA) {
            dat|=0x01;
        } else {
            dat&=0xfe;
        }
        _NOP2_();SCL=0;     
     }
     return dat;   
}

/**
 *  Method: I2C_IsGetAKG
 *      Get an AKG signal from I2C bus
 */ 
bool I2C_IsGetAKG(void)
{
    bool is_get_akg;
    SDA=1;
    SCL=0;
    _NOP4_();
    SCL=1;
    _NOP4_();
    if (SDA)
        is_get_akg=FALSE;
    else
        is_get_akg=TRUE;
    SDA=0;
    return is_get_akg; 
}
