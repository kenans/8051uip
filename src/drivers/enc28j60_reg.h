/*
 * enc28j60_reg.h
 *
 *  Created on: 2014Äê7ÔÂ29ÈÕ
 *      Author: apple
 */

#ifndef ENC28J60_REG_H_
#define ENC28J60_REG_H_

/**
 *  -----------------------------------------------------------------------
 *                         ETH/MAC/MII Registers
 *  -----------------------------------------------------------------------
 */
// Common
#define ENC28_EIE         0x1BU
#define ENC28_EIR         0x1CU
#define ENC28_ESTAT       0x1DU
#define ENC28_ECON2       0x1EU
#define ENC28_ECON1       0x1FU
// Bank0
#define ENC28_ERDPTL      0x00U
#define ENC28_ERDPTH      0x01U
#define ENC28_EWRPTL      0x02U
#define ENC28_EWRPTH      0x03U
#define ENC28_ETXSTL      0x04U
#define ENC28_ETXSTH      0x05U
#define ENC28_ETXNDL      0x06U
#define ENC28_ETXNDH      0x07U
#define ENC28_ERXSTL      0x08U
#define ENC28_ERXSTH      0x09U
#define ENC28_ERXNDL      0x0AU
#define ENC28_ERXNDH      0x0BU
#define ENC28_ERXRDPTL    0x0CU
#define ENC28_ERXRDPTH    0x0DU
#define ENC28_ERXWRPTL    0x0EU
#define ENC28_ERXWRPTH    0x0FU
#define ENC28_EDMASTL     0x10U
#define ENC28_EDMASTH     0x11U
#define ENC28_EDMANDL     0x12U
#define ENC28_EDMANDH     0x13U
#define ENC28_EDMADSTL    0x14U
#define ENC28_EDMADSTH    0x15U
#define ENC28_EDMACSL     0x16U
#define ENC28_EDMACSH     0x17U
// Bank1
#define ENC28_EHT0        0x00U
#define ENC28_EHT1        0x01U
#define ENC28_EHT2        0x02U
#define ENC28_EHT3        0x03U
#define ENC28_EHT4        0x04U
#define ENC28_EHT5        0x05U
#define ENC28_EHT6        0x06U
#define ENC28_EHT7        0x07U
#define ENC28_EPMM0       0x08U
#define ENC28_EPMM1       0x09U
#define ENC28_EPMM2       0x0AU
#define ENC28_EPMM3       0x0BU
#define ENC28_EPMM4       0x0CU
#define ENC28_EPMM5       0x0DU
#define ENC28_EPMM6       0x0EU
#define ENC28_EPMM7       0x0FU
#define ENC28_EPMCSL      0x10U
#define ENC28_EPMCSH      0x11U
#define ENC28_EPMOL       0x14U
#define ENC28_EPMOH       0x15U
#define ENC28_EWOLIE      0x16U
#define ENC28_EWOLIR      0x17U
#define ENC28_ERXFCON     0x18U
#define ENC28_EPKTCNT     0x19U
// Bank2
#define ENC28_MACON1      0x00U
#define ENC28_MACON2      0x01U
#define ENC28_MACON3      0x02U
#define ENC28_MACON4      0x03U
#define ENC28_MABBIPG     0x04U
#define ENC28_MAIPGL      0x06U
#define ENC28_MAIPGH      0x07U
#define ENC28_MACLCON1    0x08U
#define ENC28_MACLCON2    0x09U
#define ENC28_MAMXFLL     0x0AU
#define ENC28_MAMXFLH     0x0BU
#define ENC28_MAPHSUP     0x0DU
#define ENC28_MICON       0x11U
#define ENC28_MICMD       0x12U
#define ENC28_MIREGADR    0x14U
#define ENC28_MIWRL       0x16U
#define ENC28_MIWRH       0x17U
#define ENC28_MIRDL       0x18U
#define ENC28_MIRDH       0x19U
// Bank3
#define ENC28_MAADR1      0x00U
#define ENC28_MAADR0      0x01U
#define ENC28_MAADR3      0x02U
#define ENC28_MAADR2      0x03U
#define ENC28_MAADR5      0x04U
#define ENC28_MAADR4      0x05U
#define ENC28_EBSTSD      0x06U
#define ENC28_EBSTCON     0x07U
#define ENC28_EBSTCSL     0x08U
#define ENC28_EBSTCSH     0x09U
#define ENC28_MISTAT      0x0AU
#define ENC28_EREVID      0x12U
#define ENC28_ECOCON      0x15U
#define ENC28_EFLOCON     0x17U
#define ENC28_EPAUSL      0x18U
#define ENC28_EPAUSH      0x19U
/**
 *  -----------------------------------------------------------------------
 *                        PHY Register (16-bit)
 *  -----------------------------------------------------------------------
 */
