/**
 *  Filename: enc28j60.c
 *      Driver for ENC28J60 Ethernet chip.
 *
 *  kenansun0@gmail.com
 *
 *  Kenan SUN
 *  26/07/2014
 */
#include "enc28j60.h"
/**
 *  -----------------------------------------------------------------------
 *                                 Static
 *  -----------------------------------------------------------------------
 */
/**
 *  Register bank selection
 */
#define ENC28_SelectBank(bank_num) _SelectBank_##bank_num()
#define _SelectBank_0() ENC28_ClearBitField(ENC28_ECON1, ENC28_BSEL1_MASK|ENC28_BSEL0_MASK) // ECON1(1FH).1 .0 = 00
#define _SelectBank_1() do{ENC28_ClearBitField(ENC28_ECON1, ENC28_BSEL1_MASK);\
    ENC28_SetBitField(ENC28_ECON1, ENC28_BSEL0_MASK);}while(0) // 01
#define _SelectBank_2() do{ENC28_ClearBitField(ENC28_ECON1, ENC28_BSEL0_MASK);\
    ENC28_SetBitField(ENC28_ECON1, ENC28_BSEL1_MASK);}while(0) // 10
#define _SelectBank_3() ENC28_SetBitField(ENC28_ECON1, ENC28_BSEL1_MASK|ENC28_BSEL0_MASK)   // ECON1(1FH).1 .0 = 11
/**
 *  Event functions
 */
void    ENC28_OnFrameTransmitted(void);
void    ENC28_OnFrameReceived(void);
void    ENC28_OnRxError(void);
void    ENC28_OnTxError(void);
/**
 *  -----------------------------------------------------------------------
 *                                  APIs
 *  -----------------------------------------------------------------------
 */
/**
 *  -----------------------------------------------------------------------
 *                              Initialization
 *  -----------------------------------------------------------------------
 */
/**
 *  Method: ENC28_Init()
 *      This method does initialization for enc28j60.
 */
