// WatchSDK_Sample.h : header file
//

#ifndef _WATCHSDK_SAMPLE_H_
#define _WATCHSDK_SAMPLE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IDIS_WatchSDK.h"

//////////////////////////////////////////////////////////////////////////

class WatchSDK_Class
{
// Constructions
public:
	WatchSDK_Class(void);
	~WatchSDK_Class(void);

// Attributes
private:
	int _maxChannel;

// Operations
public:

	// watchSDK_object ////////////////////////////////////

	IDISHWATCH initialize(void);
	void finalize(IDISHWATCH hWatch);
	void startup(IDISHWATCH hWatch, int max_channel);
	void cleanup(IDISHWATCH hWatch);

	// watchSDK_connection ////////////////////////////////

	int  connect(IDISHWATCH hWatch, LPCTSTR siteName, LPCTSTR siteAddress, LPCTSTR userName, LPCTSTR userPassword, int port, void* attachment = NULL);
	bool reconnect(IDISHWATCH hWatch, LPCTSTR siteName, LPCTSTR siteAddress, LPCTSTR userName, LPCTSTR userPassword, int port, short channel, void* attachment = NULL);
	int  connect_dvrns(IDISHWATCH hWatch, LPCTSTR siteName, LPCTSTR dvrnsAddress, LPCTSTR dvrName, LPCTSTR userName, LPCTSTR userPassword, int dvrnsPort, void* attachment = NULL);
	bool reconnect_dvrns(IDISHWATCH hWatch, LPCTSTR siteName, LPCTSTR dvrnsAddress, LPCTSTR dvrName, LPCTSTR userName, LPCTSTR userPassword, int dvrnsPort, short channel, void* attachment);
	void disconnect(IDISHWATCH hWatch, int channel);
	bool isConnecting(IDISHWATCH hWatch, int channel);
	bool isConnected(IDISHWATCH hWatch, int channel);
	bool setCameraList(IDISHWATCH hWatch, int channel, const LPBYTE cameras, int length);
	void sendRequestCheck(IDISHWATCH hWatch, int channel);

    // watchSDK_audio function ////////////////////////////
    bool startupAudio(int maxChannel, HWND hwndFocus);
    void cleanupAudio();
    bool setAudioList(IDISHWATCH hWatch, int channel, const LPBYTE audios, int length);
    bool decodeAudioFrame(IDISHWATCH hWatch, int channel, const LPPARAMWS_FRAMEINFO frameInfo, LPBYTE decoded, int bufferSize, int* decodedLen, LPPARAMW_AUDIOINFO audioInfo = NULL);
    bool playAudioFrame(IDISHWATCH hWatch, int channel, LPPARAMWS_FRAMEINFO frameInfo);
    bool requestDeviceAudioOutOpen(IDISHWATCH hWatch, int channel, int deviceId = 0);
    bool requestDeviceAudioOutClose(IDISHWATCH hWatch, int channel, int deviceId = 0);
    bool enableMic(IDISHWATCH hWatch, int channel, bool enable);
    bool disableSpeaker(IDISHWATCH hWatch, int channel, int camera);
    bool sendCapturedAudio(IDISHWATCH hWatch, int channel, const LPPARAMW_AUDIOINFO capturedAudio);


	// watchSDK_get function //////////////////////////////

	bool needPtzAdvancedMenu(IDISHWATCH hWatch, int channel, int camera);
	bool needPtzPreset(IDISHWATCH hWatch, int channel, int camera);
	bool getPtzPreset(IDISHWATCH hWatch, int channel, LPBYTE lpPreset);
	bool getPtzPresetIDR(IDISHWATCH hWatch, int channel, LPBYTE lpPreset);
	bool getUsePTZ(IDISHWATCH hWatch, int channel, int camera);
	int  getUsePTZEx(IDISHWATCH hWatch, int channel, int camera);
	bool getStatus(IDISHWATCH hWatch, int channel, LPBYTE lpStatus);
	bool sendReqStatusIDR(IDISHWATCH hWatch, int channel);
	const char* getCameraTitleIDR(IDISHWATCH hWatch, int channel, int camera);

	// watchSDK_set function //////////////////////////////

	bool setColor(IDISHWATCH hWatch, int channel, int camera, int type, int value);
	bool setPtz(IDISHWATCH hWatch, int channel, LPBYTE lpCommand);
	bool setPtzPreset(IDISHWATCH hWatch, int channel, int camera, LPBYTE presets);
	bool setPtzPresetIDR(IDISHWATCH hWatch, int channel, int camera, LPBYTE presets);
	bool setAlarmOut(IDISHWATCH hWatch, int channel, int alarmid, bool fdevon);

	// watchSDK_chk function //////////////////////////////

	int  getCountAlarmOut(IDISHWATCH hWatch, int channel);
	int  checkAuthority(IDISHWATCH hWatch, int channel);
	bool isAuthorityCovertView(IDISHWATCH hWatch, int channel);
	bool isConnectedIDR(IDISHWATCH hWatch, int channel);
	bool isSupport(IDISHWATCH hWatch, int channel, int supportType);

	// watchSDK reg_callback //////////////////////////////

	void registerCallback(IDISHWATCH hWatch, int ntypes, LPLISTENER_FUNC lpFunc);

	// watchSDK_etc function //////////////////////////////

	bool sendNetworkAlarmOn(IDISHWATCH hWatch, int channel, LPBYTE pNetAlarmInfo);
	bool sendNetworkAlarmOff(IDISHWATCH hWatch, int channel, LPBYTE pNetAlarmInfo);
	bool requestStreamChannelControl(IDISHWATCH hWatch, int channel, int camera, int seqNumber, int bufflength, char* buffer);

    bool setUserParamByHandle(IDISHWATCH hWatch, void* pUserParam);
    bool setUserParamByChannel(IDISHWATCH hWatch, int channel, void* pUserParam);
    void* getUserParamByHandle(IDISHWATCH hWatch);
    void* getUserParamByChannel(IDISHWATCH hWatch, int channel);
    int getCountAvailableHandle(void);
    int getCountAvailableChannel(IDISHWATCH hWatch);

    bool getProductInfo(IDISHWATCH hWatch, int channel, int queryType, void* target, unsigned int targetSize);

    // watchSDK log
    void setLoggerProperties(unsigned char logType, unsigned char logLevel);

// Utility
public:
	bool isValidChannel(int channel) const;
	LPCTSTR getReasonDisconnected(int reason) const;
};

//////////////////////////////////////////////////////////////////////////

inline bool WatchSDK_Class::isValidChannel(int channel) const
{
	return (channel < 0 ||
			channel >= _maxChannel) ? false : true;
}

//////////////////////////////////////////////////////////////////////////

#endif	// !_WATCHSDK_SAMPLE_H_