#define ENC28_PHCON1    0x00U   // Default: 00-- 10-q 0--- ----
#define ENC28_PHSTAT1   0x01U   // Default: ---1 1--- ---- -00-
#define ENC28_PHID1     0x02U   // Default: 0000 0000 1000 0011
#define ENC28_PHID2     0x03U   // Default: 0001 0100 0000 0000
#define ENC28_PHCON2    0x10U   // Default: -000 0000 0000 0000
#define ENC28_PHSTAT2   0x11U   // Default: --00 00q- ---0 ----
#define ENC28_PHIE      0x12U   // Default: 0000 0000 0000 0000
#define ENC28_PHIR      0x13U   // Default: xxxx xxxx xx00 00x0
#define ENC28_PHLCON    0x14U   // Default: 0011 0100 0010 001x
/**
 *  -----------------------------------------------------------------------
 *                            Bit Masks
 *  -----------------------------------------------------------------------
 */
// EIE
#define ENC28_INTIE_MASK    0x80U
#define ENC28_PKTIE_MASK    0x40U
#define ENC28_DMAIE_MASK    0x20U
#define ENC28_LINKIE_MASK   0x10U
#define ENC28_TXIE_MASK     0x08U
#define ENC28_WOLIE_MASK    0x04U
#define ENC28_TXERIE_MASK   0x02U
#define ENC28_RXERIE_MASK   0x01U
// EIR                           
#define ENC28_PKTIF_MASK    0x40U
#define ENC28_DMAIF_MASK    0x20U
#define ENC28_LINKIF_MASK   0x10U
#define ENC28_TXIF_MASK     0x08U
#define ENC28_WOLIF_MASK    0x04U
#define ENC28_TXERIF_MASK   0x02U
#define ENC28_RXERIF_MASK   0x01U
// ESTAT                         
#define ENC28_INT_MASK      0x80U
#define ENC28_LATECOL_MASK  0x10U
#define ENC28_RXBUSY_MASK   0x04U
#define ENC28_TXABRT_MASK   0x02U
#define ENC28_CLKRDY_MASK   0x01U
// ECON2                         
#define ENC28_AUTOINC_MASK  0x80U
#define ENC28_PKTDEC_MASK   0x40U
#define ENC28_PWRSV_MASK    0x20U
#define ENC28_VRPS_MASK     0x08U
// ECON1                         
#define ENC28_TXRST_MASK    0x80U
#define ENC28_RXRST_MASK    0x40U
#define ENC28_DMAST_MASK    0x20U
#define ENC28_CSUMEN_MASK   0x10U
#define ENC28_TXRTS_MASK    0x08U
#define ENC28_RXEN_MASK     0x04U
#define ENC28_BSEL1_MASK    0x02U
#define ENC28_BSEL0_MASK    0x01U
// EWOLIE                        
#define ENC28_UCWOLIE_MASK  0x80U
#define ENC28_AWOLIE_MASK   0x40U
#define ENC28_PMWOLIE_MASK  0x10U
#define ENC28_MPWOLIE_MASK  0x08U
#define ENC28_HTWOLIE_MASK  0x04U
#define ENC28_MCWOLIE_MASK  0x02U
#define ENC28_BCWOLIE_MASK  0x01U
// EWOLIR                        
#define ENC28_UCWOLIF_MASK  0x80U
#define ENC28_AWOLIF_MASK   0x40U
#define ENC28_PMWOLIF_MASK  0x10U
#define ENC28_MPWOLIF_MASK  0x08U
#define ENC28_HTWOLIF_MASK  0x04U
#define ENC28_MCWOLIF_MASK  0x02U
#define ENC28_BCWOLIF_MASK  0x01U
// ERXFCON                       
#define ENC28_UCEN_MASK     0x80U
#define ENC28_ANDOR_MASK    0x40U
#define ENC28_CRCEN_MASK    0x20U
#define ENC28_PMEN_MASK     0x10U
#define ENC28_MPEN_MASK     0x08U
#define ENC28_HTEN_MASK     0x04U
#define ENC28_MCEN_MASK     0x02U
#define ENC28_BCEN_MASK     0x01U
// MACON1                        
#define ENC28_LOOPBK_MASK   0x10U
#define ENC28_TXPAUS_MASK   0x08U
#define ENC28_RXPAUS_MASK   0x04U
#define ENC28_PASSALL_MASK  0x02U
#define ENC28_MARXEN_MASK   0x01U
// MACON2                        
#define ENC28_MARST_MASK    0x80U
#define ENC28_RNDRST_MASK   0x40U
#define ENC28_MARXRST_MASK  0x08U
#define ENC28_RFUNRST_MASK  0x04U
#define ENC28_MATXRST_MASK  0x02U
#define ENC28_TFUNRST_MASK  0x01U
// MACON3                        
#define ENC28_PADCFG2_MASK  0x80U
#define ENC28_PADCFG1_MASK  0x40U
#define ENC28_PADCFG0_MASK  0x20U
#define ENC28_TXCRCEN_MASK  0x10U
#define ENC28_PHDRLEN_MASK  0x08U
#define ENC28_HFRMEN_MASK   0x04U
#define ENC28_FRMLNEN_MASK  0x02U
#define ENC28_FULDPX_MASK   0x01U
// MACON4                        
#define ENC28_DEFER_MASK    0x40U
#define ENC28_BPEN_MASK     0x20U
#define ENC28_NOBKOFF_MASK  0x10U
#define ENC28_LONGPRE_MASK  0x02U
#define ENC28_PUREPRE_MASK  0x01U
// MAPHSUP                       
#define ENC28_RSTINTFC_MASK 0x80U
#define ENC28_RSTRMII_MASK  0x08U
// MICON                         
#define ENC28_RSTMII_MASK   0x80U
// MICMD                         
#define ENC28_MIISCAN_MASK  0x02U
#define ENC28_MIIRD_MASK    0x01U
// EBSTCON                       
#define ENC28_PSV2_MASK     0x80U
#define ENC28_PSV1_MASK     0x40U
#define ENC28_PSV0_MASK     0x20U
#define ENC28_PSEL_MASK     0x10U
#define ENC28_TMSEL1_MASK   0x08U
#define ENC28_TMSEL0_MASK   0x04U
#define ENC28_TME_MASK      0x02U
#define ENC28_BISTST_MASK   0x01U
// MISTAT                        
#define ENC28_NVALID_MASK   0x04U
#define ENC28_SCAN_MASK     0x02U
#define ENC28_BUSY_MASK     0x01U
// ECOCON                        
#define ENC28_COCON2_MASK   0x04U
#define ENC28_COCON1_MASK   0x02U
#define ENC28_COCON0_MASK   0x01U
// EFLOCON                       
#define ENC28_FULDPXS_MASK  0x04U
#define ENC28_FCEN1_MASK    0x02U
#define ENC28_FCEN0_MASK    0x01U
/**
 *  PHY register 16-bit
 */
