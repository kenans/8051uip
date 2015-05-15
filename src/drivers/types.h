#ifndef _TYPES_H_
#define _TYPES_H_
// --------------------------------------------------
//                  Includes
// --------------------------------------------------
#include "51_config.h"
// --------------------------------------------------
//                   Types
// --------------------------------------------------
typedef unsigned char uint8_t;
typedef signed char int8_t;
typedef unsigned int uint16_t;
typedef signed int int16_t;
typedef unsigned long uint32_t;
typedef signed long int32_t;
typedef bit bool;

#ifndef NULL
#define NULL (void*)0
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#endif // _TYPES_H_