err_t ENC28_Init(void)
{
  /**
   *  -------------------------------------------------------------------
   *                         System Reset
   *  -------------------------------------------------------------------
   */
  ENC28_Reset();
  /**
   *  -------------------------------------------------------------------
   *                          Wait for OST
   *  -------------------------------------------------------------------
   */
  // ESTAT.CLKRDY==1? (300us, can do SPI read/write ETH register and ETH buffers; cannot send/recv frames)
  while (!(ENC28_ReadControlRegister(ENC28_ESTAT, ENC28_ControlRegETH) | ENC28_CLKRDY_MASK)) {
    // Wait for clock ready
  }
  /**
   *  -------------------------------------------------------------------
   *                   Receive Buffer Initialization
   *  -------------------------------------------------------------------
   */
  //  - ERXST, ERXND  -> default value (5faH = 1530)
  //  - ERXRDPT -> default 5FAH
  //  - ERXWRPT -> default 000H, should set to ERXST
  ENC28_SelectBank(0);
  ENC28_WriteControlRegister(ENC28_ERXWRPTL, 0xFAu);
  ENC28_WriteControlRegister(ENC28_ERXWRPTH, 0x05u);
  //  - Enable reception now?
  /**
   *  -------------------------------------------------------------------
   *                  Transmit Buffer Initialization
   *  -------------------------------------------------------------------
   */
  // - Nothing
  /**
   *  -------------------------------------------------------------------
   *                  Receive Filter Initialization
   *  -------------------------------------------------------------------
   */
  //  - ERXFCON -> default A1H
  ENC28_SelectBank(1);
  ENC28_WriteControlRegister(ENC28_ERXFCON, 0xA1u);
  /**
   *  -------------------------------------------------------------------
   *                   Interrupt Initialization
   *  -------------------------------------------------------------------
   */
  //    ENC28_WriteControlRegister(ENC28_EIE, ENC28_LINKIE_MASK|ENC28_INTIE_MASK);
  /**
   *  -------------------------------------------------------------------
   *                   ECON1/ECON2 Initialization
   *  -------------------------------------------------------------------
   */
  ENC28_WriteControlRegister(ENC28_ECON1, 0x00u);
  /**
   *  -------------------------------------------------------------------
   *                       MAC Initialization
   *  -------------------------------------------------------------------
   */
  //  - MACON2.MARST = 0 -> Exit MAC Reset state
  ENC28_SelectBank(2);
  //    ENC28_WriteControlRegister(ENC28_MACON2, 0x00u);
  /**
   *  Not compatible with Proteus, problem historic?
   *
   *  ENC28_ClearBitField(ENC28_MACON2, ENC28_MARST_MASK);
   */
  //  - MACON1.MARXEN = 1
  //  - If Duplex -> TXPAUS/RXPAUS=1 (Enable flow control)
  //  - MACON3.PADCFG/TXCRCEN/FULDPX
#if ENC28_FULL_DUPLEX==1
  // Full duplex should do flow control
  ENC28_SetBitField(ENC28_MACON1,
      ENC28_TXPAUS_MASK|ENC28_RXPAUS_MASK|ENC28_MARXEN_MASK); // 0b00001101
  ENC28_WriteControlRegister(ENC28_MACON3, 0xf3u); // 0b11110011
  //  - MABBIPG: FullDuplex(15h) HalfDuplex(12h)
  ENC28_WriteControlRegister(ENC28_MABBIPG, 0x15u);
  //  - MAIPGL (12h)
  ENC28_WriteControlRegister(ENC28_MAIPGL, 0x12u);
#else
  ENC28_SetBitField(ENC28_MACON1, ENC28_MARXEN_MASK); // 0b00000001
  ENC28_WriteControlRegister(ENC28_MACON3, 0xf2u); // 0b11110010
  //  - MABBIPG: FullDuplex(15h) HalfDuplex(12h)
  ENC28_WriteControlRegister(ENC28_MABBIPG, 0x12u);
  //  - MAIPGL (12h)
  ENC28_WriteControlRegister(ENC28_MAIPGL, 0x12u);
  //  - If HalfDuplex: MAIPGH(0ch) MACLCON1/2(default)
  ENC28_WriteControlRegister(ENC28_MAIPGH, 0x0Cu);
#endif
  //  - MACON4, keep default values
  //  - MAMXFL  -> length<=1518bytes (default value 1536Bytes)
  ENC28_WriteControlRegister(ENC28_MAMXFLH, 0x05u);  // 0b00000101
  ENC28_WriteControlRegister(ENC28_MAMXFLL, 0xeeu);  // 0b11101110
  //  - MAADR0:MAADR5 -> Mac address
  //  MAC Address = MAADR5.MAADR4.MAADR3.MAADR2.MAADR2.MAADR1.MAADR0
  ENC28_SelectBank(3);
  ENC28_WriteControlRegister(ENC28_MAADR5, ENC28_MAC_ADDR_5);
  ENC28_WriteControlRegister(ENC28_MAADR4, ENC28_MAC_ADDR_4);
  ENC28_WriteControlRegister(ENC28_MAADR3, ENC28_MAC_ADDR_3);
  ENC28_WriteControlRegister(ENC28_MAADR2, ENC28_MAC_ADDR_2);
  ENC28_WriteControlRegister(ENC28_MAADR1, ENC28_MAC_ADDR_1);
  ENC28_WriteControlRegister(ENC28_MAADR0, ENC28_MAC_ADDR_0);
  /**
   *  -------------------------------------------------------------------
   *                       PHY Initialization
   *  -------------------------------------------------------------------
   */
  //  - PHCON1.PDPXMD (LED config)-> should match MACON3.FULDPX
  //  - If HalfDuplex: PHCON2.HDLDIS=1,
  //  - PHLCON: Configuration LED
#if ENC28_FULL_DUPLEX==1
  ENC28_MIIWritePhyRegister(ENC28_PHCON1, 0x0100U);   // Full Duplex
#else
  ENC28_MIIWritePhyRegister(ENC28_PHCON1, 0x0000U);   // Half Duplex
  ENC28_MIIWritePhyRegister(ENC28_PHCON2, ENC28_HDLDIS_MASK);
#endif
  ENC28_MIIWritePhyRegister(ENC28_PHLCON, 0x0472U);   // LEDA: 0100B LEDB: 0111B
  // Enable Link interrupt
  ENC28_MIIWritePhyRegister(ENC28_PHIE, ENC28_PLNKIE_MASK|ENC28_PGEIE_MASK);
  return ERR_OK;
}

