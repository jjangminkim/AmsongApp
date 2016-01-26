#ifndef _IDIS_STORAGE_SDK_H
#define _IDIS_STORAGE_SDK_H

#include "IDIS_Define.h"

#ifdef __cplusplus
extern "C" {
#endif

/////////////////////////////////////////////////////////////////////
// Constants (DO NOT EDIT THESE VALUES MANUALLY!!!)
const int MAX_EVENT_COUNT_PER_REQUEST   = 100;
const int MAX_TEXTIN_COUNT_PER_REQUEST  = 100;
const int MAX_GPSDATA_COUNT_PER_REQUEST = 100;

const int MAX_MONTH_LOADING_TIME  = 12 * 50;   // 50 years
const int MAX_DAY_LOADING_TIME    = 31 * 12;   // 1 year
const int MAX_HOUR_LOADING_TIME   = 24 * 7;    // 7 days
const int MAX_MINUTE_LOADING_TIME = 60 * 24;   // 1 day

/////////////////////////////////////////////////////////////////////
// Callback register
IDIS_DLLFUNC void IDISAPI storage_register_callback(IDISHSTORAGE hStorage, int type, LPLISTENER_FUNC func);

// Initialization and Termination functions
IDIS_DLLFUNC IDISHSTORAGE IDISAPI storage_initialize(void);
IDIS_DLLFUNC void IDISAPI storage_finalize(IDISHSTORAGE hStorage);
IDIS_DLLFUNC void IDISAPI storage_startup(IDISHSTORAGE hStorage);
IDIS_DLLFUNC void IDISAPI storage_cleanup(IDISHSTORAGE hStorage);

// Connection and Disconnection functions
IDIS_DLLFUNC bool IDISAPI storage_connect(IDISHSTORAGE hStorage, LPCTSTR deviceName);
IDIS_DLLFUNC bool IDISAPI storage_disconnect(IDISHSTORAGE hStorage);
IDIS_DLLFUNC bool IDISAPI storage_isConnected(IDISHSTORAGE hStorage);

// Open and Close functions
IDIS_DLLFUNC bool IDISAPI storage_open(IDISHSTORAGE hStorage, LPCTSTR filePath);
IDIS_DLLFUNC bool IDISAPI storage_close(IDISHSTORAGE hStorage);
IDIS_DLLFUNC bool IDISAPI storage_isOpened(IDISHSTORAGE hStorage);

// Request functions
IDIS_DLLFUNC bool IDISAPI storage_loadRecDates(IDISHSTORAGE hStorage);
IDIS_DLLFUNC bool IDISAPI storage_loadRecHours(IDISHSTORAGE hStorage, long* scope);
IDIS_DLLFUNC bool IDISAPI storage_loadRecTimes(IDISHSTORAGE hStorage, int resolution, int direction, long* scope);
IDIS_DLLFUNC bool IDISAPI storage_loadClipDataScope(IDISHSTORAGE hStorage);
IDIS_DLLFUNC bool IDISAPI storage_loadScopeList(IDISHSTORAGE hStorage, time_t begin, time_t end);
IDIS_DLLFUNC bool IDISAPI storage_loadSpotList(IDISHSTORAGE hStorage, time_t time);
IDIS_DLLFUNC bool IDISAPI storage_loadEventImage(IDISHSTORAGE hStorage, int selectedIndex);
IDIS_DLLFUNC bool IDISAPI storage_queryEvent(IDISHSTORAGE hStorage, long* condition, bool queryNext);
IDIS_DLLFUNC bool IDISAPI storage_queryTextIn(IDISHSTORAGE hStorage, long* condition, bool queryNext);
IDIS_DLLFUNC bool IDISAPI storage_queryGPSData(IDISHSTORAGE hStorage, long* condition, bool queryNext);

// Public functions
IDIS_DLLFUNC bool IDISAPI storage_setCameraList(IDISHSTORAGE hStorage, bool* cameras, int count, long* rollbackInfo);
IDIS_DLLFUNC bool IDISAPI storage_getCameraList(IDISHSTORAGE hStorage, bool* cameras);
IDIS_DLLFUNC int  IDISAPI storage_getCameraCount(IDISHSTORAGE hStorage);
IDIS_DLLFUNC bool IDISAPI storage_isSupport(IDISHSTORAGE hStorage, int supportType);

// Playback functions
IDIS_DLLFUNC bool IDISAPI storage_playback(IDISHSTORAGE hStorage, int command, long* spot);
IDIS_DLLFUNC void IDISAPI storage_stop(IDISHSTORAGE hStorage, long* rollbackInfo);
IDIS_DLLFUNC void IDISAPI storage_setPlayScope(IDISHSTORAGE hStorage, long* scope);
IDIS_DLLFUNC void IDISAPI storage_setPlayOption(IDISHSTORAGE hStorage, int optionType, int value);

// ClipCopy functions
IDIS_DLLFUNC bool IDISAPI storage_requestClipCopyScopeList(IDISHSTORAGE hStorage, time_t begin, time_t end, 
                                                       bool* cameras, int count);
IDIS_DLLFUNC bool IDISAPI storage_requestCancelClipCopy(IDISHSTORAGE hStorage);
IDIS_DLLFUNC bool IDISAPI storage_requestMeasureClipCopySize(IDISHSTORAGE hStorage, long* scope, unsigned int freeSize);
IDIS_DLLFUNC bool IDISAPI storage_requestClipCopySize(IDISHSTORAGE hStorage);
IDIS_DLLFUNC bool IDISAPI storage_requestClipCopy(IDISHSTORAGE hStorage, bool start);

// Device related functions
IDIS_DLLFUNC bool IDISAPI storage_loadDeviceList(IDISHSTORAGE hStorage);
IDIS_DLLFUNC bool IDISAPI storage_getRecordedDeviceInfo(IDISHSTORAGE hStorage, int deviceIndex);
IDIS_DLLFUNC bool IDISAPI storage_isRecordedDevice(IDISHSTORAGE hStorage, int deviceIndex);
IDIS_DLLFUNC bool IDISAPI strage_getStorageModelInfo(IDISHSTORAGE hStorage, LPBYTE info);

#pragma pack(push, 1)

/////////////////////////////////////////////////////////////////////
// HDP callbacks
struct CALLBACK_STORAGE {
    enum {
        ONCONNECTED = 0,
        ONDISCONNECTED,
        ONOPENED,
        ONCLOSED,
        ONRECORDEDDATELOADED,
        ONRECORDEDHOURLOADED,
        ONRECORDEDTIMELOADED,
        ONRECEIVECLIPDATASCOPE,
        ONRECEIVECLIPDATASCOPEEND,
        ONSCOPELISTLOADED,
        ONSPOTLISTLOADED,
        ONRECEIVEEVENTLOGLIST,
        ONRECEIVEEVENTLOG,
        ONRECEIVETEXTINLIST,
        ONRECEIVETEXTIN,
        ONRECEIVEGPSDATALIST,
        ONRECEIVEGPSDATA,
        ONFRAMELOADED,
        ONNOFRAMELOADED,
        ONENDOFPLAY,
        ONPLAYSPEEDCHANGED,
        ONRECEIVECLIPCOPYSCOPELIST,
        ONRECEIVECANCELCLIPCOPY,
        ONRECEIVEMEASURECLIPCOPYSIZE,
        ONRECEIVECLIPCOPYSIZE,
        ONRECEIVECLIPCOPY,
        ONRECEIVEDEVICELIST,
        ONRECEIVEDEVICEINFO,
        MAX_LISTENER
    };
};

/////////////////////////////////////////////////////////////////////
// Spot and scope structures
typedef struct {
    unsigned int _segmentId;   // segment index
    time_t       _time;        // time
    unsigned int _tick;        // msec
} SPOT_INFO;

typedef struct {
    SPOT_INFO _begin;   // begin spot
    SPOT_INFO _end;     // end spot
} SCOPE_INFO;

// Structures representing the results of storage_loadScope/SpotList()
typedef struct {
    SPOT_INFO*   _spot;    // spot list
    unsigned int _count;   // spot count
} PARAMS_SPOTLIST;

typedef struct {
    SCOPE_INFO*  _scope;   // scope list
    unsigned int _count;   // scope count
} PARAMS_SCOPELIST;

/////////////////////////////////////////////////////////////////////
// Structure representing the results of storage_loadRecDates()
typedef struct {		
    unsigned int _count;   // the number of recorded dates
    time_t*      _date;    // recorded date information
} PARAMS_DATELIST;

/////////////////////////////////////////////////////////////////////
// TimeHour structure
typedef struct {
    unsigned int _segmentId;   // segment index
    bool         _hour[24];    // the information of recorded hours
} TIMEHOUR;

// Structure representing the results of storage_loadRecHours()
typedef struct {
    unsigned int _count;   // timeHour count
    TIMEHOUR*    _hour;    // timeHour list
} PARAMS_TIMEHOURLIST;

/////////////////////////////////////////////////////////////////////
// RecTime structure
typedef struct {
    enum Resolution {
        MONTH = 0,
        DAY,
        HOUR,
        MINUTE,
    };
    enum RecType {
        TIME_LAPSE  = 0x01,
        EVENT       = 0x02,
        PRE_EVENT   = 0x04,
        PANIC       = 0x08,
    };
    SPOT_INFO       _spot;        // spot
    int             _resolution;  // resolution
    unsigned char** _recType;     // recType[cameraIndex][timeIndex]
} RECTIME;

// Structure representing the results of storage_loadRecTimes()
typedef struct {
    unsigned int _count;     // recTime count
    RECTIME*     _recTime;   // recTime list
} PARAMS_RECTIMELIST;

/////////////////////////////////////////////////////////////////////
// Event query condition structure
typedef struct {
    time_t _begin;
    time_t _end;
    bool   _alarmIn[MAX_SYS_CAMERA];
    bool   _motion[MAX_SYS_CAMERA];
    bool   _objectTracker[MAX_SYS_CAMERA];
    bool   _videoLoss[MAX_SYS_CAMERA];
    bool   _videoBlind[MAX_SYS_CAMERA];
    bool   _textIn[MAX_SYS_CAMERA];
    bool   _cameras[MAX_SYS_CAMERA];
    bool   _system[MAX_SYS_CAMERA];
    bool   _vehicle[MAX_SYS_CAMERA];
    bool   _network[MAX_SYS_CAMERA];
} EVENT_QUERY_CONDITION;

// Structures representing the results of storage_queryEvent()
typedef struct {	
    unsigned char _eventType;      // event type (Motion, Text-In, Alarm, Sensor)
    unsigned char _eventId;        // event id
    unsigned int  _recordCameras;  // cameras related with event
    SPOT_INFO     _spot;           // event generation spot
    char          _label[MAX_LEN_LOG_LABEL]; // event label
} PARAMS_LOGINFO;

typedef struct {
    unsigned int    _count;
    PARAMS_LOGINFO* _logInfo;
} PARAMS_LOGINFOLIST;

/////////////////////////////////////////////////////////////////////
// TextIn query condition structure
typedef struct {
    struct Item{
        bool _condition;    // 'AND' or 'OR'
        char _name[80];     // item name
        int  _comparator;   // '>', '>=', '=', '<=', '<'
        char _value[80];    // item value
        int  _column;       // column 
        int  _line;         // line
    };

    time_t _begin;           // end time
    time_t _end;             // begin time
    bool   _cameras[MAX_SYS_CAMERA]; // cameras
    bool   _caseSensitive;   // case sensitive
    int    _itemCount;       // item count
    Item   _item[5];         // item list
} TEXTIN_QUERY_CONDITION;

// Structures representing the results of storage_queryTextIn()
typedef struct {
    enum TransactionType {
        TRANSACTION_BEGIN,
        TRANSACTION_CONTINUE,
        TRANSACTION_END,
        TRANSACTION_COMPLETE,
    };

    unsigned char  _transactionType; // transaction type
    unsigned int   _recordCameras;   // the cameras related to TextIn
    unsigned int   _dataSize;        // TextIn data size
    unsigned char* _data;            // TextIn data
    SPOT_INFO      _spot;            // TextIn generation spot
} PARAMS_TEXTIN;

typedef struct {
    unsigned int   _count;    // TextIn count
    PARAMS_TEXTIN* _textIn;   // TextIn list
} PARAMS_TEXTINLIST;

/////////////////////////////////////////////////////////////////////
// GPS query condition structure
typedef struct {
    time_t _begin;   // begin time
    time_t _end;     // end time
} GPSDATA_QUERY_CONDITION;

// Structures representing the results of storage_queryGpsData()
typedef struct {
    unsigned int   _dataSize;   // data size
    unsigned char* _data;       // data
    SPOT_INFO      _spot;       // spot
} PARAMS_GPSDATA;

typedef struct {
    unsigned int    _count;     // gps data count
    PARAMS_GPSDATA* _gpsData;   // gps data list
} PARAMS_GPSDATALIST;

/////////////////////////////////////////////////////////////////////
// Support types
typedef struct {
    enum SupportType {
        MINUTE_SEARCH = 0,
        GPS_SEARCH,
    };
}SUPPORT_TYPE;

/////////////////////////////////////////////////////////////////////
// Playback types
typedef struct {
    enum PlaybackType {
        STOP = 0,   // stop
        PLAY,       // play
        REW,        // rewind
        FF,         // fast forward
        PREV,       // move to previous image
        NEXT,       // move to next image
        FIRST,      // move to first
        LAST,       // move to last
        GOTO_HOUR,  // move to specified spot with hour resolution
        GOTO_SEC,   // move to specified spot with second resolution
        GOTO_EVENT, // move to specified spot with event resolution
    };
} PLAYBACK_TYPE;

/////////////////////////////////////////////////////////////////////
// Play options
typedef struct {
    enum PlayOption {
        SYNC_TEXTIN = 0,   // playback with textIn
        SYNC_EVENTLOG,     // playback with eventLog
    };
} PLAY_OPTION;

/////////////////////////////////////////////////////////////////////
// Rollback info structure
typedef struct {
    SPOT_INFO _spot;          // last spot
    int       _cameraIndex;   // last camera index
} ROLLBACK_INFO;

/////////////////////////////////////////////////////////////////////
// Structure representing the results of storage_requestClipCopySize()
typedef struct {
    char         _completeStatus;	// status of clip-copy progress
    unsigned int _clipCopySize;		// clip-copy size
    time_t       _begin;            // begin time
    time_t       _end;              // end time
} PARAMS_CLIPCOPYSIZE;

// Structure representing the results of storage_requestClipCopy()
typedef struct {
    bool         _completed;   // completed(true) or not(false)
    unsigned int _progress;    // progress(0 ~ 100)
    unsigned int _count;       // data count
    unsigned int _length;      // data length
    char*        _data;        // clip-copy data
} PARAMS_CLIPCOPY;

/////////////////////////////////////////////////////////////////////
// Device info structure
typedef struct {
    enum DeviceType{
        DEVICE_INVALID = -1,  // invalid device
        DEVICE_TYPE_IDE = 0,  // IDE / SATA type device
        DEVICE_TYPE_USB,      // USB type device
    };

    int          _deviceIndex;      // physical device index
    unsigned int _deviceSize;       // device size(MB)
    char         _deviceType;       // device type
    char         _deviceName[256];  // device name
} DEVICE_INFO;

// Structure representing the results of storage_requestDeviceList()
typedef struct {
    DEVICE_INFO*  _info;    // device info list
    unsigned int  _count;   // device info count
} PARAMS_DEVICE_LIST;

// Structure representing the results of storage_requestDeviceInfo()
typedef struct {
    int    _deviceIndex;        // physical device index
    int    _usage;              // device usage (0 ~ 100)
    time_t _begin;              // begin time
    time_t _end;                // end time
    char   _productName[256];   // product name
} RECORDED_DEVICE_INFO;

// Storage information (number of cameras,, etc)
typedef struct {
    int     _numCamera;
    int     _audioCodec;
    int     _decodedAudioSize;
} STORAGE_MODEL_INFO;

/////////////////////////////////////////////////////////////////////
// Event types
enum EventType {
    EVENT_NONE = 0,
    EVENT_UNKNOWN = 0,

    // alarm-in
    EVENT_ALARM_IN_ON           = 1,
    EVENT_ALARM_IN_OFF,
    EVENT_ALARM_IN_BAD_ON,
    EVENT_ALARM_IN_BAD_OFF,

    // motion/object-tracking
    EVENT_MOTION_ON             = 10,
    EVENT_MOTION_OFF,
    EVENT_OBJECT_TRACK_ON,
    EVENT_OBJECT_TRACK_OFF,

    // video
    EVENT_VIDEO_INIT            = 20, 
    EVENT_VIDEO_LOSS_ON,
    EVENT_VIDEO_LOSS_OFF,
    EVENT_VIDEO_BLIND_ON,
    EVENT_VIDEO_BLIND_OFF,

    // text-in
    EVENT_TEXT_IN_ON            = 30,
    EVENT_TEXT_IN_OFF,

    // recorder
    EVENT_RECORDER_BAD_ON       = 40,
    EVENT_RECORDER_BAD_OFF,

    // storage
    EVENT_STORAGE_FULL_ON       = 50,
    EVENT_STORAGE_FULL_OFF,
    EVENT_STORAGE_ALMOST_FULL_ON,
    EVENT_STORAGE_ALMOST_FULL_OFF,

    // disk
    EVENT_DISK_BAD              = 60, 
    EVENT_DISK_TEMPERATURE_ON,
    EVENT_DISK_TEMPERATURE_OFF,
    EVENT_DISK_SMART_ON,
    EVENT_DISK_SMART_OFF,
    EVENT_DISK_CONFIG_CHANGE,        
    EVENT_DISK_ON,
    EVENT_DISK_OFF,

    // system
    EVENT_SYSTEM_ALIVE          = 70,
    EVENT_PANIC_ON,
    EVENT_PANIC_OFF,
    EVENT_DC_FAN_ERROR_ON,
    EVENT_DC_FAN_ERROR_OFF,
    EVENT_SYSTEM_BOOT_UP,          
    EVENT_SYSTEM_RESTART,          
    EVENT_SYSTEM_SHUTDOWN,         

    // sipass
    EVENT_SIPASS_REC_ON         = 80,
    EVENT_SIPASS_REC_OFF,

    // car (auto-mobile)
    EVENT_CAR_OVERSPEED_ON      = 90,
    EVENT_CAR_OVERSPEED_OFF,
    EVENT_CAR_SUDDEN_ACCELERATION,
    EVENT_CAR_SUDDEN_STOP,
    EVENT_CAR_STARTING_WITH_DOORS_OPEN,

    // network alarm
    EVENT_NETWORK_ALARM_ON      = 128,
    EVENT_NETWORK_ALARM_OFF,
    EVENT_COUNT
};

/////////////////////////////////////////////////////////////////////

#pragma pack(pop)

#ifdef __cplusplus
}
#endif

/////////////////////////////////////////////////////////////////////

#endif // _IDIS_STORAGE_SDK_H