// WatchSDK_Sample.cpp : implementation file
//

#include "stdAfx.h"
#include "WatchSDK_Sample.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifdef _DEBUG
#pragma comment(lib, "./bin/idiswatchd.lib")
#else
#pragma comment(lib, "./bin/idiswatch.lib")
#endif

//////////////////////////////////////////////////////////////////////////

WatchSDK_Class::WatchSDK_Class(void)
{
	_maxChannel = 0;
}

WatchSDK_Class::~WatchSDK_Class(void)
{
	/* nothing */
}

//////////////////////////////////////////////////////////////////////////

IDISHWATCH WatchSDK_Class::initialize(void)
{
	return ::watch_initialize();
}

void WatchSDK_Class::finalize(IDISHWATCH hWatch)
{
	::watch_finalize(hWatch);
}

void WatchSDK_Class::startup(IDISHWATCH hWatch, int max_channel)
{
	::watch_startup(hWatch, max_channel);
	_maxChannel = max_channel;
}

void WatchSDK_Class::cleanup(IDISHWATCH hWatch)
{
	::watch_cleanup(hWatch);
}

//////////////////////////////////////////////////////////////////////////

int  WatchSDK_Class::connect(IDISHWATCH hWatch, LPCTSTR siteName, LPCTSTR siteAddress, LPCTSTR userName, LPCTSTR userPassword, int port, void* attachment)
{
	return ::watch_connect(hWatch, siteName, siteAddress, userName, userPassword, port, false, attachment);
}

bool WatchSDK_Class::reconnect(IDISHWATCH hWatch, LPCTSTR siteName, LPCTSTR siteAddress, LPCTSTR userName, LPCTSTR userPassword, int port, short channel, void* attachment)
{
	return ::watch_reconnect(hWatch, siteName, siteAddress, userName, userPassword, port, channel, attachment);
}

int  WatchSDK_Class::connect_dvrns(IDISHWATCH hWatch, LPCTSTR siteName, LPCTSTR dvrnsAddress, LPCTSTR dvrName, LPCTSTR userName, LPCTSTR userPassword, int dvrnsPort, void* attachment)
{
	return ::watch_connect_dvrns(hWatch, siteName,dvrnsAddress, dvrName, userName, userPassword, dvrnsPort, attachment);
}

bool WatchSDK_Class::reconnect_dvrns(IDISHWATCH hWatch, LPCTSTR siteName, LPCTSTR dvrnsAddress, LPCTSTR dvrName, LPCTSTR userName, LPCTSTR userPassword, int dvrnsPort, short channel, void* attachment)
{
	return ::watch_reconnect_dvrns(hWatch, siteName, dvrnsAddress, dvrName, userName, userPassword, dvrnsPort, channel, attachment);
}

void WatchSDK_Class::disconnect(IDISHWATCH hWatch, int channel)
{
	::watch_disconnect(hWatch, channel);
}

bool WatchSDK_Class::isConnecting(IDISHWATCH hWatch, int channel)
{
	return ::watch_isConnecting(hWatch, channel);
}

bool WatchSDK_Class::isConnected(IDISHWATCH hWatch, int channel)
{
	return ::watch_isConnected(hWatch, channel);
}

bool WatchSDK_Class::setCameraList(IDISHWATCH hWatch, int channel, const LPBYTE cameras, int length)
{
	return ::watch_setCameraList(hWatch, channel, cameras, length);
}

void WatchSDK_Class::sendRequestCheck(IDISHWATCH hWatch, int channel)
{
	::watch_sendRequestCheck(hWatch, channel);
}

//////////////////////////////////////////////////////////////////////////

bool WatchSDK_Class::needPtzAdvancedMenu(IDISHWATCH hWatch, int channel, int camera)
{
	return ::watch_needPtzAdvancedMenu(hWatch, channel, camera);
}

bool WatchSDK_Class::needPtzPreset(IDISHWATCH hWatch, int channel, int camera)
{
	return ::watch_needPtzPreset(hWatch, channel, camera);
}

bool WatchSDK_Class::getPtzPreset(IDISHWATCH hWatch, int channel, LPBYTE lpPreset)
{
	return ::watch_getPtzPreset(hWatch, channel, lpPreset);
}

bool WatchSDK_Class::getPtzPresetIDR(IDISHWATCH hWatch, int channel, LPBYTE lpPreset)
{
	return ::watch_getPtzPresetIDR(hWatch, channel, lpPreset);
}

bool WatchSDK_Class::getUsePTZ(IDISHWATCH hWatch, int channel, int camera)
{
	return ::watch_getUsePTZ(hWatch, channel, camera);
}

int WatchSDK_Class::getUsePTZEx(IDISHWATCH hWatch, int channel, int camera)
{
	return ::watch_getUsePTZEx(hWatch, channel, camera);
}

bool WatchSDK_Class::getStatus(IDISHWATCH hWatch, int channel, LPBYTE lpStatus)
{
	return ::watch_getStatus(hWatch, channel, lpStatus);
}

