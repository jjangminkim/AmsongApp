// IDIS_WatchSDK.h : header file
//

#ifndef _REMOTESETUPSDK_INTERFACE_
#define _REMOTESETUPSDK_INTERFACE_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IDIS_Define.h"
#include "IDIS_RemoteSetupSDKTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    enum _types {
        ON_CONNECTED = 0,
        ON_DISCONNECTED,
        ON_REMOTE_SETUP_RECEIVED,
        ON_REMOTE_SETUP_RECEIVE_FAIL,
        ON_REMOTE_SETUP_UPDATE_OK,
        ON_REMOTE_SETUP_UPDATE_FAIL,
        ON_DEVICEDATETIMELOADED,
        ON_SUCCESS_SETDEVICEDATETIME,
        MAX_LISTENER
    };
} CALLBACK_ADMIN;

typedef struct {
    enum _codes {
        UNKNOWN = 0,
        NOT_SUPPORTED_PRODUCT,
    };
} REMOTE_SETUP_FAIL_CODE;

typedef struct {
    int id;
    int dst;
    unsigned int time;
} DATE_TIME;

//{{ adminsdk_callback_func types
// reference below CALLBACK_ADMIN struct for ntypes
IDIS_DLLFUNC void IDISAPI admin_registerCallback(IDISHADMIN hAdmin, int ntypes, LPLISTENER_FUNC lpFunc);

/////////////////////////////////////////////////////////////////////////////

IDIS_DLLFUNC IDISHADMIN IDISAPI admin_initialize(void);
IDIS_DLLFUNC void IDISAPI admin_finalize(IDISHADMIN hAdmin);
IDIS_DLLFUNC void IDISAPI admin_startup(IDISHADMIN hAdmin, int nMaxChannels);
IDIS_DLLFUNC void IDISAPI admin_cleanup(IDISHADMIN hAdmin);

//////////////////////////////////////////////////////////////////////////
// admin sdk functions

IDIS_DLLFUNC int  IDISAPI admin_connect(IDISHADMIN hAdmin, LPCTSTR siteAddress, LPCTSTR userName, LPCTSTR userPassword, int port);
IDIS_DLLFUNC int  IDISAPI admin_connect_dvrns(IDISHADMIN hAdmin, const char* dvrnsAddress, const char* dvrName, const char* userName, const char* userPassword, int dvrnsPort);
IDIS_DLLFUNC void IDISAPI admin_disconnect(IDISHADMIN hAdmin, int channel);
IDIS_DLLFUNC bool IDISAPI admin_requestRemoteSetup(IDISHADMIN hAdmin, int channel);
IDIS_DLLFUNC bool IDISAPI admin_updateRemoteSetup(IDISHADMIN hAdmin, int channel);

IDIS_DLLFUNC bool IDISAPI admin_requestDeviceDateTime(IDISHADMIN hAdmin, int channel);
IDIS_DLLFUNC bool IDISAPI admin_getDeviceDateTime(IDISHADMIN hAdmin, int channel, DATE_TIME* dt);
IDIS_DLLFUNC bool IDISAPI admin_setDeviceDateTime(IDISHADMIN hAdmin, int channel, DATE_TIME& dt);
// if client is idle for 2 min. DVR automatically closes current connection. 
// To avoid this, client should send 'dummy' data for extending time-out.
IDIS_DLLFUNC bool IDISAPI admin_requestCheck(IDISHADMIN hAdmin, int channel);

// returns fail if 
//  : target buffer size mismatch
//      or unsupported query type.
IDIS_DLLFUNC bool IDISAPI admin_getProductInfo(IDISHADMIN hAdmin, int channel, int queryType, void* target, unsigned int targetSize);


// RemoteSetup Category
// System, Network, Device, Record, Event

IDIS_DLLFUNC bool IDISAPI setup_getConfigSysInfo(IDISHADMIN hAdmin, int channel, IDIS_CONFIG_SYSINFO* sysInfo);
IDIS_DLLFUNC bool IDISAPI setup_setConfigSysInfo(IDISHADMIN hAdmin, int channel, IDIS_CONFIG_SYSINFO* sysInfo);

