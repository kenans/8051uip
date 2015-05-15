#ifndef _DELAY_H
#define _DELAY_H
// --------------------------------------------------
//                  Includes
// --------------------------------------------------
#include "types.h"
#include "51_config.h"
// --------------------------------------------------
//                    APIs
// --------------------------------------------------
#define CPU_CORE_FREQUENCY 12000000UL
void DelayMs(unsigned int data num);
#define Delay5Us()   do{_nop_();_nop_();_nop_();_nop_();_nop_();}while(0)
#define Delay10Us()  do{Delay5Us();Delay5Us();}while(0)
#define Delay50Us()  do{Delay10Us();Delay10Us();Delay10Us();Delay10Us();Delay10Us();}while(0)
#define Delay100Us() do{Delay50Us();Delay50Us();}while(0)
#define Delay500Us() do{Delay100Us();Delay100Us();Delay100Us();Delay100Us();Delay100Us();}while(0)
#endif // _DELAY_H
