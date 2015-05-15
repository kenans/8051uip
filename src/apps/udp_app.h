#ifndef _UDP_APP_H_
#define _UDP_APP_H_

// ------------------------  Include  ---------------------------
#include "types.h"
// ------------------------  AppData  ---------------------------
typedef struct udp_state uip_udp_appstate_t;
// ------------------------  APPCALL  ---------------------------
#ifndef UIP_UDP_APPCALL()
#define UIP_UDP_APPCALL() UDP_AppCall()
#endif
// ------------------------    API    ---------------------------
void UDP_AppInit(void);
void UDP_AppCall(void);
#endif // _UDP_APP_H_
