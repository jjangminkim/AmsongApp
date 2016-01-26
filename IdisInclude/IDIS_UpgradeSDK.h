// UpgradeSDK 1.0.0
// ChangeLog
// 1.0 : initial version.

#ifndef _IDIS_UPGRADESDK_INTERFACE_
#define _IDIS_UPGRADESDK_INTERFACE_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if defined(__linux__)
    #ifdef SDK_BUILDER
        #include <Win32Porting/Win32Porting.h>
    #else
        #include "Win32Porting.h"
    #endif
#endif

#include "IDIS_Define.h"

EXTERN_C_BEGIN

typedef struct {
    enum _because_upgrade {
        UPGRADE_FAIL_NONE = 0,
        UPGRADE_FAIL_VER,
		UPGRADE_FAIL_OS_VER,
		UPGRADE_FAIL_SW_VER,
		UPGRADE_FAIL_KERNEL_VER,
		UPGRADE_FAIL_DOWNLOAD,
        UPGRADE_FAIL_ON_PLAYBACK,
        UPGRADE_FAIL_ON_SETUP,
		UPGRADE_FAIL_MOUNT,
		UPGRADE_FAIL_LILO,
		UPGRADE_FAIL_REBOOT,
		UPGRADE_FAIL_CONNECT,
		UPGRADE_FAIL_NETWORK,
		UPGRADE_FAIL_PERMISSION,
		UPGRADE_FAIL_FILE_OPEN,
		UPGRADE_FAIL_FILE_READ,
		UPGRADE_FAIL_FILE_INVALID,
		UPGRADE_FAIL_USER_CANCEL,
		UPGRADE_FAIL_ON_BACKUP,
		UPGRADE_FAIL_ON_MANUAL_ARCHIVE,
		UPGRADE_FAIL_ON_HDD_NOT_EXIST,
		UPGRADE_FAIL_GUARD_STATE_FAIL = 30,
		UPGRADE_FAIL_ERROR_FREE_SPACE,
		UPGRADE_FAIL_NO_FILE,
		UPGRADE_FAIL_GET_FILE_DATA,
		UPGRADE_FAIL_FILE_SEND_ERROR,
		UPGRADE_FAIL_NOT_MATCH_VERSION,
    };
} IDIS_UPGRADE_FAIL_CODE;

typedef struct {
    enum _types {
        UPGRADEOK = 0,
        UPGRADEPROGRESS,
        UPGRADEFAIL,
        MAX_LISTENER
    };
} CALLBACK_UPGRADE;

///callback//////////////////////////////////////////////////////////////////////
IDIS_DLLFUNC void IDISAPI upgrade_registerUpgradeCallback(IDISHADMIN hAdmin, int ntypes, LPLISTENER_FUNC lpFunc);
/////////////////////////////////////////////////////////////////////////////////
IDIS_DLLFUNC bool IDISAPI upgrade_requestUpgrade(IDISHADMIN hAdmin, int channel, char* filename);
IDIS_DLLFUNC bool IDISAPI upgrade_requestUpgradeCancel(IDISHADMIN hAdmin, int channel);
IDIS_DLLFUNC void IDISAPI upgrade_setLoggerProperties(unsigned char logType, unsigned char logLevel);
/////////////////////////////////////////////////////////////////////////////////

EXTERN_C_END

/////////////////////////////////////////////////////////////////////////////

#endif  // !_IDIS_UPGRADESDK_INTERFACE_