// PHCON1
#define ENC28_PRST_MASK     0x8000U
#define ENC28_PLOOPBK_MASK  0x4000U
#define ENC28_PPWRSV_MASK   0x0800U
#define ENC28_PDPXMD_MASK   0x0100U
// PHSTAT1
#define ENC28_PFDPX_MASK    0x1000U
#define ENC28_PHDPX_MASK    0x0800U
#define ENC28_LLSTAT_MASK   0x0004U
#define ENC28_JBSTAT_MASK   0x0002U
// PHCON2
#define ENC28_FRCLNK_MASK   0x4000U
#define ENC28_TXDIS_MASK    0x2000U
#define ENC28_JABBER_MASK   0x0400U
#define ENC28_HDLDIS_MASK   0x0100U
// PHSTAT2
#define ENC28_TXSTAT_MASK   0x2000U
#define ENC28_RXSTAT_MASK   0x1000U
#define ENC28_COLSTAT_MASK  0x0800U
#define ENC28_LSTAT_MASK    0x0400U
#define ENC28_DPXSTAT_MASK  0x0200U
#define ENC28_PLRITY_MASK   0x0010U
// PHIE
#define ENC28_PLNKIE_MASK   0x0010U
#define ENC28_PGEIE_MASK    0x0002U
// PHIR
#define ENC28_PLNKIF_MASK   0x0010U
#define ENC28_PGIF_MASK     0x0004U
// PHLCON
#define ENC28_LACFG3_MASK   0x0800U
#define ENC28_LACFG2_MASK   0x0400U
#define ENC28_LACFG1_MASK   0x0200U
#define ENC28_LACFG0_MASK   0x0100U
#define ENC28_LBCFG3_MASK   0x0080U
#define ENC28_LBCFG2_MASK   0x0040U
#define ENC28_LBCFG1_MASK   0x0020U
#define ENC28_LBCFG0_MASK   0x0010U
#define ENC28_LFRQ1_MASK    0x0008U
#define ENC28_LFRQ0_MASK    0x0004U
#define ENC28_STRCH_MASK    0x0002U



#endif /* ENC28J60_REG_H_ */
