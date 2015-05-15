/*
 * ethernet.h
 *
 *  Created on: 31 juil. 2014
 *      Author: OrpheoXlite
 */

#ifndef ETHERNET_H_
#define ETHERNET_H_
// --------------------------------------------------
//                  Includes
// --------------------------------------------------
// --------------------------------------------------
//               Configurations
// --------------------------------------------------
/**
 *  Ethernet driver
 *      - 0: ENC28J60
 *
 */
#define ETHERNET_DRIVER   0
/**
 *  MAC address
 */
#ifndef ETHERNET_DRIVER
#define ETH_MAC_ADDR_0  0x00U
#define ETH_MAC_ADDR_1  0x00U
#define ETH_MAC_ADDR_2  0x00U
#define ETH_MAC_ADDR_3  0x00U
#define ETH_MAC_ADDR_4  0x00U
#define ETH_MAC_ADDR_5  0x00U
#endif
// --------------------------------------------------
//                 APIs
// --------------------------------------------------

// --------------------------------------------------
//                Methods
// --------------------------------------------------
#if ETHERNET_DRIVER==0
#include "enc28j60.h"
#define Eth_Init()                  ENC28_Init()
#define Eth_Reset()                 ENC28_Reset()
#define Eth_SetSpeed()
#define Eth_SetDuplexMode()
#define Eth_IsLinkUp()              ENC28_IsPhyLinkUp()
#define Eth_SendFrame(frame, len)   ENC28_SendFrame(frame, len)
#define Eth_ReceiveFrame(frame)     ENC28_ReceiveFrame(frame)
#define Eth_OnInterrupt()           ENC28_OnInterrupt()
/**
 *  MAC address
 *      ADDR_5.ADDR_4.ADDR_3.ADDR_2.ADDR_1.ADDR_0
 */
#define ETH_MAC_ADDR_5  ENC28_MAC_ADDR_5
#define ETH_MAC_ADDR_4  ENC28_MAC_ADDR_4
#define ETH_MAC_ADDR_3  ENC28_MAC_ADDR_3
#define ETH_MAC_ADDR_0  ENC28_MAC_ADDR_0
#define ETH_MAC_ADDR_2  ENC28_MAC_ADDR_2
#define ETH_MAC_ADDR_1  ENC28_MAC_ADDR_1
#else
#endif // ETHERNET_DRIVER


#endif /* ETHERNET_H_ */
