#ifndef _ERR_H_
#define _ERR_H_

/**
 *  -----------------------------------------------------------------------
 *                                 Include
 *  -----------------------------------------------------------------------
 */
#include "51_config.h"
/**
 *  -----------------------------------------------------------------------
 *                           Constant and Types
 *  -----------------------------------------------------------------------
 */
typedef char err_t;

#ifndef ERR_OK
#define ERR_OK      0
#endif

#ifndef ERR_MEM
#define ERR_MEM     -1
#endif

#ifndef ERR_RANGE
#define ERR_RANGE   -2
#endif

#ifndef ERR_COMMON
#define ERR_COMMON  -3
#endif

#ifndef ERR_TIMEOUT
#define ERR_TIMEOUT -4
#endif

#ifndef ERR_FATAL
#define ERR_FATAL   -5
#endif
#endif // _ERR_H_
