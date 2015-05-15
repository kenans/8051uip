#include "spi.h"

//  Read a byte from SPI device
uint8_t SPI_ReadByte()
{
#if CPHA==0
    uint8_t dat=0, i=0;
    SCLK = CPOL;    // Clock at idle state
    for (i = 0; i<8; i++) {
        dat<<=1;  
        SCLK = ~SCLK;   // First time toggle, do sampling
        if (MISO)
            dat|=0x01;
        else
            dat&=0xfe;
        SCLK = ~SCLK;   // Second time toggle, device will send the next bit   
    }
    SCLK = CPOL;    // Make sure clock returns to idle state
    return dat;
#elif CPHA==1
    uint8_t dat=0, i=0;
    SCLK = CPOL;    // Clock at idle state
    for (i = 0; i<8; i++) {
        SCLK = ~SCLK;   // First time toggle, device will send the next bit
        dat<<=1;  
        SCLK = ~SCLK;   // Second time toggle, do sampling  
        if (MISO)
            dat|=0x01;
        else
            dat&=0xfe;
    }
    SCLK = CPOL;    // Make sure clock returns to idle state
    return dat;
#else
#error "Error: CPHA should only be 0 or 1."
#endif
}

// Write a byte to SPI device
void SPI_WriteByte(uint8_t dat)
{
#if CPHA==0
    uint8_t i = 0;
    SCLK = CPOL;    // Clock at idle state
    for (i = 0; i<8; i++) {    
        if (dat&0x80)
            MOSI = 1;
        else
            MOSI = 0;
        SCLK = ~SCLK; // First time toggle edge, device will do sampling
        dat<<=1;
        SCLK = ~SCLK; // Second time toggle edge, should then do write
    }
    SCLK = CPOL;    // Make sure clock returns to idle
#elif CPHA==1
    uint8_t i = 0;
    SCLK = CPOL;    // Clock at idle state
    for (i = 0; i<8; i++) {    
        SCLK = ~SCLK; // First time toggle edge, should then do write
        if (dat&0x80)
            MOSI = 1;
        else
            MOSI = 0;
        SCLK = ~SCLK; // Second time toggle edge, device will do sampling
        dat<<=1;
    }
    SCLK = CPOL;    // Make sure clock returns to idle
#else
#error "Error: CPHA should only be 0 or 1."
#endif
}