/**
 *  -----------------------------------------------------------------------
 *                      SPI Commands - Control Register
 *  -----------------------------------------------------------------------
 */
/**
 *  Method: ENC28_ReadControlRegister
 *      Read and return a control register value
 *  @param
 *      - addr: The address of the register
 *      - reg_type: An enum type 
 *          - ENC28_ControlRegETH: Eth register
 *          - ENC28_ControlRegMAC: Mac register
 *          - ENC28_ControlRegMII: MII register
 *  @return
 *      - dat: The read register value
 */
uint8_t ENC28_ReadControlRegister(uint8_t addr, ENC28_ControlRegType reg_type)
{
  // Variables
  uint8_t dat;
  ENC28_SelectDevice();
  // Send
  ENC28_SpiWriteByte(addr|0x00u);      // 0b 000 00000 | 5-bit-addr
  // Read
  switch (reg_type) {
  case ENC28_ControlRegETH:
    dat = ENC28_SpiReadByte();
    break;
  case ENC28_ControlRegMAC:
  case ENC28_ControlRegMII:
    dat = ENC28_SpiReadByte();   // dummy byte
    dat = ENC28_SpiReadByte();   // data byte
    break;
  default:
    break;
  }
  ENC28_DeselectDevice();
  return dat;
}
/**
 *  Method: ENC28_WriteControlRegister
 *      Write data to a control register of enc28j60
 *  @param
 *      - addr: The register address
 *      - dat: The data to write
 *  @return
 *      - ERR_OK: No error
 */
err_t ENC28_WriteControlRegister(uint8_t addr, uint8_t dat)
{
  ENC28_SelectDevice();
  // Send
  ENC28_SpiWriteByte(addr|0x40u);      // 0b 010 00000 | 5-bit-addr
  // Write data
  ENC28_SpiWriteByte(dat);
  ENC28_DeselectDevice();
  return ERR_OK;
}
/**
 *  -----------------------------------------------------------------------
 *                         MII PHY registers
 *  -----------------------------------------------------------------------
 */
/**
 *  Method: ENC28_MIIWritePhyRegister
 *      Write data to a PHY register
 *  @param
 *      - addr: The PHY register address
 *      - val: The 16-bit data to write
 *  @return
 *      - ERR_OK: No error
 *      - ERR_TIMEOUT: Failure, timeout
 */
err_t ENC28_MIIWritePhyRegister(uint8_t addr, uint16_t val)
{
  // Write PHY register addr to ENC28_MIREGADR
  ENC28_SelectBank(2);
  ENC28_WriteControlRegister(ENC28_MIREGADR, addr);
  // Firstly write MIWRL
  ENC28_WriteControlRegister(ENC28_MIWRL, (uint8_t)val);
  // Then write MIWRH
  ENC28_WriteControlRegister(ENC28_MIWRH, (uint8_t)(val>>8u));
  // Wait for MISTAT.BUSY being clear (about 10.24us)
  ENC28_Delay10Us();
  ENC28_SelectBank(3);
  if ((ENC28_ReadControlRegister(ENC28_MISTAT, ENC28_ControlRegMII)&ENC28_BUSY_MASK)) {
    return ERR_TIMEOUT;
  }
  return ERR_OK;
}
/**
 *  Method: ENC28_MIIReadPhyRegister
 *      Read the value of a PHY register
 *  @param
 *      - addr: The PHY register address
 *  @return
 *      - The value of PHY register in 16-bit. Returns 0 in case of reading error
 */
uint16_t ENC28_MIIReadPhyRegister(uint8_t addr)
{
  uint16_t val = 0;
  // Write PHY register addr to ENC28_MIREGADR
  ENC28_SelectBank(2);
  ENC28_WriteControlRegister(ENC28_MIREGADR, addr);
  // Set MICMD.MIIRD, then MISTAT.BUSY is set automatically
  ENC28_SetBitField(ENC28_MICMD, ENC28_MIIRD_MASK);
  // Wait for MISTAT.BUSY being clear (about 10.24us)
  ENC28_Delay10Us();
  ENC28_SelectBank(3);
  if ((ENC28_ReadControlRegister(ENC28_MISTAT, ENC28_ControlRegMII)&ENC28_BUSY_MASK)) {
    return 0U;
  }
  ENC28_SelectBank(2);
  // Clear MICMD.MIIRD
  ENC28_ClearBitField(ENC28_MICMD, ENC28_MIIRD_MASK);
  // Read MIRDL, MIRDH to get value
  val = (uint16_t)((ENC28_ReadControlRegister(ENC28_MIRDL, ENC28_ControlRegMII))&0x00ffu);
  val |= (((uint16_t)ENC28_ReadControlRegister(ENC28_MIRDH, ENC28_ControlRegMII))<<8u);
  return val;
}
/**
 *  -----------------------------------------------------------------------
 *                      SPI Commands - Bit Field
 *  -----------------------------------------------------------------------
 */
