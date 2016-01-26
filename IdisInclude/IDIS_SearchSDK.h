// IDIS_SearchSDK.h : header file
//

#ifndef _IDIS_SEARCHSDK_INTERFACE_
#define _IDIS_SEARCHSDK_INTERFACE_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IDIS_Define.h"

#ifdef __cplusplus
extern "C" {
#endif

/////////////////////////////////////////////////////////////////////

const int MAX_TRANS_NUM                 = 16;
const int MAX_PLUS_ALARM_IN_COUNT       = 16;       // max. number of alarm_in per channel

const int MAX_LEN_DESCRIPTION           = 31;
const int MAX_LEN_CAMERA_TITLE          = 31;

const int MAX_ALARMOUT_BUTTONS_EX       = 32;

const int MAX_CAMERA			        = 16;

const int MAX_TIME_SEGMENT_COUNT        = 100;
const int MAX_EVENT_COUNT_PER_REQUEST   = 100;
const int MAX_CLIP_COPY_SCOPE_COUNT     = 100;

//////////////////////////////////////////////////////////////////////////

// searchsdk_callback_func types
// reference below CALLBACK_SEARCH struct for ntypes
IDIS_DLLFUNC void IDISAPI search_register_callback(IDISHSEARCH hSearch, int ntypes, LPLISTENER_FUNC lpFunc);

// Initialization and Termination
IDIS_DLLFUNC IDISHSEARCH IDISAPI search_initialize(void);
IDIS_DLLFUNC void IDISAPI search_finalize(IDISHSEARCH hSearch);
IDIS_DLLFUNC void IDISAPI search_startup(IDISHSEARCH hSearch, int maxChannels);
IDIS_DLLFUNC void IDISAPI search_cleanup(IDISHSEARCH hSearch);

// User-specific data
IDIS_DLLFUNC bool  IDISAPI search_setUserParamByHandle(IDISHSEARCH hSearch, void* pUserParam);
IDIS_DLLFUNC bool  IDISAPI search_setUserParamByChannel(IDISHSEARCH hSearch, int channel, void* pUserParam);
IDIS_DLLFUNC void* IDISAPI search_getUserParamByHandle(IDISHSEARCH hSearch);
IDIS_DLLFUNC void* IDISAPI search_getUserParamByChannel(IDISHSEARCH hSearch, int channel);

// Connection and Disconnection
IDIS_DLLFUNC int  IDISAPI search_connect(IDISHSEARCH hSearch, LPCTSTR siteName, LPCTSTR siteAddress, LPCTSTR userName, LPCTSTR sitePassword, int port, bool isPasswordEncrypted = false, void* attachment = NULL, bool isPortUnity = false);
IDIS_DLLFUNC int  IDISAPI search_connect_dvrns(IDISHSEARCH hSearch, LPCTSTR siteName, LPCTSTR dvrnsAddress, LPCTSTR dvrName, LPCTSTR userName, LPCTSTR userPassword, int dvrnsPort, bool isPasswordEncrypted = false, void* attachment = NULL, bool isPortUnity = false);
IDIS_DLLFUNC int  IDISAPI search_connect_connectService(IDISHSEARCH hSearch, LPCTSTR siteName, LPCTSTR dvrName, LPCTSTR gatewayAddress, int gatewayPort, int proxyPort, LPCTSTR userName, LPCTSTR userPassword, int natType, void* attachment = NULL, bool isPortUnity = false);


IDIS_DLLFUNC void IDISAPI search_disconnect(IDISHSEARCH hSearch, int channel);
IDIS_DLLFUNC bool IDISAPI search_isConnecting(IDISHSEARCH hSearch, int channel);
IDIS_DLLFUNC bool IDISAPI search_isConnected(IDISHSEARCH hSearch, int channel);

// Product Version Function
IDIS_DLLFUNC int IDISAPI search_getProductId(IDISHSEARCH hSearch, int channel);
IDIS_DLLFUNC int IDISAPI search_getMajorVersion(IDISHSEARCH hSearch, int channel);
IDIS_DLLFUNC int IDISAPI search_getMinorVersion(IDISHSEARCH hSearch, int channel);
IDIS_DLLFUNC int IDISAPI search_getCameraCount(IDISHSEARCH hSearch, int channel);

// load Time, date, segment, searchMode Function
IDIS_DLLFUNC bool IDISAPI search_loadRecDates(IDISHSEARCH hSearch, int channel);
IDIS_DLLFUNC bool IDISAPI search_loadRecTimes(IDISHSEARCH hSearch, int channel, SDK_TIME_T date);
IDIS_DLLFUNC bool IDISAPI search_changeSegment(IDISHSEARCH hSearch, int channel, int id);
IDIS_DLLFUNC bool IDISAPI search_changeSearchMode(IDISHSEARCH hSearch,int channel, bool mode);

// Playback
IDIS_DLLFUNC bool IDISAPI search_playback(IDISHSEARCH hSearch, int channel, int command, SDK_TIME_T time);
IDIS_DLLFUNC bool IDISAPI search_stop(IDISHSEARCH hSearch, int channel, SDK_TIME_T time, int msec, int cameraId);

// EventSearch Function
IDIS_DLLFUNC bool IDISAPI search_queryEvent(IDISHSEARCH hSearch, int channel, const LPBYTE condition, bool queryNext);
IDIS_DLLFUNC bool IDISAPI search_queryTextIn(IDISHSEARCH hSearch, int channel, const LPBYTE condition, bool queryNext);
IDIS_DLLFUNC bool IDISAPI search_idrEventSearchStop(IDISHSEARCH hSearch, int channel);
IDIS_DLLFUNC bool IDISAPI search_loadEventImage(IDISHSEARCH hSearch, int channel, int selected, bool isLast);

// Public
IDIS_DLLFUNC bool IDISAPI search_isSupport(IDISHSEARCH hSearch, int channel, int support);
IDIS_DLLFUNC bool IDISAPI search_setCameraList(IDISHSEARCH hSearch, int channel, const bool* cameras, int length, LPPARAMS_SPOT lastDisplayedSpot, LPPARAMS_SPOT lastSpot);
IDIS_DLLFUNC bool IDISAPI search_getCameraList(IDISHSEARCH hSearch, int channel, bool* cameras);

// Minibank
IDIS_DLLFUNC bool IDISAPI search_export2Minibank(IDISHSEARCH hSearch, int channel, int cameraId, const SDK_TIME_T& from, const SDK_TIME_T& to, bool audio, LPCTSTR fileName);
IDIS_DLLFUNC bool IDISAPI search_requestCancelMinibank(IDISHSEARCH hSearch, int channel);

// ClipCopy
IDIS_DLLFUNC bool IDISAPI search_requestGetEnableClipCopyChannel(IDISHSEARCH hSearch, int channel);
IDIS_DLLFUNC bool IDISAPI search_export2ClipCopy(IDISHSEARCH hSearch, int channel, LPCTSTR fileName, const SDK_TIME_T& from, const SDK_TIME_T& to, const bool* cameras, bool usePassword, LPCTSTR password);
IDIS_DLLFUNC bool IDISAPI search_exportToClipCopy(IDISHSEARCH hSearch, int channel, LPCTSTR fileName, const SDK_TIME_T& from, const SDK_TIME_T& to, const bool* cameras, int length, bool usePassword, LPCTSTR password, bool includeTextIn = false, bool excludePlayer = false, bool includeGpsData = false, bool includeEvent = false);
IDIS_DLLFUNC bool IDISAPI search_addClipUserData(IDISHSEARCH hSearch, int channel, LPCTSTR key, LPCTSTR value);
IDIS_DLLFUNC void IDISAPI search_beginAddClipUserData(IDISHSEARCH hSearch, int channel);
IDIS_DLLFUNC void IDISAPI search_endAddClipUserData(IDISHSEARCH hSearch, int channel);

#if defined(_WIN32)
IDIS_DLLFUNC bool IDISAPI search_requestMeasureClipCopySize(IDISHSEARCH hSearch, int channel, const LPBYTE scopeInfo);
#else
IDIS_DLLFUNC bool IDISAPI search_requestMeasureClipCopySize(IDISHSEARCH hSearch, int channel, const LPBYTE scopeInfo, int freespace);
#endif
IDIS_DLLFUNC bool IDISAPI search_requestClipCopySize(IDISHSEARCH hSearch, int channel);
IDIS_DLLFUNC bool IDISAPI search_requestCancelClipCopy(IDISHSEARCH hSearch, int channel);
IDIS_DLLFUNC bool IDISAPI search_setClipCopyNotCompletedTimeout(IDISHSEARCH hSearch, int channel, unsigned int notCompletedTimeoutMs);
IDIS_DLLFUNC bool IDISAPI search_requestClipCopyScopeList(IDISHSEARCH hSearch, int channel, const SDK_TIME_T& from, const SDK_TIME_T& to, const bool* cameras, int length);

// GPS
IDIS_DLLFUNC bool IDISAPI search_requestMeasureGpsData(IDISHSEARCH hSearch, int channel, const SDK_TIME_T& start, const SDK_TIME_T& end);
IDIS_DLLFUNC bool IDISAPI search_requestMeasureGpsDataResult(IDISHSEARCH hSearch, int channel);
IDIS_DLLFUNC bool IDISAPI search_requestGpsDataNext(IDISHSEARCH hSearch, int channel);
IDIS_DLLFUNC bool IDISAPI search_requestGpsExportCancel(IDISHSEARCH hSearch, int channel);
IDIS_DLLFUNC bool IDISAPI search_requestGpsLocationSearch(IDISHSEARCH hSearch, int channel, const LPBYTE pCondition);

// ClipCopy Archive Function
IDIS_DLLFUNC bool IDISAPI search_requestListClipCopyArchive(IDISHSEARCH hSearch, int channel);
IDIS_DLLFUNC bool IDISAPI search_requestCreateClipCopyArchive(IDISHSEARCH hSearch, int channel, LPCTSTR fileName, LPCTSTR description, const bool* cameras, int length, const LPBYTE scopeInfo);
IDIS_DLLFUNC bool IDISAPI search_requestDeleteClipCopyArchive(IDISHSEARCH hSearch, int channel, LPCTSTR fileName);
IDIS_DLLFUNC bool IDISAPI search_requestClipCopyArchiveData(IDISHSEARCH hSearch, int channel, const LPBYTE fileNameList);
IDIS_DLLFUNC bool IDISAPI search_requestCancelClipCopyArchive(IDISHSEARCH, int channel);
IDIS_DLLFUNC bool IDISAPI search_requestContinueClipCopyArchive(IDISHSEARCH hSearch, int channel);

// Overwrite Protection 
IDIS_DLLFUNC bool IDISAPI search_requestAddOverwriteProtection(IDISHSEARCH hSearch, int channel, const bool* cameras, int length, const LPBYTE scopeInfo);
IDIS_DLLFUNC bool IDISAPI search_requestRemoveOverwriteProtection(IDISHSEARCH hSearch, int channel, const bool* cameras, int length, const LPBYTE scopeInfo);
IDIS_DLLFUNC bool IDISAPI search_requestOverwriteProtectionList(IDISHSEARCH hSearch, int channel);

// etc
IDIS_DLLFUNC bool IDISAPI search_getProductInfo(IDISHSEARCH hSearch, int channel, int queryType, void* target, unsigned int targetSize);
IDIS_DLLFUNC void IDISAPI search_setLoggerProperties(const unsigned char loggerType, const unsigned char loggerLevel);
IDIS_DLLFUNC int IDISAPI search_getFrameDataOffset(IDISHSEARCH hSearch, int channel, void* videoData);
IDIS_DLLFUNC int IDISAPI search_getCountAvailableHandle(void);
IDIS_DLLFUNC int IDISAPI search_getCountAvailableChannel(IDISHSEARCH hSearch);

// to prevent disconnection due to idle time, send dummy packet.
IDIS_DLLFUNC void IDISAPI search_sendRequestCheck(IDISHSEARCH hSearch, int channel);



//////////////////////////////////////////////////////////////////////////
#pragma pack(push, 1)


typedef struct {
    enum _types {
        ONCONNECTEDSEARCH = 0,
        ONDISCONNECTEDSEARCH,
        ONRECORDEDDATELOADED,
        ONRECORDEDTIMEHOURLOADED,
        ONRECORDEDTIMEMINUTELOADED,
        FRAMELOADED,
        NOFRAMELOADED,
        ONCHANGEDSEARCHMODE,
        ONRECEIVEEVENTQUERYRESULT,
        PLAYSPEEDCHANGED,
        ONCHANGEDSEGMENT,
        ONRECEIVECLIPCOPYSCOPELIST,
        ONRECEIVECANCELCLIPCOPY,
        ONRECEIVEMEASURECLIPCOPYSIZE,
        ONRECEIVECLIPCOPYSIZE,
        ONRECEIVECLIPCOPY,
        ONRECEIVEGETENABLECLIPCOPYCHANNEL,

        MINIBANKPROGRESS,
        FINDINGIDREVENTTIME,

        ONRECEIVETEXTINQUERYRESULT,
        ONRECEIVETEXTIN,
        ONRECEIVEGPSDATA,
        ONRECEIVEGPSDATABYGPSEVENT,
        ONRECEIVEGPSDATALIST,
        ONRECEIVEGPSDATALISTBYGPSEVENT,
        ONRECEIVEMEASUREGPSDATARESULT,
        ONRECEIVEGPSEXPORTCANCELRESULT,
        ONRECEIVEGPSLOCATIONSEARCHRESULT,
        ONRECEIVEG2GPSLOCATIONSEARCHRESULT,
        ONRECEIVECREATECLIPCOPYARCHIVERESULT,
        ONRECEIVEDELETECLIPCOPYARCHIVERESULT,
        ONRECEIVELISTCLIPCOPYARCHIVE,
        ONRECEIVECLIPCOPYARCHIVEDATA,
        ONRECEIVECLIPCOPYARCHIVEDATAERROR,
        ONRECEIVECANCELCLIPCOPYARCHIVE,
        ONRECEIVECLIPCOPYARCHIVEMEASURESIZERESULT,
        ONRECEIVEOVERWRITEPROTECTIONLIST,
        MAX_LISTENER
    };
} CALLBACK_SEARCH;

typedef struct {
    enum _types {
        USE_SAMBA_SEARCH = 0,
        USE_CLIPPLAYER,
        USE_MINIBANK,
        HAVE_CLIPCOPY_AUTH,
        CLIPCOPY_AVAIL_CHANNEL,
        USE_G2_SEARCH,
    };
} SUPPORT_TYPE;

typedef struct {
    enum _types {
        NOT_COMPLETED = -1,
        NOT_ENOUGH_SPACE,
        PARTIAL_COPIABLE,
        FULL_COPIABLE,
        NO_RECORDED_DATA,
    };
} CLIPCOPY_STATUS;

enum SEARCHMODE {
    TIME_LAPSE_SEARCH = 0,
    EVENT_SEARCH,
};

enum TIMELAPSEMODE {
    TIME_HOUR_SEARCH = 0,
    TIME_MINUTE_SEARCH,
};

typedef struct {
    enum _types {
        ERRORCODE_NO_ERROR = 0,
        ERRORCODE_FILE_NOT_FOUND,
        ERRORCODE_FILE_ALREADY_EXIST,
        ERRORCODE_NOT_ENOUGH_SPACE,
        ERRORCODE_BROKEN_FILE,
        ERRORCODE_INVALID_PARAMETER,
        ERRORCODE_ACCESS_VIOLATION,
    };
} CLIPCOPY_ARCHIVE_ERROR_CODE;

typedef struct {
    enum _status {
            MEASURE_SIZE_PARTIAL_COPIABLE = 1,
            MEASURE_SIZE_FULL_COPIABLE,
            MEASURE_SIZE_NO_RECORDED_DATA,
    };
} CLIPCOPY_ARCHIVE_MEASURESIZE_RESULT;

typedef struct {		
    UINT32 _length;             // the number of recorded date
    DWORD* _dates;              // recorded date information			
} PARAMS_DATE, *LPPARAMS_DATE;

typedef struct {
    UINT32 _segCount;           // the number of recorded time
    BYTE*  _hour;               // recorded time information		
} PARAMS_TIMEHOUR, *LPPARAMS_TIMEHOUR;

typedef struct {	
    BYTE* _minute;              // recorded time information		
} PARAMS_TIMEMINUTE, *LPPARAMS_TIMEMINUTE;

typedef struct {
    int     seqNum;
    SDK_TIME_T  begin;
    SDK_TIME_T  end;
    bool    alarmIn[MAX_SYS_CAMERA32];
    bool    motion[MAX_SYS_CAMERA32];
    bool    objectTracker[MAX_SYS_CAMERA32];
    bool    videoLoss[MAX_SYS_CAMERA32];
    bool    videoBlind[MAX_SYS_CAMERA32];
    bool    textIn[MAX_SYS_CAMERA32];
    bool    cameras[MAX_SYS_CAMERA32];
    bool    system[MAX_SYS_CAMERA32];
    bool    reload;
    int     alarmDwellTime;
    int     motionDwellTime;
    int     objectDwellTime;
} EVENT_QUERY_CONDITION, *LPEVENT_QUERY_CONDITION;

typedef struct {
    struct Item {
        int  condition;
        char name[80];
        int  comparator;
        char value[80];
        int  column;
        int  line;

        Item()
        {
            reset();
        }

        void reset()
        {
            condition   = 0;
            comparator  = 0;
            column      = 0;
            line        = 0;
            memset(name, 0, sizeof(name));
            memset(value, 0, sizeof(value));
        }
    };

    bool    reload;
    SDK_TIME_T  from;
    SDK_TIME_T  to;
    bool    channel[MAX_SYS_CAMERA32];
    short   dataType;
    int     caseSensitive;
    int     itemCount;
    Item    item[5];
} TEXTIN_QUERY_CONDITION, *LPTEXTIN_QUERY_CONDITION;

typedef struct {
    bool reload;
    SDK_TIME_T from;
    SDK_TIME_T to;
    float easternBoundary;
    float westernBoundary;
    float southernBoundary;
    float northernBoundary;
} GPS_LOCATION_SEARCH_CONDITION, *LPGPS_LOCATION_SEARCH_CONDITION;

typedef struct {
    enum _type_disk { // for disk-related event
        DISK_TYPE_UNKNOWN = 0,
        DISK_TYPE_IDE_HDD,
        DISK_TYPE_SCSI_HDD,
        DISK_TYPE_USB_HDD,
        DISK_TYPE_IDE_CDRW,
        DISK_TYPE_IDE_DVDRW,
        DISK_TYPE_SW_RAID_DISK,
        DISK_TYPE_FLASH_MEMORY,
        DISK_TYPE_ESATA_HDD,
        DISK_TYPE_ISCSI_HDD
    };

    int                 _seqNum;                    // the number stored in log
    char                _version[2];                // version information
    char                _eventType;                 // alarm type (Motion, Text-In, Alarm, Sensor)
    char                _eventId;                   // alarm id
    SDK_TIME_T          _time;                      // event generation time
    int                 _msec;                      // event generation msec
    unsigned int        _camId;                     // camera related with event
    unsigned short int  _preDwell[MAX_CAMERA];      // Previous alarm dwell time(second)
    unsigned short int  _postDwell[MAX_CAMERA];     // Post alarm dwell time(second) (16*2)
    char                _label[MAX_LEN_LOG_LABEL];  // alarm label
    char                _transNum[MAX_TRANS_NUM+1]; // transaction number (16)
    char                _level;                     // event level(urgent event,normal event)
    char                _reserved[2];               // reserved

    int camId2IntBasedZero() {
        for (int i = 0; i < MAX_CAMERA; i++) {
            if (_camId & (1 << i)) {
                return i;
            }
        }
        return -1;
    }
} PARAMS_LOGINFO, *LPPARAMS_LOGINFO;

typedef struct {
    enum STATUS{
        NONE = -1,
        PROGRESS,
        COMPLETED,
        CANCELED,
        NO_RECORDED_DATA,
        TOO_BIG_FILE,
        INSUFFCIENT_SPACE,
        FILE_OPEN_FAIL,
    };

    STATUS  _status;
    int     _progress;
} PARAMS_MINIBANK_PROGRESS, *LPPARAM_MINIBANK_PROGRESS;

typedef struct {
    unsigned int _beginSegmentId;
    SDK_TIME_T   _beginTime;
    unsigned int _beginTick;
    unsigned int _endSegmentId;
    SDK_TIME_T   _endTime;
    unsigned int _endTick;
} SCOPEINFO, *LPSCOPEINFO;

typedef struct {
    LPSCOPEINFO _scopeInfo;
    int         _count;
} PARAMS_SCOPELIST, *LPPARAMS_SCOPELIST;

typedef struct {
    char    _completeStatus;    // status of clip-copy progress
    int     _clipCopySize;      // clip-copy size
    SDK_TIME_T  _begin;
    SDK_TIME_T  _end;
} PARAMS_CLIPCOPYSIZE, *LPPARAMS_CLIPCOPYSIZE;

typedef struct {
    bool _completed;
    int _progress; 
} PARAMS_CLIPCOPY, *LPPARAMS_CLIPCOPY;

typedef struct {
    char _channels[MAX_SYS_CAMERA32];
} PARAMS_CLIPCOPYCHANNEL, *LPPARAMS_CLIPCOPYCHANNEL;

typedef struct {
    UINT16  _camera;
    BYTE    _fstart;
    BYTE    _dummy;
} PARAMS_IDRTEXTIN, *LPPARAMS_IDRTEXTIN;

typedef struct {
    enum _type_transaction {
        TRANSACTION_BEGIN,
        TRANSACTION_CONTINUE,
        TRANSACTION_END,
        TRANSACTION_COMPLETE,
    };

    UINT32  _camera;
    BYTE    _type;
    UINT32  _length;
    LPCTSTR _lpData;
    SDK_TIME_T  _time;

    int camId2IntBasedZero() {
        for (int i = 0; i < MAX_CAMERA; i++) {
            if (_camera & (1 << i)) {
                return i;
            }
        }
        return -1;
    }
} PARAMS_TEXTINDATA, *LPPARAMS_TEXTINDATA;

typedef struct {
    float _latitude;
    float _longitude;
    float _speed;
    float _angle;
    SDK_TIME_T _time;
    LPCTSTR _gpsData;
} PARAMS_GPSDATA, *LPPARAMS_GPSDATA;

typedef struct {
    int _count;
    LPPARAMS_GPSDATA _lpG2GpsData;
} PARAMS_GPSDATALIST, *LPPARAMS_GPSDATALIST;
typedef struct {
    int _count;
    LPPARAMS_TEXTINDATA _lpTextInData;
} PARAMS_TEXTINLIST, *LPPARAMS_TEXTINLIST;

typedef struct {
    int  _loadedCount;
    char _done;
} PARAMS_MEASUREGPSDATA, *LPPARAMS_MEASUREGPSDATA;

typedef struct {
    LPCTSTR _fileName;
} PARAMS_FILENAME, *LPPARAMS_FILENAME;

typedef struct {
    LPPARAMS_FILENAME _lpFileName;
    int _count;
} PARAMS_FILENAMELIST, *LPPARAMS_FILENAMELIST;

typedef struct {
    LPCTSTR _fileName;
    unsigned long long _fileSize;
    SDK_TIME_T _createdTime;
    LPCTSTR _description;
    char _channels[MAX_SYS_CAMERA32]; 
    SCOPEINFO _scopeInfo;
} PARAMS_FILEINFOCLIPCOPY, *LPPARAM_FILEINFOCLIPCOPY;

typedef struct {
    LPPARAM_FILEINFOCLIPCOPY _fileInfoClipCopyList;
    int _count;
} PARAMS_FILEINFOCLIPCOPYLIST, *LPPARAM_FILEINFOCLIPCOPYLIST;

typedef struct {
    LPCTSTR fileName;
    unsigned long long fileSize;
    unsigned long long offset;
    unsigned int size;
    LPBYTE  data;
} PARAMS_CLIPCOPYARCHIVE, *LPPARAMS_CLIPCOPYARCHIVE;

typedef struct {
    SCOPEINFO _scopeInfo;
    unsigned long long _fileSize;
} PARAMS_CLIPCOPYARCHIVEMEASURERESULT, *LPPARAMS_CLIPCOPYARCHIVEMEASURERESULT;

typedef struct {
    LPPARAMS_CLIPCOPYARCHIVEMEASURERESULT _measureResult;
    int _count;
    int _status; //CLIPCOPY_ARCHIVE_MEASURESIZE_RESULT::_status
} PARAMS_CLIPCOPYARCHIVEMEASURERESULTLIST, *LPPARAMS_CLIPCOPYARCHIVEMEASURERESULTLIST;

typedef struct {
    bool    _channel[MAX_SYS_CAMERA32];
    SCOPEINFO _scopeInfo;
} PARAMS_OVERWRITEPROTECTION, *LPPARAMS_OVERWRITEPROTECTION;

typedef struct {
    LPPARAMS_OVERWRITEPROTECTION _overwriteProtection;
    int _count;
} PARAMS_OVERWRITEPROTECTIONLIST, *LPPARAMS_OVERWRITEPROTECTIONLIST;

typedef struct {
    PARAMS_TEXTINDATA _previousGpsData;
    PARAMS_TEXTINDATA _gpsData;
} PARAMS_PAIR_TEXTINDATA, *LPPARAMS_PAIR_TEXTINDATA;

typedef struct {
    LPPARAMS_PAIR_TEXTINDATA _lpPairTextInData;
    int _count;
} PARAMS_PAIR_TEXTINDATALIST, *LPPARAMS_PAIR_TEXTINDATALIST;

typedef struct {
    PARAMS_GPSDATA _previousGpsData;
    PARAMS_GPSDATA _gpsData;
} PARAMS_PAIR_GPSDATA, *LPPARAMS_PAIR_GPSDATA;

typedef struct {
    LPPARAMS_PAIR_GPSDATA _lpPairGpsData;
    int _count;
} PARAMS_PAIR_GPSDATALIST, *LPPARAMS_PAIR_GPSDATALIST;

typedef struct {
    enum _types {
        STOP = 0,
        PLAY,
        REW,
        FF,
        PREV,
        NEXT,
        FIRST,
        LAST,
        GOTO_HOUR,
        GOTO_SEC,
        GOTO_MSEC,
        AUDIO_NEXT,
        AUDIO_GOTO_SEC,
        AUDIO_GOTO_MSEC,
        TEXT_GOTO_SEC,
        TEXT_NEXT,
        GOTO_EVENT,
    };
} PLAYBACK_TYPE;

typedef struct {
    enum _types {
        ADR1H = 0,
        ADR4H,
        ADR9H,
        ADR16H,
        IDR,
        SDR4,
        XDR,
        LUNA,
        JUNO,
        HERA
    };
} PRODUCT_ID;

#pragma pack(pop)
/////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

/////////////////////////////////////////////////////////////////////

#endif  // !_IDIS_SEARCHSDK_INTERFACE_
