// IDIS_AdminDK.h : header file
//

#ifndef _IDIS_ADMINSDK_INTERFACE_
#define _IDIS_ADMINSDK_INTERFACE_

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


#ifdef __cplusplus
extern "C" {
#endif

/////////////////////////////////////////////////////////////////////////////

const int MAX_NUM_UNITS                 = 16;
const int MAX_NUM_CAMERA_32             = 32;
const int MAX_NUM_AUDIO_16              = 16;
const int MAX_LEN_LOG_DATA              = 20;
const int MAX_LEN_LOG_DATA_EX           = 32;
const int MAX_SYSTEM_LOG                = 100;
const int MAX_EVENT_LOG                 = 100;
const int MAX_SYSTEM_LOG_SEND           = 25;
const int MAX_TEXT_IN_DATA_LENGTH       = 64;

const int MAX_DVRNS_DVR_NAME_LENGTH     = 63;
const int MAX_DVRNS_SERVER_LENGTH       = 63;
const int MAX_DVRNS_DVR_DESC_LENGTH     = 63;
const int MAX_DVRNS_DVR_DB_DESC_LENGTH  = 255;
const int MAX_DVRNS_HELP_PHONE_LENGTH   = 63;
const int MAX_DVRNS_HELP_EMAIL_LENGTH   = 63;
const int MAX_DVRNS_PORT_COUNT          = 16;
const int MAX_DVRNS_LOG_DATA_LENGTH     = 255;
const int MAX_DVRNS_RECORD_COUNT        = 100000;
const int MAX_DVRNS_LOG_COUNT           = 50000;

const int MAX_CAMERA_TITLE_LEN          = 31;
const int MAX_SITE_NAME_LEN             = 31;

// for remote configuration..
const unsigned int EVENT_NOTIFY_MAIL       = 0;
const unsigned int EVENT_NOTIFY_CALLBACK_1 = 1;
const unsigned int EVENT_NOTIFY_CALLBACK_2 = 2;
const unsigned int EVENT_NOTIFY_CALLBACK_3 = 3;
const unsigned int EVENT_NOTIFY_CALLBACK_4 = 4;
const unsigned int EVENT_NOTIFY_CALLBACK_5 = 5;
const unsigned int EVENT_NOTIFY_ALERT_WND  = 6;
const unsigned int EVENT_NOTIFY_COUNT      = 7;

const unsigned int MAX_ALARM_IN_COUNT   = 32;
const unsigned int MAX_TEXT_IN_COUNT    = 32;
const unsigned int MAX_ALARM_OUT_COUNT  = 32;
const unsigned int MAX_SYS_EVENT_COUNT  = 32;
const unsigned int MAX_SPOT             = 32;
const unsigned int MAX_PTZ_PRESET       = 32;
const unsigned int MAX_USER_GROUP     = 64;
const unsigned int MAX_USER           = 256;
const unsigned int MAX_GROUP_USER_LEN = 15;
const unsigned int MAX_PASSWORD_LEN   = 8;
const unsigned int USER_MODIFY_TYPE_ADD     = 1;
const unsigned int USER_MODIFY_TYPE_MODIFY  = 2;
const unsigned int USER_MODIFY_TYPE_REMOVE  = 3;

const unsigned char TYPE_PRODUCTINFO    = 1;    // Not used in IDIS_AdminSDK
const unsigned char TYPE_DUMMY          = 2;    // Not used in IDIS_AdminSDK
const unsigned char TYPE_SYSTEM         = 3;
const unsigned char TYPE_CAMERA         = 4;
const unsigned char TYPE_NETWORK        = 5;
const unsigned char TYPE_USER           = 6;
const unsigned char TYPE_NOT_USED       = 7;    // Not used yet.
const unsigned char TYPE_AUDIO          = 8;
const unsigned char TYPE_ALARMOUT       = 9;
const unsigned char TYPE_DISPLAY        = 10;
const unsigned char TYPE_REMOTE_CONTROL = 11;
const unsigned char TYPE_RECORDING      = 12;
const unsigned char TYPE_EVENT          = 13;
const unsigned char TYPE_VIDEO          = 14;   // for IP-cameras
const unsigned char TYPE_MAX            = 15;

const unsigned char SUB_TYPE_NET_COMMON             = 1;    // Network subtypes
const unsigned char SUB_TYPE_NET_LAN                = 2;
const unsigned char SUB_TYPE_NET_MODEM              = 3;
const unsigned char SUB_TYPE_NET_DVRNS              = 4;
const unsigned char SUB_TYPE_NET_WEBGUARD           = 5;
const unsigned char SUB_TYPE_NET_CALLBACKSERVER     = 6;
const unsigned char SUB_TYPE_NET_DDNS               = 7;
const unsigned char SUB_TYPE_NET_DASHBOARD          = 8;
const unsigned char SUB_TYPE_NET_RTSP               = 9;
const unsigned char SUB_TYPE_NET_IP_FILTERING       = 10;
const unsigned char SUB_TYPE_NET_ONVIF              = 11;
const unsigned char SUB_TYPE_NET_IEEE_802_1X        = 12;
const unsigned char SUB_TYPE_NET_UPGRADE_SERVER     = 13;
const unsigned char SUB_TYPE_NET_MAIL               = 14;
const unsigned char SUB_TYPE_NETWORK_MAX            = 15;

const unsigned char SUB_TYPE_EVT_ALARMIN            = 1;   // Event subtypes
const unsigned char SUB_TYPE_EVT_MOTION             = 2;
const unsigned char SUB_TYPE_EVT_VIDEOLOSS          = 3;
const unsigned char SUB_TYPE_EVT_VIDEOBLIND         = 4;
const unsigned char SUB_TYPE_EVT_TEXTIN             = 5;
const unsigned char SUB_TYPE_EVT_SYSTEM             = 6;
const unsigned char SUB_TYPE_EVENT_MAX              = 7;

const unsigned char SUB_TYPE_VID_CAMERA             = 1;   // VIDEO subtypes
const unsigned char SUB_TYPE_VID_STREAMING          = 2;
const unsigned char SUB_TYPE_VID_WEBCASTING         = 3;
const unsigned char SUB_TYPE_VID_MAT                = 4;
const unsigned char SUB_TYPE_VIDEO_MAX              = 5;
// ..

const unsigned char FAIL_UNKNOWN               = 0; // REMOTE_CONFIGURATION_MODIFY_RESULT
const unsigned char SUCCESS_ALL                = 1;
const unsigned char SUCCESS_PARTIAL            = 2;
const unsigned char FAIL_RANGE_ERROR           = 3;
const unsigned char FAIL_DUAL_STREAM_COLLISION = 4;             // ip cameras (can not use ftp upload or image attachment if second stream is enabled)
const unsigned char FAIL_SECOND_STREAM_OUTSTANDS_PRIMARY = 5;   // ip cameras (resolution, quality, ips of primary stream must be greater than secondary)
const unsigned char FAIL_INVALID_COMBINATION   = 6;             // invalid combination (If secondary stream of NC_* is h.264, ips of secondary stream must be same to the primary)
const unsigned char FAIL_FIELD_NOT_FILLED      = 7;

#pragma pack(push, 1)
typedef struct {
    enum _types {
        ONCONNECTED = 0,
        ONDISCONNECTED,
        STATUSLOADED,
        SYSTEMLOGLOADED,
        EVENTLOGLOADED,
        EMERGENCYINFO,
        EMERGENCYINFOEX,
        EMERGENCYINFOIDR,
        SETUPDLLLOADED,
        REMOTECONFIGURATION,
        REMOTECONFIGURATION_RESULT,
        DEVICEDATETIMELOADED,
        SUCCESSSETDEVICEDATETIME,
        REMOTEDEVICEINFOLOADED,
        SETUPDLLAPPLYSUCCESS,
        SETUPDLLAPPLYFAIL,
        SETUPDLLLOADPROGRESS,
        MAX_LISTENER
    };
} CALLBACK_ADMIN;

typedef struct {
    enum _setupResult {
        LOAD_OK = 0,
        ERROR_NOT_SUPPORT = 10,
        ERROR_HANDLE_NOT_FOUND,
        ERROR_FAIL_TO_OPEN_ZIP_FILE,
        ERROR_FAIL_TO_WRITE_SETUP_FILE,
        ERROR_FAIL_TO_RETRIEVE_DLL,
        ERROR_FAIL_TO_FIND_DLL,
        ERROR_FAIL_TO_LOAD_DLL,
        ERROR_FAIL_TO_LOAD_SETUP_FUNCTION,
    };
} REMOTE_SETUP_RESULT;

typedef struct {
    enum _record_mode {
        MODE_ALL = 0xffffffff,
        MODE_NONE = 0x00000000,
        MODE_RECORDING = 0x00000001,
        MODE_PLAYBACK = 0x00000002,
        MODE_ARCHIVE = 0x00000004,
        MODE_CLIPCOPY = 0x00000008,
        MODE_PANIC_RECORDING = 0x00000010
    };
} XDR_NET_ADMIN;

typedef struct {
    enum _system_log_type {  // system-log
        SYSTEM_LOG_UNKNOWN = 0,
        ////////////////////////////////////

        // system
        SYSTEM_LOG_BOOT_UP,
        SYSTEM_LOG_SHUTDOWN,
        SYSTEM_LOG_RESTART,
        SYSTEM_LOG_LOCAL_UPGRADE,
        SYSTEM_LOG_LOCAL_UPGRADE_FAIL,
        SYSTEM_LOG_REMOTE_UPGRADE,
        SYSTEM_LOG_REMOTE_UPGRADE_FAIL,
        SYSTEM_LOG_POWER_FAILURE,
        SYSTEM_LOG_LOCAL_TIME_CHANGE,
        SYSTEM_LOG_LOCAL_TIME_ZONE_CHANGE,
        SYSTEM_LOG_REMOTE_TIME_CHANGE,
        SYSTEM_LOG_REMOTE_TIME_ZONE_CHANGE,
        SYSTEM_LOG_TIME_SYNCED,
        SYSTEM_LOG_TIME_SYNC_FAILED,
        SYSTEM_LOG_DISK_BAD,
        SYSTEM_LOG_DISK_CONFIG_CHANGE,
        SYSTEM_LOG_DISK_ON,     // IP Cameras only; (removable disk)
        SYSTEM_LOG_DISK_OFF,    // IP Cameras only; (removable disk)
        SYSTEM_LOG_FACTORY_RESET,
        SYSTEM_LOG_HEATER_ON,
        SYSTEM_LOG_ACC_ON_OFF,
        SYSTEM_LOG_DISK_INFO,
        SYSTEM_LOG_DISK_REMOVED,
        SYSTEM_LOG_NO_STORAGE,
        SYSTEM_LOG_NOT_FORMATTED_STORAGE,
        SYSTEM_LOG_AUTO_FORMAT,
        SYSTEM_LOG_KEY_ON_OFF,
        SYSTEM_LOG_SHUTOFF,

        // user
        SYSTEM_LOG_LOCAL_LOGIN = 100,
        SYSTEM_LOG_LOCAL_LOGOUT,
        SYSTEM_LOG_REMOTE_LOGIN,
        SYSTEM_LOG_REMOTE_LOGOUT,
        SYSTEM_LOG_PASSWORD_MISMATCH,
        SYSTEM_LOG_PASSWORD_CHANGED_BY_AUTHENTICATION,

        // setup
        SYSTEM_LOG_LOCAL_SETUP_BEGIN = 200,
        SYSTEM_LOG_LOCAL_SETUP_END,
        SYSTEM_LOG_REMOTE_SETUP_CHANGE,
        SYSTEM_LOG_REMOTE_SETUP_FAIL,
        SYSTEM_LOG_SETUP_IMPORTED,
        SYSTEM_LOG_SETUP_IMPORT_FAIL,
        SYSTEM_LOG_SETUP_EXPORTED,
        SYSTEM_LOG_SETUP_EXPORT_FAIL,
        SYSTEM_LOG_SETUP_EXPORT_CANCEL,
        SYSTEM_LOG_LOCAL_SETUP_CHANGE,

        // record
        SYSTEM_LOG_SCHEDULE_ON = 300,
        SYSTEM_LOG_SCHEDULE_OFF,
        SYSTEM_LOG_PANIC_ON,
        SYSTEM_LOG_PANIC_OFF,
        SYSTEM_LOG_LOCAL_CLEAR_ALL_DATA,
        SYSTEM_LOG_REMOTE_CLEAR_ALL_DATA,
        SYSTEM_LOG_CLEAR_DISK,
        SYSTEM_LOG_FORMAT_DISK,
        SYSTEM_LOG_TANGO_FULL,
        SYSTEM_LOG_AUTO_DELETION,
        SYSTEM_LOG_ARCHIVE_ON,
        SYSTEM_LOG_ARCHIVE_OFF,
        SYSTEM_LOG_AUTO_DELETION_ARCHIVE,
        SYSTEM_LOG_REMOTE_FORMAT_DISK,

        // search
        SYSTEM_LOG_LOCAL_SEARCH_BEGIN = 400,
        SYSTEM_LOG_LOCAL_SEARCH_END,
        SYSTEM_LOG_REMOTE_SEARCH_BEGIN,
        SYSTEM_LOG_REMOTE_SEARCH_END,

        // clip-copy
        SYSTEM_LOG_LOCAL_CLIP_COPY_BEGIN = 500,
        SYSTEM_LOG_LOCAL_CLIP_COPY_END,
        SYSTEM_LOG_LOCAL_CLIP_COPY_CANCEL,
        SYSTEM_LOG_LOCAL_CLIP_COPY_FAIL,
        SYSTEM_LOG_REMOTE_CLIP_COPY_BEGIN,
        SYSTEM_LOG_REMOTE_CLIP_COPY_END,
        SYSTEM_LOG_REMOTE_CLIP_COPY_CANCEL,
        SYSTEM_LOG_REMOTE_CLIP_COPY_FAIL,
        SYSTEM_LOG_LOCAL_CLIP_COPY_INFO_USER,
        SYSTEM_LOG_LOCAL_CLIP_COPY_INFO_FROM_TIME,
        SYSTEM_LOG_LOCAL_CLIP_COPY_INFO_TO_TIME,
        SYSTEM_LOG_LOCAL_CLIP_COPY_INFO_DURATION,
        SYSTEM_LOG_LOCAL_CLIP_COPY_INFO_EXPORT_TIME,
        SYSTEM_LOG_LOCAL_CLIP_COPY_INFO_CAMERA_TITLE,
        SYSTEM_LOG_REMOTE_CLIP_COPY_INFO_USER,
        SYSTEM_LOG_REMOTE_CLIP_COPY_INFO_FROM_TIME,
        SYSTEM_LOG_REMOTE_CLIP_COPY_INFO_TO_TIME,
        SYSTEM_LOG_REMOTE_CLIP_COPY_INFO_DURATION,
        SYSTEM_LOG_REMOTE_CLIP_COPY_INFO_EXPORT_TIME,
        SYSTEM_LOG_REMOTE_CLIP_COPY_INFO_CAMERA_TITLE,
        SYSTEM_LOG_LOCAL_CLIP_COPY_INFO_SITE_NAME,
        SYSTEM_LOG_REMOTE_CLIP_COPY_INFO_SITE_NAME,
        SYSTEM_LOG_CLIP_COPY_ARCHIVE_EXPORTED,
        SYSTEM_LOG_CLIP_COPY_ARCHIVE_EXPORT_FAIL,
        SYSTEM_LOG_CLIP_COPY_ARCHIVE_EXPORT_CANCEL,

        // network
        SYSTEM_LOG_CALLBACK_FAIL = 600,
        SYSTEM_LOG_WATCH_CLIENT_CONNECTED,
        SYSTEM_LOG_WATCH_CLIENT_DISCONNECTED,
        SYSTEM_LOG_WATCH_CLIENT_CONNECT_FAILED,
        SYSTEM_LOG_AUDIO_CLIENT_CONNECTED,
        SYSTEM_LOG_AUDIO_CLIENT_DISCONNECTED,
        SYSTEM_LOG_AUDIO_CLIENT_CONNECT_FAILED,
        SYSTEM_LOG_FTP_UPLOAD_FAIL,
        SYSTEM_LOG_FTP_UPLOAD_OK,

        SYSTEM_LOG_UPNP_OK              = 610,
        SYSTEM_LOG_UPNP_PORT_CHANGED,
        SYSTEM_LOG_UPNP_ERROR_NO_IGD,
        SYSTEM_LOG_UPNP_ERROR_NETWORK,
        SYSTEM_LOG_UPNP_ERROR_FULL,
        SYSTEM_LOG_UPNP_ERROR_CONFLICT,

        SYSTEM_LOG_PUSH_NOTIFICATION_FAIL = 620,

        // print
        SYSTEM_LOG_PRINT_BEGIN = 700,
        SYSTEM_LOG_PRINT_END,
        SYSTEM_LOG_PRINT_CANCEL,

        // mirroring
        SYSTEM_LOG_MIRROR_1_START       = 800,
        SYSTEM_LOG_MIRROR_1_START_FAIL,
        SYSTEM_LOG_MIRROR_1_STOP,
        SYSTEM_LOG_MIRROR_1_STOP_FAIL,
        SYSTEM_LOG_MIRROR_2_START,
        SYSTEM_LOG_MIRROR_2_START_FAIL,
        SYSTEM_LOG_MIRROR_2_STOP,
        SYSTEM_LOG_MIRROR_2_STOP_FAIL,

        // reschedule
        SYSTEM_LOG_RESCHEDULE_START		= 900,
        SYSTEM_LOG_RESCHEDULE_STOP,

        // live
        SYSTEM_LOG_SEQUENCE_ON          = 1000,
        SYSTEM_LOG_SEQUENCE_OFF,
        SYSTEM_LOG_EVENT_MONITORING_ENABLED,
        SYSTEM_LOG_EVENT_MONITORING_DISABLED,

        // audio deterrent
        SYSTEM_LOG_ALARM_AUDIO_IMPORT_FAIL = 1100,
        SYSTEM_LOG_ALARM_AUDIO_IMPORTED,
        SYSTEM_LOG_ALARM_AUDIO_EXPORT_FAIL,
        SYSTEM_LOG_ALARM_AUDIO_EXPORTED,
        SYSTEM_LOG_ALARM_AUDIO_EXPORT_CANCEL,

        SYSTEM_LOG_PARTIAL_DATA_ERASE_BEGIN = 1200,
        SYSTEM_LOG_PARTIAL_DATA_ERASE_END,
        SYSTEM_LOG_PARTIAL_DATA_ERASE_CANCEL,
        SYSTEM_LOG_PARTIAL_DATA_ERASE_FAIL,
        SYSTEM_LOG_PARTIAL_DATA_ERASE_INFO_INFO_USER,
        SYSTEM_LOG_PARTIAL_DATA_ERASE_INFO_FROM_TIME,
        SYSTEM_LOG_PARTIAL_DATA_ERASE_INFO_TO_TIME,
        SYSTEM_LOG_PARTIAL_DATA_ERASE_INFO_DURATION,
        SYSTEM_LOG_PARTIAL_DATA_ERASE_INFO_CAMERA_TITLE,

        // log
        SYSTEM_LOG_SYSTEM_LOG_EXPORTED              = 1300,
        SYSTEM_LOG_SYSTEM_LOG_EXPORT_FAIL,
        SYSTEM_LOG_SYSTEM_LOG_EXPORT_CANCEL,

        // network camera
        SYSTEM_LOG_NETWORK_CAMERA_UPGRADE_BEGIN     = 1400,
        SYSTEM_LOG_NETWORK_CAMERA_UPGRADE_END,
        SYSTEM_LOG_NETWORK_CAMERA_UPGRADE_FAIL,
        SYSTEM_LOG_NETWORK_CAMERA_UPGRADE_INFO_USER,
        SYSTEM_LOG_NETWORK_CAMERA_UPGRADE_INFO_TITLE,
        SYSTEM_LOG_NETWORK_CAMERA_REGISTER_BEGIN,
        SYSTEM_LOG_NETWORK_CAMERA_REGISTER_END,
        SYSTEM_LOG_NETWORK_CAMERA_REGISTER_FAIL,
        SYSTEM_LOG_NETWORK_CAMERA_REGISTER_CANCEL,

        // equalizer
        SYSTEM_LOG_EQUALIZER_INITIALIZE_ALL_CHANNEL = 1500,
        SYSTEM_LOG_EQUALIZER_INITIALIZE_EACH_CHANNEL,
    };
} SYSTEM_LOG_TYPE;

struct SystemCheck {
    // 0:abnormal, 1:normal, 2:not use
    unsigned char   camera[MAX_NUM_UNITS];      // system check - video loss
    unsigned char   alarm[MAX_NUM_UNITS];       // system check - alarm in
    long            record;                     // system check - recording
};

struct DiskStatus {
    // 0:abnormal, 1:normal, 2:not use
    unsigned char bad;             // HDD bad
    unsigned char overTemperature; // HDD over temperature
    unsigned char smartError;      // HDD S.M.A.R.T. bad
};

struct StatusInfo {
    // 0:no event, 1:event, 2:not use
    unsigned char   motion[MAX_NUM_UNITS];      // status - motion event
    unsigned char   alarm_in[MAX_NUM_UNITS];    // status - alarm in event
    unsigned char   text_in[MAX_NUM_UNITS];     // status - text in event
    SystemCheck     sys_check;                  // system check
    unsigned char   recording[MAX_NUM_UNITS];   // not use
    unsigned char   alarm_out[MAX_NUM_UNITS];   // status - alarm out event
    SDK_TIME_T      record_begin;               // status - begin of recording period
    SDK_TIME_T      record_end;                 // status - end of recording period
    int             playback;                   // status - now playback?
    char            version[24];                // status - version of SDR4
    int             nAlarmOut;
    unsigned char   objectTracker[MAX_NUM_UNITS];
    unsigned char   videoBlind[MAX_NUM_UNITS];  // video blind
    DiskStatus      diskStatus[MAX_NUM_UNITS];

    // for 32ch
    unsigned char   motion32[MAX_NUM_UNITS];        // status - motion event
    unsigned char   alarm_in32[MAX_NUM_UNITS];      // status - alarm in event
    unsigned char   recording32[MAX_NUM_UNITS];     // not use
    SystemCheck     sys_check32;
    unsigned int    struct_size;
    unsigned int    packet_version;
    unsigned char   alarm_out32[MAX_NUM_UNITS];     // status - alarm out event
    unsigned char   terrorism[MAX_NUM_CAMERA_32];   // status - Terrorism
    int             nCameraNum;                     // Number of camera
    int             nSensorNum;                     // Number of sensor
    int             nPosNum;                        // Number of Pos
    int             nAudioNum;                      // Number of Audio
    int             reserved[4];
    unsigned char   audio_in[MAX_NUM_CAMERA_32];    // status - alarm out event
    unsigned char   videoBlind32[MAX_NUM_UNITS];    // video blind
    unsigned char   reserved1[MAX_NUM_CAMERA_32];   // reserved status1
    unsigned char   reserved2[MAX_NUM_CAMERA_32];   // reserved status2
    unsigned char   reserved3[256];                 // reserved status2
};

typedef struct {
    int     seq_num;                                // system log number
    char    version[2];                             // version info.
    char    type;                                   // system log type
    char    dummy;
    SDK_TIME_T  time;                                   // time
    char    data[MAX_LEN_LOG_DATA];                 // more data
} SYSTEM_LOG, *PSYSTEM_LOG;

typedef struct {
    SDK_TIME_T  time;                                   // time
    int     type;                                   // system log type
    char    data[MAX_LEN_LOG_DATA_EX];              // more data
} SYSTEM_LOG_EX, *PSYSTEM_LOG_EX;

typedef struct {
    int                 seq_num;                    // event log number
    char                version[2];                 // version info.
    char                type;                       // alarm type (Motion, Text-In, Alarm, Sensor, ... see _event_type for details)
    char                id;                         // alarm id
    SDK_TIME_T          time;                       // event sec.
    int                 msec;                       // event msec.
    unsigned int        cam_id;                     // associated camera
    unsigned short int  pre_dwell[MAX_NUM_UNITS];
    unsigned short int  post_dwell[MAX_NUM_UNITS];  // Post alarm dwell time(second)
    char                label[MAX_NUM_UNITS];       // alarm label
    char                trans_num[MAX_NUM_UNITS+1]; // transaction number
    char                level;                      // event level, emergency event / normal event
    char                dummy[2];
} EVENT_LOG, *PEVENT_LOG;

typedef struct {
    SDK_TIME_T  time;                                   // time
    char    type;                                   // alarm type (Motion, Text-In, Alarm, Sensor)
    char    label[MAX_LEN_LOG_DATA_EX];             // alarm label
} EVENT_LOG_EX, *PEVENT_LOG_EX;

typedef struct {
    int id;
    int dst;
    unsigned int time;
} DATE_TIME;

typedef struct {
    int classInfo;
    int typeInfo;
    char version[5];
} VERSION_INFO, *PVERSION_INFO;

typedef  struct {
    int                 seq_num;                    // log num
    char                version[2];                 // version
    char                type;                       // alarm type (Motion, Text-In, Alarm, Sensor)
    char                id;                         // alarm id
    SDK_TIME_T          time;                       // event sec
    int                 msec;                       // event msec
    unsigned int        cam_id;                     // camera info related to event
    unsigned short int  pre_dwell[MAX_NUM_UNITS];
    unsigned short int  post_dwell[MAX_NUM_UNITS];  // Post alarm dwell time(second) (16*2)
    char                label[MAX_LEN_LOG_LABEL];   // alarm label(log info for system logs)(32)
    char                trans_num[MAX_NUM_UNITS+1]; // transaction number(16)
    char                level;                      // event level  (emergency event / normal event)
    char                dummy[2];
    char                textIn[MAX_TEXT_IN_DATA_LENGTH];
} EVENT_INFO, *PEVENT_INFO;     // 120bytes

typedef struct {
    EVENT_INFO eventInfo;
    char dvrName[MAX_DVRNS_DVR_NAME_LENGTH + 1];
} EVENT_INFO_EX, *PEVENT_INFO_EX;

// IDR Event Info
typedef struct {
    EVENT_INFO eventInfo;
    char postName[32];
    char dvrName[MAX_DVRNS_DVR_NAME_LENGTH + 1];
} EVENT_INFO_IDR, *PEVENT_INFO_IDR;


enum EVENT_INFO_TYPE {
    INFO=0, INFO_EX, INFO_IDR,
};

typedef struct {
    EVENT_INFO eventInfo;
    char postName[32];
    char dvrName[MAX_DVRNS_DVR_NAME_LENGTH + 1];

    EVENT_INFO_TYPE infoType;
    char peerName[32];
} EVENT_INFO_COMMON;

typedef struct {
    char            dvrnsServer[MAX_DVRNS_SERVER_LENGTH + 1] ;
    unsigned int    dvrnsPortNumber;
    char            dvrnsDvrName[MAX_DVRNS_DVR_NAME_LENGTH + 1];
    //IpAddress     dnsServer;
    char            dnsServer[16];
    unsigned int    key;
} DVRNS_NAME_CHECK_INFO;

typedef struct {
    static const unsigned int MAX_LEN_DATA = 32;
    static const unsigned int MAX_LEN_TYPESTRING = 128;
    int   _type;
    SDK_TIME_T  _time;
    char    _typeString[MAX_LEN_TYPESTRING];
    char    _data[MAX_LEN_DATA];
} REMOTE_LOG_SYSTEM;

typedef struct {
    static const unsigned int MAX_LEN_DATA = 32;
    static const unsigned int MAX_LEN_TYPESTRING = 128;
    int   _type;
    SDK_TIME_T  _time;
    char    _typeString[MAX_LEN_TYPESTRING];
    char    _label[MAX_LEN_DATA];
} REMOTE_LOG_EVENT;

typedef struct {
    enum {
        MAX_SERIAL_LENGTH = 48,
        MAX_DISK_SMART_ATTRIBUTE = 32,
    };
    typedef struct {
        enum {
            MAX_ATTRIBUTENAME_LENGTH = 48,
        };
        unsigned char   id;
        char            attributeName[MAX_ATTRIBUTENAME_LENGTH];
        unsigned char   current;
        unsigned char   worst;
        unsigned char   threshold;
    } DISK_SMART_ATTRIBUTE;
    char            diskModel[MAX_SERIAL_LENGTH];
    char            diskSerial[MAX_SERIAL_LENGTH];
    DISK_SMART_ATTRIBUTE diskSmartAttribute[MAX_DISK_SMART_ATTRIBUTE];
    unsigned __int64 freespace;
} DISK_INFO;

typedef struct {
    enum {
        MAX_ATTRIBUTENAME_LENGTH = 48,
    };
    unsigned char   id;
    char            attributeName[MAX_ATTRIBUTENAME_LENGTH];
    unsigned char   current;
    unsigned char   worst;
    unsigned char   threshold;
} DISK_SMART_ATTRIBUTE;

/*
 Categorized and layered struct which represents selective set of category types and their subcategory types.
 Class REMOTE_CONFIGURATION_CATEGORY has set of CATEGORYs. Each category can contain up to 255 subcategories.
 For example, if you want to retrieve lan configuration and mail configuration under network settings
 and motion event under event settting, actual shape of REMOTE_CONFIGURATION_CATEGORY will be like below:

 REMOTE_CONFIGURATION_CATEGORY
   - CATEGORY (type : TYPE_NETWORK)
     + CATEGORY (type : SUB_TYPE_LAN)
     + CATEGORY (type : SUB_TYPE_MAIL)
   - CATEGORY (type : TYPE_EVENT)
     + CATEGORY (type : SUB_TYPE_MOTION)

 * This struct should build caller of admin_requestGetRemoteConfiguration. (see sample program code)

 See REMOTE_CONFIGURATION struct for actual configuration caregories and their subcategories.

 Beware of memory leaks! this class does not delete passed resources (dynamically allocated pointers).
*/

class REMOTE_CONFIGURATION_CATEGORY {
public:
    enum { MAX_SUB_TYPE = 255 };
    class CATEGORY {
    public:
        CATEGORY(unsigned char type) : _type(type), _subCategoryCnt(0) { memset(_subCategories, 0, sizeof(_subCategories)); }
        CATEGORY() : _type(0), _subCategoryCnt(0) { memset(_subCategories, 0, sizeof(_subCategories)); }
        virtual ~CATEGORY()   { }

        void putSubCategory(CATEGORY* cat) { if (_subCategoryCnt < MAX_SUB_TYPE) _subCategories[_subCategoryCnt++] = cat; }
        void setType(unsigned char type) { _type = type;    }
        unsigned char type() const { return _type;          }
        int subCategoryCnt() const  { return _subCategoryCnt; }
        const CATEGORY* subCategory(unsigned char idx) const { return _subCategories[idx]; }

    private:
        unsigned char _type;
        int           _subCategoryCnt;
        CATEGORY*     _subCategories[MAX_SUB_TYPE];
    };

public:
    REMOTE_CONFIGURATION_CATEGORY() { clear(); }
    virtual ~REMOTE_CONFIGURATION_CATEGORY() {  }
    void putCategory(CATEGORY* cat)   { if (_subCategoryCnt < MAX_SUB_TYPE) _subCategories[_subCategoryCnt++] = cat; }
    void clear()   { _subCategoryCnt = 0; memset(_subCategories, 0, sizeof(_subCategories));      }
    int subRequestCnt() const  { return _subCategoryCnt; }
    const CATEGORY* getCategory(unsigned char idx) const { return _subCategories[idx];        }

private:
    CATEGORY*    _subCategories[MAX_SUB_TYPE];
    int          _subCategoryCnt;
};

/*
 Categorized and layered struct which represents configuration modify types and their results.
 Class REMOTE_CONFIGURATION_RESULTS has set of RESULTs. Each result can contain up to 255 results.
 For example, if you called admin_requestGetRemoteConfiguration function with REMOTE_CONFIGURATION_CATEGORY
 that contains lan category and mail category under network category and motion category under event category,
 REMOTE_CONFIGURATION_RESULTS returned from remote device will be like below:

 REMOTE_CONFIGURATION_RESULTS
   - RESULT (type : TYPE_NETWORK, result value)
     + RESULT (type : SUB_TYPE_LAN, result value)
     + RESULT (type : SUB_TYPE_MAIL, result value)
   - RESULT (type : TYPE_EVENT, result value)
     + RESULT (type : SUB_TYPE_MOTION, result value)

 * This struct is build by IDIS admin sdk.

 Class REMOTE_CONFIGURATION_RESULTS has same struct with REMOTE_CONFIGURATION_CATEGORY because peer device
 should return operation for each request (configuration categories and subcategories).

 Unlike REMOTE_CONFIGURATION_CATEGORY, dynamically allocated objects are freed in dtor of REMOTE_CONFIGURATION_RESULTS.
*/

class REMOTE_CONFIGURATION_RESULTS {
public:
    enum { MAX_SUB_RESULT = 256 };
    class RESULT {
    public:
        RESULT(unsigned char type, unsigned char result) : _type(type), _result(result), _subResultCnt(0) { memset(_subResults, 0, sizeof(_subResults)); }
        RESULT() : _type(0), _result(0), _subResultCnt(0)  { memset(_subResults, 0, sizeof(_subResults)); }
        virtual ~RESULT() { free(); }

        void putSubResult(RESULT* result) { if (_subResultCnt < MAX_SUB_RESULT) _subResults[_subResultCnt++] = result; }
        void setTypeResult(unsigned char type, unsigned char result) { _type = type; _result = result;   }
        unsigned char type() const   { return _type;          }
        unsigned char result() const { return _result;        }
        int subResultCnt() const     { return _subResultCnt;  }
        const RESULT* getResult(unsigned char idx) const { return _subResults[idx]; }

        void free() {
            for (int i = 0; i < _subResultCnt; ++i) {
                if (_subResults[i]) {
                    _subResults[i]->free();
                    delete _subResults[i];
                }
            }
            _subResultCnt = 0;
        }

    private:
        unsigned char _type;
        unsigned char _result;
        int           _subResultCnt;
        RESULT*       _subResults[MAX_SUB_RESULT];
    };

public:
    REMOTE_CONFIGURATION_RESULTS() { clear(); }
    virtual ~REMOTE_CONFIGURATION_RESULTS() { free(); }
    void putResult(RESULT* res)   { if (_subResultCnt < MAX_SUB_RESULT) _results[_subResultCnt++] = res; }
    void clear()   { _subResultCnt = 0; memset(_results, 0, sizeof(_results));      }
    int  subResultCnt() const  { return _subResultCnt; }
    void free() {
        for (int i = 0; i < _subResultCnt; ++i) {
            if (_results[i]) {
                _results[i]->free();
                delete _results[i];
            }
        }
        _subResultCnt = 0;
    }

    RESULT* getResult(unsigned char idx) const { return _results[idx];        }

private:
    RESULT*      _results[MAX_SUB_RESULT];
    int          _subResultCnt;
};

/*
 Categorized and layered struct which represents configuration of IDIS products.
 Using REMOTE_CONFIGURATION_CATEGORY class, we can get/set configuration we want.
 When modifying configuration of remote devices, it is recommended that fill this struct with
 zeroes to prevent passing invalid values to remote devices.
*/
typedef struct {
    typedef struct {
        enum {
            NORMAL,
            COVERT_1,
            COVERT_2,
            MAX_USE_COUNT,
        };  // useMask in CAMERA_CONFIGURATION;
        enum {
            BRATE_300, BRATE_600, BRATE_1200, BRATE_2400, BRATE_4800,
            BRATE_9600, BRATE_19200, BRATE_38400, BRATE_57600, BRATE_115200,
            MAX_BRATE,
        };  // bit rate in serial communication; (PTZ control, text-in, ...)
        enum {
            PORT_NONE, PORT_RS232, PORT_RS485,
            USB_SERIAL1, USB_SERIAL2, USB_SERIAL3, USB_SERIAL4,
            USB_SERIAL5, USB_SERIAL6, USB_SERIAL7, USB_SERIAL8,
            LAN1, LAN2, LAN3, LAN4, LAN5, LAN6, LAN7, LAN8,
            LAN9, LAN10, LAN11, LAN12, LAN13, LAN14, LAN15, LAN16,
            MAX_PORT,
        };  // port type in serial communication; (PTZ control, text-in, ...)
        enum {
            PTY_NONE,
            PTY_ODD,
            PTY_EVEN,
            MAX_PARITY,
        }; // parity in serial communication; (PTZ control, text-in, ...)
        enum {
            MAX_PTZ_PRESSET = 32,
            //MAX_NUM_PTZ_PRODUCT = 256,
            MAX_NUM_PTZ_PRODUCT = 32,
            MAX_NUM_PTZ_PRODUCT_NAME = 64,
        }; // field length in PTZ_CONFIGURATION;
        enum {
            MAX_ALARMOUT_SCHEDULE = 20,
            MAX_ALARMOUT_TITLE_LEN = 31,
        }; // field length in ALAMOUT_CONFIGURATION
        enum {
            SUN     = 0x00000001,
            MON     = 0x00000002,
            TUE     = 0x00000004,
            WED     = 0x00000008,
            THU     = 0x00000010,
            FRI     = 0x00000020,
            SAT     = 0x00000040,
            HOLIDAY = 0x00000080,
            MON_FRI = MON | TUE | WED | THU | FRI,
            ALL     = SUN | MON_FRI | SAT | HOLIDAY,
        }; // day in schedule (alarm-out, schedule, ...)
        enum {
            TYPE_NC,        // normally closed
            TYPE_NO,        // normally open
        }; // alarm-out type
        enum {
            MAX_IPADDR_LEN = 15,
            MAX_CALLBACK_SERVER = 5,
            MAX_ID_PW_LEN = 31,
            MAX_NAME_LEN = 63,
        }; // field length in callback notification
        enum {
            TRANSFER_UNIT_BPS,
            TRANSFER_UNIT_IPS,
        };
        enum {
            TYP_RESOLUTION_STANDARD,
            TYP_RESOLUTION_HIGH,
            TYP_RESOLUTION_VERY_HIGH,
            MAX_RESOLUTION_COUNT,
        };
        enum {
            QUALITY_LOW,
            QUALITY_STANDARD,
            QUALITY_HIGH,
            QUALITY_VERYHIGH,
            MAX_QUALITY_COUNT,
        };
        enum {
            LAN_MANUAL,
            LAN_DHCP,
            LAN_ADSL,
        };
        enum {
            IP_FILTERING_ALLOW_TYPE,
            IP_FILTERING_DENY_TYPE
        };  // for ip cameras
        enum {
            IP_FILTERING_HOST,
            IP_FILTERING_GROUP
        };  // for ip cameras
        enum {
            MAX_IP_FILTERING_IPADDRESS_COUNT = 32,
        };
        enum {
            MAX_EAP_USERNAME_LENGTH = 31,
            MAX_EAP_PASSWORD_LENGTH = 31,
        };
        enum {
            MAX_SERVER_SENDER = 63,
            MAX_MAIL_ID_PW = 31,
            MAX_MAIL_RECIPIENT = 10,
        };  // mail
        enum {
            AUTHORITY_SHUTDOWN_RESTART      = 0x00000001,
            AUTHORITY_UPGRADE               = 0x00000002,
            AUTHORITY_SYSTEM_TIME_CHANGE    = 0x00000004,
            AUTHORITY_DATA_CLEAR            = 0x00000008,
            AUTHORITY_SETUP                 = 0x00000010,
            AUTHORITY_USER_MANAGE           = 0x00000020,
            AUTHORITY_COLOR_CONTROL         = 0x00000040,
            AUTHORITY_PTZ_CONTROL           = 0x00000080,
            AUTHORITY_ALARM_OUT_CONTROL     = 0x00000100,
            AUTHORITY_COVERT_CAMERA_VIEW    = 0x00000200,
            AUTHORITY_SYSTEM_CHECK          = 0x00000400,
            AUTHORITY_RECORD_SETUP          = 0x00000800,
            AUTHORITY_SEARCH                = 0x00001000,
            AUTHORITY_CLIP_COPY             = 0x00002000,
            AUTHORITY_PTZ_SETUP             = 0x00004000,
            AUTHORITY_ALARM_OUT_SETUP       = 0x00008000,
            AUTHORITY_COVERT_CAMERA_SETUP   = 0x00010000,

            AUTHORITY_ALL                   = 0xffffffff,

            MAX_AUTHORITY_COUNT = 30
        };  // user and group authority
        enum {
            LOGIN_IN_PROGRESS = -1,
            LOGIN_LEVEL_INVALID = 0,
            LOGIN_LEVEL_GUEST,
            LOGIN_LEVEL_USER,
            LOGIN_LEVEL_ADMINISTRATOR,
        };  // user login level
        enum {
            REMOTE_CONTROL,
            ZOOM,
            NETWORK,
            FREEZE_N_SEQUENCE,
            FREE_SPACE,
            DATE,
            TIME,
            USER_NAME,
            SCREEN_GROUP,
            ARCHIVE,
            BACKGROUND_PANEL,
            MIRROR,
            MAX_STATUS_INDEX,
        }; // display configuration setup item
        enum {
            NO,
            RECORD,
            PTZ,
            TITLE,
            AUDIO,
            TEXT_IN,
            MAX_CAMERA_INFO_INDEX,
        }; // display configuration setup item
        enum {
            FULL_SEQUENCE,
            CAMEO_SEQUENCE,
        }; // sequence type
        enum {
            RCTL_PRODUCT1,
            RCTL_PRODUCT2,
            MAX_REMOTE_CONTROL_PRODUCT,
        }; // remote control product type
        enum {
            MASK_GENERAL    = 0x00000001,
            MASK_SCHEDULE   = 0x00000002,
            MASK_PREEVENT   = 0x00000004,
        }; // recording configuration mask
        enum {
            N_ACTION_NONE            = 0,
            N_ACTION_RECORD          = 1,
            N_ACTION_ALARM_OUT       = 2,
            N_ACTION_NOTIFY          = 3,
            N_ACTION_PTZ_PRESET      = 4,
            N_ACTION_SPOT_MONITORING = 5,
            N_ACTION_AUDIO_ALARM     = 6,
            N_ACTION_MAX             = 7,
        }; // notification action type
        enum {
            MAX_SCHEDULE_SET = 20,
        };
        enum {
            MAX_REMOTE_LAN_CALLBACK = 5,
        };
        enum {
            MAX_START_STRING_LENGTH = 15,
            MAX_END_STRING_LENGTH = 15,
            MAX_LINE_DELIMITER_LENGTH = 7,
            MAX_IGNORE_STRING_LENGTH = 31,
        };  // text-in settings
        enum {
            MAX_TEXTIN_TITLE_LEN = 31,
        };
        enum {
            MAX_MOTION_BLOCK = 512,
        };
        enum {
            DUAL_STREAM_LIVE_MAIN,      // [Live,Recording] / [Live]
            DUAL_STREAM_RECORD_MAIN,    // [Live] / [Live,Recording]
            SINGLE_STREAM_LIVE_MAIN,    // [Live,Recording] / [None]
            MAX_STREAM_TYPE_COUNT,
        };
        enum {
            COMPRESSION_H264,
            COMPRESSION_JPEG,
            MAX_COMPRESSION_COUNT,
        };
        enum {
            NUM_RESOLUTION_352_240,
            NUM_RESOLUTION_704_480,
            NUM_RESOLUTION_1280_720,
            NUM_RESOLUTION_1920_1080,
            NUM_RESOLUTION_1280_720_WIDE,
            NUM_MAX_RESOLUTION_COUNT,
        }; // image reolustion in (width x height)
        enum {
            CBR = 1,
            VBR = 3,
        }; // bit-rate control mode
        enum {
            MAX_DNS_SERVERS = 2,
            MAX_NETWORK_INTERFACES = 4,
        };
        enum {
            MAX_STREAM_COUNT = 3,
        };
    } DEFINES;

    typedef struct {
        typedef struct {
            typedef struct {
                char         _ipAddress[DEFINES::MAX_IPADDR_LEN+1];
                char         _gateway[DEFINES::MAX_IPADDR_LEN+1];
                char         _subnetMask[DEFINES::MAX_IPADDR_LEN+1];

                unsigned int _lanType;
                char         _adslId[DEFINES::MAX_ID_PW_LEN+1];       // LEN = 31 (w/o NULL char)
                char         _adslPassword[DEFINES::MAX_ID_PW_LEN+1]; // LEN = 31 (w/o NULL char)
                char         _dnsServer[DEFINES::MAX_DNS_SERVERS][DEFINES::MAX_IPADDR_LEN+1];
                bool         _useUPnP;
                bool         _useAutoDnsServer;
            } NETWORK_INTERFACE;

            unsigned char _numInterfaces;
            unsigned int _adminPortNumber;
            unsigned int _watchPortNumber;
            unsigned int _searchPortNumber;
            //unsigned int _callbackPortNumber; // defined in CALLBACKSERVER struct
            unsigned int _audioPortNumber;
            unsigned int _recordPortNumber;
            unsigned int _webguardPortNumber;

            NETWORK_INTERFACE _networkInterfaces[DEFINES::MAX_NETWORK_INTERFACES];
        } LAN;

        typedef struct {
        } MODEM;

        typedef struct {
            bool         _useCallbackServer;
            unsigned int _retry;
            char         _callbackAcceptIps[DEFINES::MAX_CALLBACK_SERVER][DEFINES::MAX_IPADDR_LEN+1];
            unsigned short _callbackAcceptPorts[DEFINES::MAX_CALLBACK_SERVER];
        } CALLBACKSERVER;

        typedef struct {
            typedef struct {
                unsigned char _type[DEFINES::MAX_IP_FILTERING_IPADDRESS_COUNT];             // IP_FILTERING_HOST, IP_FILTERING_GROUP
                char _ipAddress1[DEFINES::MAX_IP_FILTERING_IPADDRESS_COUNT][DEFINES::MAX_IPADDR_LEN+1];    // Specific IP or Begin IP Address
                char _ipAddress2[DEFINES::MAX_IP_FILTERING_IPADDRESS_COUNT][DEFINES::MAX_IPADDR_LEN+1];    // End IP Address;
            } IPFILTERGROUP;

            bool            _useIpFiltering;
            unsigned char   _ipFilteringPolicy; // IP_FILTERING_ALLOW_LIST, IP_FILTERING_DENY_LIST
            unsigned char   _ipFilteringAllowCount;
            unsigned char   _ipFilteringDenyCount;
            IPFILTERGROUP   _ipFilteringAllowList;
            IPFILTERGROUP   _ipFilteringDenyList;
        } IPFILTERING;

        typedef struct {
            unsigned short  _rtspPortNumber;
            unsigned char   _discoveryMode;
            unsigned char   _remoteDiscoveryMode;
        } ONVIF;

        typedef struct {
            bool            _useRtsp;
            unsigned int    _rtspPortNumber;
            unsigned int    _rtpStartPortNumber;
            unsigned int    _rtpEndPortNumber;
            bool            _useMobile;
            bool            _allowAnonymousUsers;
        } RTSP;

        typedef struct {
            bool          _useMail;
            bool          _useSmtpLogin;
            bool          _useSmtpTls;
            unsigned int  _smtpPort;
            char          _smtpServer[DEFINES::MAX_SERVER_SENDER + 1];
            char          _sender[DEFINES::MAX_SERVER_SENDER + 1];
            char          _recipients[DEFINES::MAX_MAIL_RECIPIENT][DEFINES::MAX_SERVER_SENDER + 1];
            char          _smtpUserName[DEFINES::MAX_MAIL_ID_PW + 1];
            char          _smtpPassword[DEFINES::MAX_MAIL_ID_PW + 1];
        } MAIL;

        LAN            _lan;
        MODEM          _modem;
        CALLBACKSERVER _callbackServer;
        IPFILTERING    _ipFiltering;
        RTSP           _rtsp;
        ONVIF          _onvif;
        MAIL           _mail;
    } NETWORK_CONFIGURATION;

    typedef struct {
        typedef struct {
            unsigned int    _alarmOutChannel;
            bool            _sendEmail;
            bool            _remoteCallback[DEFINES::MAX_REMOTE_LAN_CALLBACK]; // < 0 for don't use
            char            _audioAlarm;     // IP cameras only, < 0 for don't use
            bool            _ftpUpload;      // IP cameras only;
            unsigned int    _recordChannels;
            char            _ptzPreset;     // < 0 for don't use, (not used in System event)
            char            _spotMonitor;   // 0 for none
            bool            _attachImageOnMail;
        } ACTION_TO_TAKE;
        typedef struct {
            typedef struct {
                bool _use;
                unsigned int _sensitivityDay;
                unsigned int _sensitivityNight;
                unsigned int _minBlockDay;
                unsigned int _minBlockNight;
                bool _viewZone;
                unsigned char _gridArea[DEFINES::MAX_MOTION_BLOCK];   // 1-dimension'ed grid Selection area (length : gridSizeX * gridSizeY)
                ACTION_TO_TAKE _action;
            } MOTION_ITEM;

            unsigned short _imageSizeX, _imageSizeY;  // width, height of original image
            unsigned char  _gridSizeX, _gridSizeY;    // grid number
            bool   _useIgnoringTime;
            unsigned short _ignoreTime;              // in milliseconds
            unsigned char _dayTimeBeginHour;
            unsigned char _dayTimeBeginMin;
            unsigned char _dayTimeEndHour;
            unsigned char _dayTimeEndMin;
            MOTION_ITEM _motionItems[MAX_NUM_CAMERA_32];
        } MOTION;

        MOTION      _motion;
    } EVENT_CONFIGURATION;

    typedef struct {
        typedef struct {
        } CAMERA;
        typedef struct {
            typedef struct {
                bool _use;
                bool _isRecordStream;
                unsigned char _compression;
                unsigned char _resolution;
                unsigned char _quality;
                unsigned char _bitrateControl;
                unsigned char _frameRate;
            } STREAM_CONFIG;

            unsigned char _streamType;  // DUAL_STREAM_LIVE_MAIN, DUAL_STREAM_RECORD_MAIN, SINGLE_STREAM_LIVE_MAIN
            unsigned int _numStreams;
            STREAM_CONFIG _streamings[DEFINES::MAX_STREAM_COUNT];
        } STREAMING;
        typedef struct {
        } WEBCASTING;
        typedef struct {
        } MAT;

        CAMERA      _camera;
        STREAMING   _streaming;
        WEBCASTING  _webcasting;
        MAT         _mat;
    } VIDEO_CONFIGURATION;    // for ip cameras


    REMOTE_CONFIGURATION_CATEGORY _categories;      // used when modify device configuration

    NETWORK_CONFIGURATION   _networkConfiguration;
    EVENT_CONFIGURATION     _eventConfiguration;
    VIDEO_CONFIGURATION     _videoConfiguration; // for ip-cameras (NC_*)
} REMOTE_CONFIGURATION;


#pragma pack(pop)
/////////////////////////////////////////////////////////////////////////////

//{{ adminsdk_callback_func types
// reference below CALLBACK_ADMIN struct for ntypes
IDIS_DLLFUNC void IDISAPI admin_registerCallback(IDISHADMIN hAdmin, int ntypes, LPLISTENER_FUNC lpFunc);

/////////////////////////////////////////////////////////////////////////////

IDIS_DLLFUNC IDISHADMIN IDISAPI admin_initialize(void);
IDIS_DLLFUNC void IDISAPI admin_finalize(IDISHADMIN hAdmin);
IDIS_DLLFUNC void IDISAPI admin_startup(IDISHADMIN hAdmin, int nMaxChannels, int nMaxCallbackChannels = 5, int callbackPort = 8201);
IDIS_DLLFUNC void IDISAPI admin_cleanup(IDISHADMIN hAdmin);

// adminSDK_connection //////////////////////////////////////////////////////

IDIS_DLLFUNC int  IDISAPI admin_connect(IDISHADMIN hAdmin, LPCTSTR siteName, LPCTSTR siteAddress, LPCTSTR userName, LPCTSTR userPassword, int adminPort, int watchPort, bool isPasswordEncrypted = false, void* attachment = NULL);
IDIS_DLLFUNC int  IDISAPI admin_connect_dvrns(IDISHADMIN hSearch, LPCTSTR siteName, LPCTSTR dvrnsAddress, LPCTSTR dvrName, LPCTSTR userName, LPCTSTR userPassword, int dvrnsPort, bool isPasswordEncrypted = false, void* attachment = NULL);
IDIS_DLLFUNC bool IDISAPI admin_reconnect(IDISHADMIN hAdmin, LPCTSTR siteName, LPCTSTR siteAddress, LPCTSTR userName, LPCTSTR userPassword, int adminPort, int watchPort, short channel, bool isPasswordEncrypted = false, void* attachment = NULL);
IDIS_DLLFUNC bool IDISAPI admin_reconnect_dvrns(IDISHADMIN hAdmin, LPCTSTR siteName, LPCTSTR dvrnsAddress, LPCTSTR dvrName, LPCTSTR userName, LPCTSTR userPassword, int dvrnsPort, short channel, bool isPasswordEncrypted = false, void* attachment = NULL);
IDIS_DLLFUNC void IDISAPI admin_disconnect(IDISHADMIN hAdmin, int channel);
IDIS_DLLFUNC bool IDISAPI admin_isConnecting(IDISHADMIN hAdmin, int channel);
IDIS_DLLFUNC bool IDISAPI admin_isConnected(IDISHADMIN hAdmin, int channel);
IDIS_DLLFUNC int  IDISAPI admin_connect_connectService(IDISHADMIN hAdmin, LPCTSTR siteName, LPCTSTR dvrName, LPCTSTR gatewayAddress, int gatewayPort, int proxyPort, LPCTSTR userName, LPCTSTR userPassword, int natType, void* attachment);
/////////////////////////////////////////////////////////////////////////////
IDIS_DLLFUNC bool IDISAPI admin_isSupportRequestNextPrevLogPage(IDISHADMIN hAdmin, int channel);
/////////////////////////////////////////////////////////////////////////////
// User-specific data
IDIS_DLLFUNC bool  IDISAPI admin_setUserParamByHandle(IDISHADMIN hAdmin, void* pUserParam);
IDIS_DLLFUNC bool  IDISAPI admin_setUserParamByChannel(IDISHADMIN hAdmin, int channel, void* pUserParam);
IDIS_DLLFUNC void* IDISAPI admin_getUserParamByHandle(IDISHADMIN hAdmin);
IDIS_DLLFUNC void* IDISAPI admin_getUserParamByChannel(IDISHADMIN hAdmin, int channel);

IDIS_DLLFUNC void IDISAPI admin_requestStatus(IDISHADMIN hAdmin, int channel);
IDIS_DLLFUNC bool IDISAPI admin_requestSystemLog(IDISHADMIN hAdmin, int channel, SDK_TIME_T tmFrom, SDK_TIME_T tmTo, int reqPage, bool reload, unsigned int type = 0);
IDIS_DLLFUNC bool IDISAPI admin_requestEventLog(IDISHADMIN hAdmin, int channel, SDK_TIME_T tmFrom, SDK_TIME_T tmTo, int reqPage, bool reload, unsigned int type = 0, unsigned short* eventTypes = 0, unsigned short eventCount = 0);
IDIS_DLLFUNC bool IDISAPI admin_requestPanicRecording(IDISHADMIN hAdmin, int channel, bool on);
IDIS_DLLFUNC bool IDISAPI admin_requestSetup(IDISHADMIN hAdmin, int channel);
IDIS_DLLFUNC bool IDISAPI admin_requestGetRemoteConfiguration(IDISHADMIN hAdmin, int channel, const REMOTE_CONFIGURATION_CATEGORY* category);
IDIS_DLLFUNC bool IDISAPI admin_requestModifyRemoteConfiguration(IDISHADMIN hAdmin, int channel, const REMOTE_CONFIGURATION* configuration);
IDIS_DLLFUNC bool IDISAPI admin_requestDeviceDateTime(IDISHADMIN hAdmin, int channel);
IDIS_DLLFUNC bool IDISAPI admin_requestRemoteDeviceInfo(IDISHADMIN hAdmin, int channel);

/////////////////////////////////////////////////////////////////////////////

IDIS_DLLFUNC bool IDISAPI admin_getStatus(IDISHADMIN hAdmin, int channel, StatusInfo* status);
IDIS_DLLFUNC bool IDISAPI admin_getPeerVersion(IDISHADMIN hAdmin, int channel, VERSION_INFO* version);
IDIS_DLLFUNC bool IDISAPI admin_getSystemLog(IDISHADMIN hAdmin, int channel, int index, SYSTEM_LOG* log);
IDIS_DLLFUNC bool IDISAPI admin_getSystemLogEx(IDISHADMIN hAdmin, int channel, int index, SYSTEM_LOG_EX* log);
IDIS_DLLFUNC bool IDISAPI admin_getRemoteSystemLog(IDISHADMIN hAdmin, int channel, int index, REMOTE_LOG_SYSTEM* log);
IDIS_DLLFUNC bool IDISAPI admin_getEventLog(IDISHADMIN hAdmin, int channel, int index, EVENT_LOG* log);
IDIS_DLLFUNC bool IDISAPI admin_getEventLogEx(IDISHADMIN hAdmin, int channel, int index, EVENT_LOG_EX* log);
IDIS_DLLFUNC bool IDISAPI admin_getRemoteEventLog(IDISHADMIN hAdmin, int channel, int index, REMOTE_LOG_EVENT* log);
IDIS_DLLFUNC bool IDISAPI admin_getEventInfoCommon(IDISHADMIN hAdmin, EVENT_INFO_COMMON *event);
IDIS_DLLFUNC bool IDISAPI admin_getLocalDateTime(IDISHADMIN hAdmin, int channel, DATE_TIME* dt);
IDIS_DLLFUNC bool IDISAPI admin_getDeviceDateTime(IDISHADMIN hAdmin, int channel, DATE_TIME* dt);

/////////////////////////////////////////////////////////////////////////////

IDIS_DLLFUNC bool IDISAPI admin_getCallbackPeerName(IDISHADMIN hAdmin, int channel, char *peerName);
IDIS_DLLFUNC bool IDISAPI admin_requestSystemCheck(IDISHADMIN hAdmin, int channel);
IDIS_DLLFUNC int IDISAPI admin_getUserAuthority(IDISHADMIN hAdmin, int channel);
IDIS_DLLFUNC int IDISAPI admin_getUserLoginLevel(IDISHADMIN hAdmin, int channel);
IDIS_DLLFUNC void IDISAPI admin_restartCallbackServer(IDISHADMIN hAdmin, int callbackPort);
IDIS_DLLFUNC bool IDISAPI admin_setDeviceDateTime(IDISHADMIN hAdmin, int channel, DATE_TIME& dt);
IDIS_DLLFUNC bool IDISAPI admin_getConnectionInfo(IDISHADMIN hAdmin, int channel, void* buffer);

/////////////////////////////////////////////////////////////////////////////

IDIS_DLLFUNC bool IDISAPI admin_getRemoteConfiguration(IDISHADMIN hAdmin, int channel, REMOTE_CONFIGURATION* configuration);
IDIS_DLLFUNC bool IDISAPI admin_getRemoteConfigurationModifyResult(IDISHADMIN hAdmin, int channel, REMOTE_CONFIGURATION_RESULTS* result);

IDIS_DLLFUNC bool IDISAPI admin_getRemoteDiskInfo(IDISHADMIN hAdmin, int channel, DISK_INFO* disks, int length, int* count);
IDIS_DLLFUNC bool IDISAPI admin_getAvailableRecordingTime(IDISHADMIN hAdmin, int channel, unsigned long long* calcRecTime, float eventrate[]);

/////////////////////////////////////////////////////////////////////////////

IDIS_DLLFUNC bool IDISAPI admin_exportSetupFile(IDISHADMIN hAdmin, int channel, LPCTSTR path);
IDIS_DLLFUNC bool IDISAPI admin_importSetupFile(IDISHADMIN hAdmin, int channel, LPCTSTR path);

// returns fail if 
//  : target buffer size mismatch
//      or unsupported query type.
IDIS_DLLFUNC bool IDISAPI admin_getProductInfo(IDISHADMIN hAdmin, int channel, int queryType, void* target, unsigned int targetSize);

/////////////////////////////////////////////////////////////////////////////
IDIS_DLLFUNC int IDISAPI admin_showRemoteSetupFromDllPath(IDISHADMIN hAdmin, int channel, int size, const char* dllPath);
IDIS_DLLFUNC int IDISAPI admin_showRemoteSetup(IDISHADMIN hAdmin, int channel, int size);

/////////////////////////////////////////////////////////////////////////////

IDIS_DLLFUNC bool IDISAPI admin_checkUserPassword(IDISHADMIN hAdmin, int channel, const char* name, const char* password);

/////////////////////////////////////////////////////////////////////////////

IDIS_DLLFUNC void IDISAPI admin_setLoggerProperties(unsigned char logType, unsigned char logLevel);
IDIS_DLLFUNC int IDISAPI admin_getCountAvailableHandle(void);
IDIS_DLLFUNC int IDISAPI admin_getCountAvailableChannel(IDISHADMIN hAdmin);

/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

/////////////////////////////////////////////////////////////////////////////

#endif  // !_IDIS_ADMINSDK_INTERFACE_