/**
 *  Method: ENC28_SetBitField
 *  @param
 *      - addr: The register address
 *      - mask: Bit mask to be set (1 for setting; 0 not set)
 *  @return
 *      - ERR_OK: No error 
 */
err_t ENC28_SetBitField(uint8_t addr, uint8_t mask)
{
    ENC28_SelectDevice();
    // Send 100 00000 | addr
    ENC28_SpiWriteByte(0x80u|addr); 
    // Send data mask
    ENC28_SpiWriteByte(mask);
    ENC28_DeselectDevice();
    return ERR_OK;
}
/**
 *  Method: ENC28_ClearBitField
 *  @param
 *      - addr: The register address
 *      - mask: Bit mask to be cleared (1 for clearing; 0 not clear)
 *  @return
 *      - ERR_OK: No error 
 */
err_t ENC28_ClearBitField(uint8_t addr, uint8_t mask)
{
    ENC28_SelectDevice();
    // Send 101 00000 | addr
    ENC28_SpiWriteByte(0xa0u|addr); 
    // Send data mask
    ENC28_SpiWriteByte(mask);
    ENC28_DeselectDevice();
    return ERR_OK;
}
/**
 *  -----------------------------------------------------------------------
 *                      SPI Commands - Buffer Memory
 *  -----------------------------------------------------------------------
 */
/**
 *  Method: ENC28_ReadBufferMemoryByte
 *      Read and return a data byte in buffer memory
 *  @return
 *      - dat: The read memory value
 */
uint8_t ENC28_ReadBufferMemoryByte(void)
{
    uint8_t dat;
    ENC28_SelectDevice();
    // Send 0011 1010 B (0x3A)
    ENC28_SpiWriteByte(0x3Au); 
    // Read
    dat = ENC28_SpiReadByte();
    ENC28_DeselectDevice();
    return dat;
}
/**
 *  Method: ENC28_ReadBufferMemoryBlock
 *      Read a memory block in enc28j60, and copy it to a pre-allocated
 *  memory.
 *  @param
 *      - *dat: A pointer to the first address of a pre-allocated data buffer 
 *      - count: The amount of data to read
 *  @return
 *      - ERR_OK: No error
 *      - ERR_MEM: Memory error (null pointer, etc.)
 */
err_t ENC28_ReadBufferMemoryBlock(uint8_t *dat, const uint16_t count)
{
    uint16_t i;
    if (dat==NULL||count==0) return ERR_MEM;
    ENC28_SelectDevice();
    // Send 0011 1010 B (0x3A)
    ENC28_SpiWriteByte(0x3Au); 
    // Read
    for (i=0; i<count; i++) {
        dat[i] = ENC28_SpiReadByte(); 
    }
    ENC28_DeselectDevice();
    return ERR_OK;
}
/**
 *  Method: ENC28_WriteBufferMemoryByte
 *      Write a byte of data to the buffer memory
 *  @param
 *      - dat: The data to write
 *  @return
 *      - ERR_OK: No error
 */
err_t ENC28_WriteBufferMemoryByte(uint8_t dat)
{
    ENC28_SelectDevice();
    // Send 0111 1010 B (0x7A)
    ENC28_SpiWriteByte(0x7Au); 
    // Send data
    ENC28_SpiWriteByte(dat);
    ENC28_DeselectDevice();
    return ERR_OK;
}
/**
 *  Method: ENC28_WriteBufferMemoryBlock
 *      Write a block of data to the buffer memory
 *  @param
 *      - *dat: A pointer to the first address of the data buffer
 *      - count: The amount of data to write
 *  @return
 *      - ERR_OK: No error
 *      - ERR_MEM: Memory error (null pointer, etc.)
 */
