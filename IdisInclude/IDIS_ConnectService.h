// IDIS_WatchSDK.h : header file
//

#ifndef _IDIS_CONNECTSERVICESDK_INTERFACE_
#define _IDIS_CONNECTSERVICESDK_INTERFACE_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IDIS_Define.h"

#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////////////////////////

typedef struct
{
    enum _types {
        ONNATTYPEDISCORVERED = 0,
        MAX_LISTENER
    };
    // SDK user must implement both callbacks for compatibility.
} CALLBACK_CONNECTSERVICE;

struct G2NAT_INFO {
    enum VERSION {
        G2NATINFO_1_0 = 0x00000100,
        G2NATINFO = G2NATINFO_1_0,
    };
    enum TYPE {
        TYPE_UNKNOWN = 0,
        TYPE_OPEN_INTERNET,
        TYPE_FULL_CONE,
        TYPE_RESTRICTED_CONE,
        TYPE_PORT_RESTRICTED_CONE,
        TYPE_SYMMETRIC,
        TYPE_SYMMETRIC_UDP_FIREWALL,
        TYPE_UDP_BLOCKED,
        TYPE_DISCOVERY_FAILED,
        TYPE_MOBILE
    };
    enum PORT_MAPPING {
        PORT_MAPPING_NONE = 0x00000000,
        PORT_FORWARDING   = 0x00000001,
        UPNP              = 0x00000002,
        NAT_PMP           = 0x00000004,
    };

    unsigned int  _version;
    unsigned char _type;
    unsigned char _port_mapping;
};

struct G2FEN_CONNECTION {
    enum TYPE {
        UNKNOWN = 0,
        TCP_DIRECT_EXTERNAL = 1,
        TCP_DIRECT_INTERNAL = 2,
        UDP_HOLE_PUNCHING = 3,
        VIA_RELAY_SERVICE = 4
    };
};
IDIS_DLLFUNC void IDISAPI connectservice_registerCallback(int ntypes, LPLISTENER_FUNC lpFunc);
IDIS_DLLFUNC int IDISAPI connectservice_initialize(void);
IDIS_DLLFUNC int IDISAPI connectservice_initialize_setHistoryPath(const char* historyPath);
IDIS_DLLFUNC void IDISAPI connectservice_finalize();
IDIS_DLLFUNC void IDISAPI connectservice_setGateWayServiceAddress(LPCTSTR address, int port);
IDIS_DLLFUNC int IDISAPI connectservice_getProxyPort();
IDIS_DLLFUNC G2NAT_INFO IDISAPI connectservice_getNatInfo();


#ifdef __cplusplus
}
#endif

//////////////////////////////////////////////////////////////////////////

#endif	// !_IDIS_CONNECTSERVICESDK_INTERFACE_