bool WatchSDK_Class::sendReqStatusIDR(IDISHWATCH hWatch, int channel)
{
	return ::watch_sendReqStatusIDR(hWatch, channel);
}

const char* WatchSDK_Class::getCameraTitleIDR(IDISHWATCH hWatch, int channel, int camera)
{
	return ::watch_getCameraTitleIDR(hWatch, channel, camera);
}

//////////////////////////////////////////////////////////////////////////

bool WatchSDK_Class::setColor(IDISHWATCH hWatch, int channel, int camera, int type, int value)
{
	return ::watch_setColor(hWatch, channel, camera, type, value);
}

bool WatchSDK_Class::setPtz(IDISHWATCH hWatch, int channel, LPBYTE lpCommand)
{
	return ::watch_setPtz(hWatch, channel, lpCommand);
}

bool WatchSDK_Class::setPtzPreset(IDISHWATCH hWatch, int channel, int camera, LPBYTE presets)
{
	return ::watch_setPtzPreset(hWatch, channel, camera, presets);
}

bool WatchSDK_Class::setPtzPresetIDR(IDISHWATCH hWatch, int channel, int camera, LPBYTE presets)
{
	return ::watch_setPtzPresetIDR(hWatch, channel, camera, presets);
}

bool WatchSDK_Class::setAlarmOut(IDISHWATCH hWatch, int channel, int alarmid, bool fdevon)
{
	return ::watch_setAlarmOut(hWatch, channel, alarmid, fdevon);
}

//////////////////////////////////////////////////////////////////////////

int WatchSDK_Class::getCountAlarmOut(IDISHWATCH hWatch, int channel)
{
	return ::watch_getCountAlarmOut(hWatch, channel);
}

int WatchSDK_Class::checkAuthority(IDISHWATCH hWatch, int channel)
{
	return ::watch_checkAuthority(hWatch, channel);
}

bool WatchSDK_Class::isAuthorityCovertView(IDISHWATCH hWatch, int channel)
{
	return ::watch_isAuthorityCovertView(hWatch, channel);
}

bool WatchSDK_Class::isConnectedIDR(IDISHWATCH hWatch, int channel)
{
	return ::watch_isConnectedIDR(hWatch, channel);
}

bool WatchSDK_Class::isSupport(IDISHWATCH hWatch, int channel, int supportType)
{
	return ::watch_isSupport(hWatch, channel, supportType);
}

void WatchSDK_Class::registerCallback(IDISHWATCH hWatch, int ntypes, LPLISTENER_FUNC lpFunc)
{
	::watch_registerCallback(hWatch, ntypes, lpFunc);
}

//////////////////////////////////////////////////////////////////////////

bool WatchSDK_Class::sendNetworkAlarmOn(IDISHWATCH hWatch, int channel, LPBYTE pNetAlarmInfo)
{
	return ::watch_sendNetworkAlarmOn(hWatch, channel, pNetAlarmInfo);
}

bool WatchSDK_Class::sendNetworkAlarmOff(IDISHWATCH hWatch, int channel, LPBYTE pNetAlarmInfo)
{
	return ::watch_sendNetworkAlarmOff(hWatch, channel, pNetAlarmInfo);
}

bool WatchSDK_Class::requestStreamChannelControl(IDISHWATCH hWatch, int channel, int camera, int seqNumber, int bufflength, char* buffer)
{
	return ::watch_requestStreamChannelControl(hWatch, channel, camera, seqNumber, bufflength, buffer);
}

bool WatchSDK_Class::setUserParamByHandle(IDISHWATCH hWatch, void* pUserParam)
{
    return ::watch_setUserParamByHandle(hWatch, pUserParam);
}

bool WatchSDK_Class::setUserParamByChannel(IDISHWATCH hWatch, int channel, void* pUserParam)
{
    return ::watch_setUserParamByChannel(hWatch, channel, pUserParam);
}

void* WatchSDK_Class::getUserParamByHandle(IDISHWATCH hWatch)
{
    return ::watch_getUserParamByHandle(hWatch);
}

void* WatchSDK_Class::getUserParamByChannel(IDISHWATCH hWatch, int channel)
{
    return ::watch_getUserParamByChannel(hWatch, channel);
}

int WatchSDK_Class::getCountAvailableHandle(void)
{
    return ::watch_getCountAvailableHandle();
}

int WatchSDK_Class::getCountAvailableChannel(IDISHWATCH hWatch)
{
    return ::watch_getCountAvailableChannel(hWatch);
}

bool WatchSDK_Class::getProductInfo(IDISHWATCH hWatch, int channel, int queryType, void* target, unsigned int targetSize)
{
    return ::watch_getProductInfo(hWatch, channel, queryType, target, targetSize);
}


//////////////////////////////////////////////////////////////////////////
bool WatchSDK_Class::startupAudio(int maxChannel, HWND hwndFocus)
{
    return ::watch_startupAudio(maxChannel, hwndFocus);
}

bool WatchSDK_Class::playAudioFrame(IDISHWATCH hWatch, int channel, LPPARAMWS_FRAMEINFO frameInfo)
{
    return ::watch_playAudioFrame(hWatch, channel, frameInfo);
}

