#include "24LC.h"

void EEPROM_24LC_WriteByte(uint16_t addr, uint8_t dat)
{
    // Start
    I2C_Start();
    // Write device addr + Write + Read AKG
    I2C_WriteDeviceAddr(DEVICE_ADDR, 0);    // 0 for write (Out)
    if (!I2C_IsGetAKG()) return;
    // Write 16-bit addr + Read AKG
    I2C_WriteByte((uint8_t)(addr>>8));      // 8 bits high
    if (!I2C_IsGetAKG()) return;
    I2C_WriteByte((uint8_t)(addr));         // 8 bits low
    if (!I2C_IsGetAKG()) return;
    // Write data + Read AKG
    I2C_WriteByte(dat);
    if (!I2C_IsGetAKG()) return;
    // End
    I2C_End();
    // Delay 5ms to get the write done
    DelayMs(5);
}

uint8_t EEPROM_24LC_ReadByte(uint16_t addr)
{
    uint8_t dat;
    // Start
    I2C_Start();
    // Write device addr + Write + Read AKG
    I2C_WriteDeviceAddr(DEVICE_ADDR, 0);    // 0 for write (Out)
    if (!I2C_IsGetAKG()) return 0;
     // Write 16-bit addr + Read AKG
    I2C_WriteByte((uint8_t)(addr>>8));      // 8 bits high
    if (!I2C_IsGetAKG()) return 0;
    I2C_WriteByte((uint8_t)(addr));         // 8 bits low
    if (!I2C_IsGetAKG()) return 0;
    // Start
    I2C_End();I2C_Start();
    // Write device addr + Read + Read AKG
    I2C_WriteDeviceAddr(DEVICE_ADDR, 1);    // 1 for read (In)
    if (!I2C_IsGetAKG()) return 0;
    // Read data + Write Non-AKG
    dat = I2C_ReadByte();
    I2C_SendNoAKG();
    // End
    I2C_End();
    // Return
    return dat;
}