err_t ENC28_WriteBufferMemoryBlock(uint8_t *dat, const uint16_t count)
{
    uint16_t i;
    if (dat==NULL) return ERR_MEM;
    ENC28_SelectDevice();
    // Send 0111 1010 B (0x7A)
    ENC28_SpiWriteByte(0x7Au); 
    // Send data
    for (i=0; i<count; i++) {
        ENC28_SpiWriteByte(dat[i]);
    }
    ENC28_DeselectDevice();
    return ERR_OK;
}
/**
 *  -----------------------------------------------------------------------
 *                      Send/Recieve Ethernet Frames
 *  -----------------------------------------------------------------------
 */
/**
 *  Method: ENC28_SendFrame
 *      Send an Ethernet frame 
 *  @param
 *      - *frame: A pointer to the first address of the frame buffer
 *      - count: The amount of byte of frame to send
 *  @return
 *      - ERR_OK: No error
 *      - ERR_MEM: Memory error (null pointer, etc.)
 */
err_t ENC28_SendFrame(uint8_t *frame, uint16_t count)
{
    if (frame==NULL)
        return ERR_MEM;
    if (count==0)
        return ERR_RANGE;
    // Set ETXST pointer to the control byte (to the first byte)
    //     We just keep it at its initial position now (0000H). Each time, there will
    // be only one Ethernet frame (no matter how long) in the tramsmit buffer.
    //     Later should store the unsent frames in the buffer if it's not full.
    ENC28_SelectBank(0);
    ENC28_WriteControlRegister(ENC28_ETXSTL, 0x00u);      // ETXSTL
    ENC28_WriteControlRegister(ENC28_ETXSTH, 0x00u);      // ETXSTH
    // Set EWRPT pointer to the same address as ETXST
    //      We keep it only at 0000H now
    ENC28_SelectBank(0);
    ENC28_WriteControlRegister(ENC28_EWRPTL, 0x00u);      // EWRPTL
    ENC28_WriteControlRegister(ENC28_EWRPTH, 0x00u);      // EWRPTH
    // Send control byte (0x01U: use configuration in MACON3)
    ENC28_WriteBufferMemoryByte(0x01U);
    // Send Ethernet data 
    //  - Destination addr
    //  - Source addr
    //  - Type/Length
    //  - Data
    //  - Padding+CRC (Sent by enc28j60)
    if (ENC28_WriteBufferMemoryBlock(frame, count) != ERR_OK)
        return ERR_MEM;
    // Set ETXND (point to the last data byte = start(0000H) + count)
    ENC28_SelectBank(0);
    ENC28_WriteControlRegister(ENC28_ETXNDL, count%0xffu);// ETXNDL
    ENC28_WriteControlRegister(ENC28_ETXNDH, count/0xffu);// ETXNDH
    // Interrupt or not?
    //  - Clear EIR.TXIF
    //  - Set EIE.TXIE and EIE.INTIE
    //  - Set ECON1.TXRTS to start transmit
    //  - To cancel the transmission, clear TXRTS bit
    ENC28_ClearBitField(ENC28_EIR, ENC28_TXIF_MASK);      // EIR.TXIF      0x1C.bit3
    ENC28_SetBitField(ENC28_EIE, ENC28_TXIE_MASK|ENC28_INTIE_MASK);    // EIE.TXIE, EIE.INTIE   0x1B bit7, bit3
    ENC28_SetBitField(ENC28_ECON1, ENC28_TXRTS_MASK);         // ECON1.TXRTS
    // If transmit stops because of error/cancel
    //  - ECON1.TXRTS will be cleared
    //  - 7 bytes of transmit state vector will be written to ETXND+1
    //  - EIR.TXIF will be set, if interrupt is enabled 
    //  - ETXST and ETXND will not be modified
    //  - ESTAT.TXABRT shows transmit state; if set, should also check
    //    ESTAT.LATECOL to figure out the failure reason
    //  - State vector is little-endian(in bytes), content see P41 of the
    //    datasheet
    //  - More info of tramsmit register, see P42 of the datasheet
    /**
     *  Here we wait for Tx transmit being finished
     */
    while (!(ENC28_ReadControlRegister(ENC28_EIR, ENC28_ControlRegETH)&ENC28_TXIF_MASK)) {
        // A short delay
//        ENC28_Delay10Us();
    }
    ENC28_ClearBitField(ENC28_EIR, ENC28_TXIF_MASK);
    return ERR_OK;
}
/**
 *  Method: ENC28_ReceiveFrame
 *      Receive an Ethernet frame 
 *  @param
 *      - *frame: A pointer to the first address of the frame buffer
 *  @return
 *      - count : The length of data received.
 */