// up to 32 cameras..
// number of camera will be saved in 'int* camera'
IDIS_DLLFUNC bool IDISAPI setup_getConfigCameraGeneral(IDISHADMIN hAdmin, int channel, IDIS_CONFIG_CAMERA_GENERAL* camInfo, int* count);
IDIS_DLLFUNC bool IDISAPI setup_setConfigCameraGeneral(IDISHADMIN hAdmin, int channel, IDIS_CONFIG_CAMERA_GENERAL* camInfo, int count);

IDIS_DLLFUNC bool IDISAPI setup_getConfigNetworkCommon(IDISHADMIN hAdmin, int channel, IDIS_CONFIG_NETWORK_COMMON* common);
IDIS_DLLFUNC bool IDISAPI setup_setConfigNetworkCommon(IDISHADMIN hAdmin, int channel, IDIS_CONFIG_NETWORK_COMMON* common);
IDIS_DLLFUNC bool IDISAPI setup_getConfigNetworkLan(IDISHADMIN hAdmin, int channel, IDIS_CONFIG_NETWORK_LAN* lan);
IDIS_DLLFUNC bool IDISAPI setup_setConfigNetworkLan(IDISHADMIN hAdmin, int channel, IDIS_CONFIG_NETWORK_LAN* lan);
IDIS_DLLFUNC bool IDISAPI setup_getConfigNetworkDvrns(IDISHADMIN hAdmin, int channel, IDIS_CONFIG_NETWORK_DVRNS* dvrns);
IDIS_DLLFUNC bool IDISAPI setup_setConfigNetworkDvrns(IDISHADMIN hAdmin, int channel, IDIS_CONFIG_NETWORK_DVRNS* dvrns);

IDIS_DLLFUNC bool IDISAPI setup_getConfigEventVideoLoss(IDISHADMIN hAdmin, int channel, IDIS_CONFIG_EVENT_VIDEOLOSS* videoLoss);
IDIS_DLLFUNC bool IDISAPI setup_setConfigEventVideoLoss(IDISHADMIN hAdmin, int channel, IDIS_CONFIG_EVENT_VIDEOLOSS* videoLoss);
IDIS_DLLFUNC bool IDISAPI setup_getConfigEventMotion(IDISHADMIN hAdmin, int channel, IDIS_CONFIG_EVENT_MOTION* motion);
IDIS_DLLFUNC bool IDISAPI setup_setConfigEventMotion(IDISHADMIN hAdmin, int channel, IDIS_CONFIG_EVENT_MOTION* motion);
IDIS_DLLFUNC bool IDISAPI setup_getConfigEventAlarmIn(IDISHADMIN hAdmin, int channel, IDIS_CONFIG_EVENT_ALARMIN* alarmIn);
IDIS_DLLFUNC bool IDISAPI setup_setConfigEventAlarmIn(IDISHADMIN hAdmin, int channel, IDIS_CONFIG_EVENT_ALARMIN* alarmIn);
IDIS_DLLFUNC bool IDISAPI setup_getConfigEventVideoBlind(IDISHADMIN hAdmin, int channel, IDIS_CONFIG_EVENT_VIDEOBLIND* videoBlind);
IDIS_DLLFUNC bool IDISAPI setup_setConfigEventVideoBlind(IDISHADMIN hAdmin, int channel, IDIS_CONFIG_EVENT_VIDEOBLIND* videoBlind);

// number of schedule will be saved in 'int* count'
IDIS_DLLFUNC bool IDISAPI setup_getConfigAudioAlarm(IDISHADMIN hAdmin, int channel, IDIS_CONFIG_AUDIO_ALARM* audioAlarm, int* count);
IDIS_DLLFUNC bool IDISAPI setup_setConfigAudioAlarm(IDISHADMIN hAdmin, int channel, IDIS_CONFIG_AUDIO_ALARM* audioAlarm, int count);


// System->Date/Time->Date/Time
// get/set Date
// get/set Time
// get/set DateFormat
// get/set TimeFormat
// get/set TimeZone;
// get/set UseDaylightSave

// System->Date/Time->Holiday
// getHolidayList
// add/delete Holiday

// System->Date/Time->TimeSync
// get/set AutoSync;
// get/set TimeServer;
// get/set RunAsServer

// System->Storage
// System->User

#ifdef __cplusplus
}
#endif

/////////////////////////////////////////////////////////////////////////////

#endif  // !_REMOTESETUPSDK_INTERFACE_
