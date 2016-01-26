// IDIS_AudioSDK.h : header file
//

#ifndef _IDIS_AUDIOSDK_INTERFACE_
#define _IDIS_AUDIOSDK_INTERFACE_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IDIS_Define.h"

#ifdef __cplusplus
extern "C" {
#endif

/////////////////////////////////////////////////////////////////////////////

//{{ audiosdk_callback_func types
// reference below CALLBACK_AUDIO struct for ntypes
IDIS_DLLFUNC void IDISAPI audio_registerCallback(IDISHAUDIO hAudio, int ntypes, LPLISTENER_FUNC lpFunc);

/////////////////////////////////////////////////////////////////////////////

IDIS_DLLFUNC IDISHAUDIO IDISAPI audio_initialize(void);
IDIS_DLLFUNC void IDISAPI audio_finalize(IDISHAUDIO hAudio);
IDIS_DLLFUNC void IDISAPI audio_startup(IDISHAUDIO hAudio, int max_channel, HWND hWndMain);
IDIS_DLLFUNC void IDISAPI audio_cleanup(IDISHAUDIO hAudio);

// audioSDK_connection ////////////////////////////////////

IDIS_DLLFUNC int  IDISAPI audio_connect(IDISHAUDIO hAudio, LPCTSTR siteName, LPCTSTR siteAddress, LPCTSTR userName, LPCTSTR userPassword, int port, bool isPasswordEncrypted = false, void* attachment = NULL);
IDIS_DLLFUNC int  IDISAPI audio_connect_dvrns(IDISHAUDIO hWatch, LPCTSTR siteName, LPCTSTR dvrnsAddress, LPCTSTR dvrName, LPCTSTR userName, LPCTSTR userPassword, int dvrnsPort, bool isPasswordEncrypted = false, void* attachment = NULL);
IDIS_DLLFUNC bool IDISAPI audio_reconnect(IDISHAUDIO hAudio, LPCTSTR siteName, LPCTSTR siteAddress, LPCTSTR userName, LPCTSTR userPassword, int port, int channel, bool isPasswordEncrypted = false, void* attachment = NULL);
IDIS_DLLFUNC bool IDISAPI audio_reconnect_dvrns(IDISHAUDIO hAudio, LPCTSTR siteName, LPCTSTR dvrnsAddress, LPCTSTR dvrName, LPCTSTR userName, LPCTSTR userPassword, int dvrnsPort, short channel, bool isPasswordEncrypted = false, void* attachment = NULL);
IDIS_DLLFUNC void IDISAPI audio_disconnect(IDISHAUDIO hAudio, int channel);
IDIS_DLLFUNC bool IDISAPI audio_isConnecting(IDISHAUDIO hAudio, int channel);
IDIS_DLLFUNC bool IDISAPI audio_isConnected(IDISHAUDIO hAudio, int channel);

// audioSDK_get function //////////////////////////////////

IDIS_DLLFUNC bool IDISAPI audio_enableMic(IDISHAUDIO hAudio, int channel);
IDIS_DLLFUNC bool IDISAPI audio_disableMic(IDISHAUDIO hAudio, int channel);
IDIS_DLLFUNC bool IDISAPI audio_enableSpeaker(IDISHAUDIO hAudio, int channel);
IDIS_DLLFUNC bool IDISAPI audio_disableSpeaker(IDISHAUDIO hAudio, int channel);
IDIS_DLLFUNC bool IDISAPI audio_setAudioChannel(IDISHAUDIO hAudio, int channel, int audio_channel);

// audioSDK log ///////////////////////////////////////////

IDIS_DLLFUNC void IDISAPI audio_setLoggerProperties(unsigned char logType, unsigned char logLevel);

// User-specific data /////////////////////////////////////
IDIS_DLLFUNC bool  IDISAPI audio_setUserParamByHandle(IDISHAUDIO hAudio, void* pUserParam);
IDIS_DLLFUNC bool  IDISAPI audio_setUserParamByChannel(IDISHAUDIO hAudio, int channel, void* pUserParam);
IDIS_DLLFUNC void* IDISAPI audio_getUserParamByHandle(IDISHAUDIO hAudio);
IDIS_DLLFUNC void* IDISAPI audio_getUserParamByChannel(IDISHAUDIO hAudio, int channel);
/////////////////////////////////////////////////////////////////////////////
#pragma pack(push, 1)

typedef struct {
	enum _types {
		ONCONNECTED = 0,
		ONDISCONNECTED,
		ONSELECTEDAUDIOCHANNEL,
        ONSPEAKEROPENED,
        ONSPEAKERCLOSED,
        ONMICOPENED,
        ONMICCLOSED,
		MAX_LISTENER
	};
} CALLBACK_AUDIO;

#pragma pack(pop)
/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

/////////////////////////////////////////////////////////////////////////////

#endif	// !_IDIS_AUDIOSDK_INTERFACE_