uint16_t ENC28_ReceiveFrame(uint8_t *frame)
{
    uint16_t count = 0;
    uint8_t next_addr_low_byte = 0;
    uint8_t next_addr_high_byte = 0;
    if (frame==NULL)
        return 0;
    // Enable reception
    //  1. If need an interrupt when a packet received, set EIE.PKTIE and EIE.INTIE
    //  2. If need an interrupt when buffer not enough, clear EIE.RXERIF, set EIE.RXERIE and EIE.INTIE
    //  3. Set ECON1.RXEN to enable reception (after that, cannot modify duplex and RXST/RXND)
    //   After setting RXEN, packets will be written to RxBuffer; When a packet is written into RxBuffer,
    //  EPKTCNT++, EIR.PKTIF set, there will be an interrupt(if enabled); ERXWRPT will advance
//    ENC28_ClearBitField(ENC28_EIE, ENC28_RXERIF_MASK);
//    ENC28_SetBitField(ENC28_EIE, ENC28_PKTIE_MASK|ENC28_INTIE_MASK|ENC28_RXERIE_MASK);
    ENC28_SetBitField(ENC28_ECON1, ENC28_RXEN_MASK);
    // Is there any packet?
    ENC28_SelectBank(0);
    if (!(ENC28_ReadControlRegister(ENC28_EIR, ENC28_ControlRegETH)&ENC28_PKTIF_MASK)) {
        // No packets to receive
        return 0;
    }
    // Read the next data packet address (2 bytes)
    next_addr_low_byte = ENC28_ReadBufferMemoryByte();
    next_addr_high_byte = ENC28_ReadBufferMemoryByte();
    // Read State Vector (4 bytes)
    // First two bytes are length of the frame, stored little endian
    count = 0u;
    count = (uint16_t)(ENC28_ReadBufferMemoryByte()&0x00ffu);      // Low byte
    count |= (uint16_t)(((uint16_t)ENC28_ReadBufferMemoryByte())<<8u);
    if (count==0u) {
        // Roll back transaction
        ENC28_WriteControlRegister(ENC28_ERXRDPTL, next_addr_low_byte);
        ENC28_WriteControlRegister(ENC28_ERXRDPTH, next_addr_high_byte);
        return 0;
    }
    // Next two bytes not used now
    (void)ENC28_ReadBufferMemoryByte();
    (void)ENC28_ReadBufferMemoryByte();
    // Don't receive CRC (the last 4 bytes)
    count-=4u;
    // Read Data Packets (destination addr, source addr, type/len, data(padding), CRC)
    if (ENC28_ReadBufferMemoryBlock(frame, count) != ERR_OK) {
        // Roll back transaction?
        ENC28_WriteControlRegister(ENC28_ERXRDPTL, next_addr_low_byte);
        ENC28_WriteControlRegister(ENC28_ERXRDPTH, next_addr_high_byte);
        return 0;
    }
    // Set ERDPT to next buffer address
    ENC28_WriteControlRegister(ENC28_ERDPTL, next_addr_low_byte);
    ENC28_WriteControlRegister(ENC28_ERDPTH, next_addr_high_byte);
    // Free Memory Buffer Space
    // 1. Move ERXRDPT to the next packet address(hardware will write to but not include this position)
    //    Should write ERXRDPTL firstly because it will be buffered (address not accessible) to avoid move
    //    the pointer partially.
    //    If hardware tries to write ERXRDPT, EIR.RXERIF will be set, and interrupt if it's enabled.
    ENC28_SelectBank(0);
    ENC28_WriteControlRegister(ENC28_ERXRDPTL, next_addr_low_byte);
    ENC28_WriteControlRegister(ENC28_ERXRDPTH, next_addr_high_byte);
    // 2. Set ECON2.PKTDEC to let EPKTCNT decrement by 1.
    //    If after decrementing, EPKTCNT==0, EIR.PKTIF will be cleared; otherwise remains set,
    //    indicating additional packets are waiting to be processed.
    //    If EPKTCNT==255, all new packets will be aborted, even buffer not full. In this case,
    //    EIR.RXERIF will be set.
    //    If want to process packets later, should copy them to the unused memory buffer using DMA.
    ENC28_SetBitField(ENC28_ECON2, ENC28_PKTDEC_MASK);
    // 3. If want to know available space in the buffer, should read ERXWRPTL and ERXWRPTH, and compare
    //    with ERXRDPT.
    //      - Read EPKTCNT save it;
    //      - Read ERXWRPT
    //      - Read EPKTCNT again and compare with the previous value; if not match reread ERXWRPT, until they are the same
    //      - Read ERXRDPT:
    //      -   if ERXWRPT>ERXRDPT, space = (ERXND-ERXST)-(ERXWRPT-ERXRDPT)
    //      -   else if ERXWRPT=ERXRDPT, space = ERXND-ERXST
    //      -   else space = ERXRDPT-ERXWRPT-1
    return count;
}
/**
 *  -----------------------------------------------------------------------
 *                       Interrupt events
 *  -----------------------------------------------------------------------
 */
