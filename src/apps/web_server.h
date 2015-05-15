#ifndef _WEB_SERVER_H_
#define _WEB_SERVER_H_
// ------------------------  Include  ---------------------------
#include "types.h"
// --------------------   uip_appstate  -------------------------

typedef struct tcp_state uip_tcp_appstate_t;
// ------------------------  APPCALL  ---------------------------
#ifndef UIP_APPCALL()
#define UIP_APPCALL() WebServer_Appcall()
#endif // UIP_APPCALL
// ------------------------   APIs    ---------------------------
#define WebServer_Init() uip_listen(HTONS(80))
void WebServer_Appcall(void);

#endif  // _WEB_SERVER_H_