bool WatchSDK_Class::decodeAudioFrame(IDISHWATCH hWatch, int channel, const LPPARAMWS_FRAMEINFO frameInfo, LPBYTE decoded, int bufferSize, int* decodedLen, LPPARAMW_AUDIOINFO audioInfo)
{
    return ::watch_decodeAudioFrame(hWatch, channel, frameInfo, decoded, bufferSize, decodedLen, audioInfo);
}

bool WatchSDK_Class::setAudioList(IDISHWATCH hWatch, int channel, const LPBYTE audios, int length)
{
    return ::watch_setAudioList(hWatch, channel, audios, length);
}

bool WatchSDK_Class::requestDeviceAudioOutOpen(IDISHWATCH hWatch, int channel, int deviceId)
{
    return ::watch_requestDeviceAudioOutOpen(hWatch, channel, deviceId);
}

bool WatchSDK_Class::requestDeviceAudioOutClose(IDISHWATCH hWatch, int channel, int deviceId)
{
    return ::watch_requestDeviceAudioOutClose(hWatch, channel, deviceId);
}

bool WatchSDK_Class::enableMic(IDISHWATCH hWatch, int channel, bool enable)
{
    return ::watch_enableMic(hWatch, channel, enable);
}

bool WatchSDK_Class::disableSpeaker(IDISHWATCH hWatch, int channel, int camera)
{
    return ::watch_disableSpeaker(hWatch, channel, camera);
}

bool WatchSDK_Class::sendCapturedAudio(IDISHWATCH hWatch, int channel, const LPPARAMW_AUDIOINFO capturedAudio)
{
    return ::watch_sendCapturedAudio(hWatch, channel, capturedAudio);
}

void WatchSDK_Class::setLoggerProperties(unsigned char logType, unsigned char logLevel)
{
    return ::watch_setLoggerProperties(logType, logLevel);
}

//////////////////////////////////////////////////////////////////////////

LPCTSTR WatchSDK_Class::getReasonDisconnected(int reason) const
{
	LPTSTR lpszReturn = _T("");

	switch (reason) {
	case IDIS_WHYDISCONNECTED::UNKNOWN : 
		lpszReturn = _T("unknown case");
		break;
	case IDIS_WHYDISCONNECTED::LOGOUT :
		lpszReturn = _T("normally logout");
		break;
	case IDIS_WHYDISCONNECTED::FULL_CHANNEL :
		lpszReturn = _T("deny connection because all of server channels are used");
		break;
	case IDIS_WHYDISCONNECTED::INVALID_VERSION :
		lpszReturn = _T("invalid product version");
		break;
	case IDIS_WHYDISCONNECTED::LOGIN_FAIL :
		lpszReturn = _T("invalid user or password");
		break;
	case IDIS_WHYDISCONNECTED::ADMIN_CLOSE : 
		lpszReturn = _T("admin close the current connection forcely");
		break;
	case IDIS_WHYDISCONNECTED::ADMIN_TIMEOUT :
		lpszReturn = _T("connection timeout");
		break;
	case IDIS_WHYDISCONNECTED::SYS_SHUTDOWN :
		lpszReturn = _T("post system shutdown");
		break;
	case IDIS_WHYDISCONNECTED::NO_CHANNEL :
		lpszReturn = _T("cann't connect - all of my network channels are used");	
		break;
	case IDIS_WHYDISCONNECTED::NO_SERVER : 
		lpszReturn = _T("cann't connect - no server module");
		break;
	case IDIS_WHYDISCONNECTED::NET_DOWN : 
		lpszReturn = _T("network is down");
		break;
	case IDIS_WHYDISCONNECTED::NET_UNREACHABLE :
		lpszReturn = _T("network is unreachable");
		break;
	case IDIS_WHYDISCONNECTED::CONN_TIMEOUT :
		lpszReturn = _T("connection time out");
		break;
	case IDIS_WHYDISCONNECTED::CONN_RESET : 
		lpszReturn = _T("connection reset by peer");
		break;
	case IDIS_WHYDISCONNECTED::HOST_DOWN : 
		lpszReturn = _T("host is down");
		break;
	case IDIS_WHYDISCONNECTED::HOST_UNREACHABLE : 
		lpszReturn = _T("no route th host");
		break;
	case IDIS_WHYDISCONNECTED::CONN_ABORTED : 
		lpszReturn = _T("connection aborted");
		break;
	case IDIS_WHYDISCONNECTED::CONN_CANCEL : 
		lpszReturn = _T("connection has been canceled by user.");
		break;
	case IDIS_WHYDISCONNECTED::NET_NORESPONSE :
		lpszReturn = _T("the peer host does not respond.");
		break;
	case IDIS_WHYDISCONNECTED::NET_NOISY :
		lpszReturn = _T("network is too noisy.");
		break;
	case IDIS_WHYDISCONNECTED::SEND_OVERFLOW :
		lpszReturn = _T("sending queue overflow.");
		break;
	default :
		lpszReturn = _T("unknown case");
		break;
	}

	return lpszReturn;
}