/**
 *  Method: ENC28_OnFrameInterrupt(void)
 *      This event should be called by the programmer when an ENC28J60
 *  interrupt occurs. It will find the correspond interrupt source, then
 *  call the event function.
 */
void ENC28_OnInterrupt(void)
{
    uint8_t eth_interrupt_flag;
    // Disable INTIE
    ENC28_DisableGlobalInterrupt();
    // Interrupt mask, then clear interrupt flag
    eth_interrupt_flag = ENC28_ReadControlRegister(ENC28_EIR, ENC28_ControlRegETH);
    if (eth_interrupt_flag&ENC28_PKTIF_MASK) {
        ENC28_ClearBitField(ENC28_EIR, ENC28_PKTIF_MASK);
        ENC28_OnFrameReceived();
    } else if (eth_interrupt_flag&ENC28_TXIF_MASK) {
        ENC28_ClearBitField(ENC28_EIR, ENC28_TXIF_MASK);
        ENC28_OnFrameTransmitted();
    } else if (eth_interrupt_flag&ENC28_DMAIF_MASK) {
        ENC28_ClearBitField(ENC28_EIR, ENC28_DMAIF_MASK);
    } else if (eth_interrupt_flag&ENC28_LINKIF_MASK) {
        ENC28_ClearBitField(ENC28_EIR, ENC28_LINKIF_MASK);
    } else if (eth_interrupt_flag&ENC28_WOLIF_MASK) {
        ENC28_ClearBitField(ENC28_EIR, ENC28_WOLIF_MASK);
    } else if (eth_interrupt_flag&ENC28_TXERIF_MASK) {
        ENC28_ClearBitField(ENC28_EIR, ENC28_TXERIF_MASK);
    } else if (eth_interrupt_flag&ENC28_RXERIF_MASK) {
        ENC28_ClearBitField(ENC28_EIR, ENC28_RXERIF_MASK);
    }
    // Enable INTIE
    ENC28_EnableGlobalInterrupt();
}
/**
 *  Method: ENC28_OnFrameTransmitted(void)
 *      This event is called after a whole frame has been sent, TXIF is set
 *       - If TXRTS from 1 to 0, TXIF will be set;
 *       - If TXABRT not set, packet is successfully sent
 */
static void ENC28_OnFrameTransmitted(void)
{

}
/**
 *  Method: ENC28_OnFrameReceived(void)
 *      This event is call after PKTIF is set
 *      - EPKTCNT is not 0;
 *      - When EPKTCNT==0, PKTIF can be clear automatically
 */
static void ENC28_OnFrameReceived(void)
{
}
/**
 *  Method: ENC28_OnTxError(void)
 *      This event is call after Tx error, TXERIF is set
 *       - When transmit is aborted;
 *
 */
static void ENC28_OnTxError(void)
{
}
/**
 *  Method: ENC28_OnRxError(void)
 *      This event is call after Rx error, RXERIF is set
 *       - Hardware tries to write ERXRDPT;
 *       - EPKTCNT reaches 255;
 */
static void ENC28_OnRxError(void)
{
}
