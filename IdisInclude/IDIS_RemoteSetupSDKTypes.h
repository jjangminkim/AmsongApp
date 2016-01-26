#ifndef _IDIS_REMOTE_SETUP_SDK_TYPES_H_
#define _IDIS_REMOTE_SETUP_SDK_TYPES_H_

typedef struct _tag_field_info {
    enum {
        MAX_FIELD = 256,
    };
    bool fieldUsed[MAX_FIELD];

    void reset() {
        memset(fieldUsed, 0, MAX_FIELD);
    }
    _tag_field_info() {
        reset();
    }
} FieldInfo;

typedef struct {
    enum {
        FKEY_SITENAME = 0, FKEY_SYSTEMID, FKEY_SYSLANGUAGE,
        FKEY_MAX,
    };

    enum {  // language
        LANGUAGE_UNKNOWN        = 0,
        /////////////////////////////////

        LANGUAGE_ENGLISH        = 1,
        LANGUAGE_FRENCH,
        LANGUAGE_GERMAN,
        LANGUAGE_ITALIAN,
        LANGUAGE_SPANISH,
        LANGUAGE_DANISH,
        LANGUAGE_DUTCH,
        LANGUAGE_POLISH,
        LANGUAGE_PORTUGUESE,
        LANGUAGE_SWEDISH,
        LANGUAGE_HUNGARIAN,
        LANGUAGE_CZECH,
        LANGUAGE_RUSSIAN,
        LANGUAGE_FINNISH,
        LANGUAGE_TURKISH,
        LANGUAGE_ENGLISH_UK,

        LANGUAGE_KOREAN         = 20,
        LANGUAGE_JAPANESE,
        LANGUAGE_CHINESE_S,
        LANGUAGE_CHINESE_T,

        /////////////////////////////////////
        max_language_count_plus_1,
        MAX_LANGUAGE_COUNT = max_language_count_plus_1 - 1
    };

    char siteName[32];
    int  systemId;
    int  systemLanguage;
    FieldInfo fieldInfo;
} IDIS_CONFIG_SYSINFO;

typedef struct {
    enum {
        FKEY_ON = 0, FKEY_TITLE, FKEY_COVERTLEVEL,
        FKEY_MAX,
    };
    enum {
        MAX_CAMERA_TITLE_LENGTH = 31,
    };

    char isOn;                  // 0 for off 1 for on
    char title[MAX_CAMERA_TITLE_LENGTH + 1];
    char covertLevel;           // 0 = NORMAL, 1 = COVERT_1, 2 = COVERT_2
    FieldInfo fieldInfo;
} IDIS_CONFIG_CAMERA_GENERAL;

typedef struct {
    enum {
        FKEY_TRANS_SPEED = 0, FKEY_TRANS_UNIT, FKEY_RESOLUTION, FKEY_BANDWIDTH,
        FKEY_MAX,
    };
    enum {
        TRANSFER_UNIT_BPS,
        TRANSFER_UINT_IPS,
    };
    enum {
        RESOLUTION_STANDARD,
        RESOLUTION_HIGH,
        RESOLUTION_VERY_HIGH,
        MAX_RESOLUTION_COUNT,
    };

    int transferSpeed;
    int transferUnit;
    int resolution;
    int bandwidthBps;
    FieldInfo fieldInfo;
} IDIS_CONFIG_NETWORK_COMMON;

typedef  struct {
    enum {
        FKEY_IPADDR = 0, FKEY_GATEWAY, FKEY_SUBNET, FKEY_DNS,
        FKEY_ADMIN_PORT, FKEY_WATCH_PORT, FKEY_SEARCH_PORT, FKEY_AUDIO_PORT,
        FKEY_MAX,
    };
    enum {
        MAX_ADDR_LEN = 15,
    };

    char ipAddress[MAX_ADDR_LEN+1];
    char gateway[MAX_ADDR_LEN+1];
    char subnetMask[MAX_ADDR_LEN+1];
    char dnsServer[MAX_ADDR_LEN+1];
    int adminPort;
    int watchPort;
    int searchPort;
    int audioPort;
    FieldInfo fieldInfo;
} IDIS_CONFIG_NETWORK_LAN;

typedef struct {
    enum {
        FKEY_USEDVRNS = 0, FKEY_USENAT, FKEY_DVRNSPORT, FKEY_DVRNSSERVER, FKEY_DVRNAME,
        FKEY_MAX,
    };
    enum {
        MAX_DVRNS_SERVER_LENGTH = 63,
        MAX_DVRNS_DVR_NAME_LENGTH = 63,
    };

    bool useDvrns;
    bool useNat;
    int  dvrnsServerPort;
    char dvrnsServer[MAX_DVRNS_SERVER_LENGTH+1];
    char dvrName[MAX_DVRNS_DVR_NAME_LENGTH+1];
    FieldInfo fieldInfo;
} IDIS_CONFIG_NETWORK_DVRNS;

typedef struct {
    enum {
        FKEY_RECORD_CHANNELS, FKEY_ALARM_OUT, FKEY_NOTIFY_MAIL,
        FKEY_NOTIFY_LANCALLBACK, NOTIFY_ALERTWINDOW, NOFITY_DIGITAL_DETERRENT,
        FKEY_MAX,
    };
    enum {
        MAX_RECORD_CHANNEL = 32,
        MAX_ALARM_OUT = 17,
        MAX_LAN_CALLBACK = 5,
    };

    bool recordChannel[MAX_RECORD_CHANNEL];
    bool alarmOut[MAX_ALARM_OUT];      // last index is for beeping
    bool notifyMail;
    bool notifyLanCallback[MAX_LAN_CALLBACK];
    bool notifyAlertWindow;
    bool notifyDigitalDeterrent;
    FieldInfo fieldInfo;
} IDIS_CONFIG_EVENT_ACTION;

typedef struct {
    enum {
        FKEY_ACTION,
        FKEY_MAX,
    };
    IDIS_CONFIG_EVENT_ACTION action;
    FieldInfo fieldInfo;
} IDIS_CONFIG_EVENT_VIDEOLOSS_ITEM;

typedef struct {
    enum {
        FKEY_OBSCURATION, FKEY_VIDEO_LOSS_ITEMS,
        FKEY_MAX,
    };
    enum {
        MAX_VIDEOLOSS_ITEMS = 32,
    };

    unsigned short obscuration;
    IDIS_CONFIG_EVENT_VIDEOLOSS_ITEM items[MAX_VIDEOLOSS_ITEMS];
    FieldInfo fieldInfo;
} IDIS_CONFIG_EVENT_VIDEOLOSS;

typedef struct {
    enum {
        FKEY_USE, FKEY_VIEWZONE, FKEY_SENSITIVITY_DAY, FKEY_SENSITIVITY_NIGHT,
        FKEY_MINBLOCK_DAY, FKEY_MINBLOCK_NIGHT, FKEY_MOTIONBLOCK, FKEY_ACTION,
        FKEY_MAX,
    };
    enum {
        MAX_GRID_BLOCK_X = 64, 
        MAX_GRID_BLOCK_Y = 64,
    };

    bool use;
    bool viewZone;
    unsigned int sensitivityDay;        // 1(Dull) ~ 5(Sensitive)
    unsigned int sensitivityNight;      // 1(Dull) ~ 5(Sensitive)
    unsigned int minBlockDay;           // number of blocks that detect as motion event.
    unsigned int minBlockNight;
    bool motionBlock[MAX_GRID_BLOCK_X][MAX_GRID_BLOCK_Y];
    IDIS_CONFIG_EVENT_ACTION action;
    FieldInfo fieldInfo;
} IDIS_CONFIG_EVENT_MOTION_ITEM;

typedef struct {
    enum {
        FKEY_GRID_SIZE_X, FKEY_GRID_SIZE_Y, FKEY_IGNORING_TIME,
        FKEY_DAYTIME_BEGIN, FKEY_DAYTIME_END, FKEY_MOTION_ITEMS,
        FKEY_MAX,
    };
    enum {
        MAX_MOTION_ITEMS = 32,
    };
    unsigned int dayTimeBeign;      // minutes from 00:00
    unsigned int dayTimeEnd;        // eg.) 600 -> 10:00, 1230 -> 8:30
    int ignoringTime;            // 1~10 sec. 0 for don't use
    int gridSizeX;                  // number of motion detect block (not modifiable)
    int gridSizeY;                  // number of motion detect block (not modifiable)
    IDIS_CONFIG_EVENT_MOTION_ITEM items[MAX_MOTION_ITEMS];
    FieldInfo fieldInfo;
} IDIS_CONFIG_EVENT_MOTION;

typedef struct {
    enum {
        MAX_TITLE_LENGTH = 31,
    };
    enum {
        TYPE_NC, TYPE_NO,
    };
    enum {
        FKEY_ENABLE, FKEY_TITLE, FKEY_TYPE, FKEY_ACTION,
        FKEY_MAX,
    };

    bool enable;
    char title[MAX_TITLE_LENGTH + 1];
    unsigned char type;
    IDIS_CONFIG_EVENT_ACTION action;
    FieldInfo fieldInfo;
} IDIS_CONFIG_EVENT_ALARMIN_ITEM;

typedef struct {
    enum {
        MAX_ALARMIN_ITEM = 32,
    };
    enum {
        FKEY_PANIC_ALARM, FKEY_ALARMIN_ITEMS,
        FKEY_MAX,
    };

    char panicAlarm; // < 0 for don't use
    IDIS_CONFIG_EVENT_ALARMIN_ITEM items[MAX_ALARMIN_ITEM];
    FieldInfo fieldInfo;
} IDIS_CONFIG_EVENT_ALARMIN;

typedef struct {
    enum {
        FKEY_BLACK_SENSITIVITY, FKEY_WHITE_SENSITIVITY, FKEY_ACTIVATION_TIME,
        FKEY_ACTION,
    };

    unsigned char blackSensitivity;
    unsigned char whiteSensitivity;
    short activataionTime; // < 0 for none.
    IDIS_CONFIG_EVENT_ACTION action;
    FieldInfo fieldInfo;
} IDIS_CONFIG_EVENT_VIDEOBLIND_ITEM;

typedef struct {
    enum {
        FKEY_USE_IGNORING_TIME, FKEY_IGNORETIME_BEGIN, FKEY_IGNORETIME_END,
        FKEY_VIDEOBLIND_ITEMS,
        FKEY_MAX,
    };
    enum {
        MAX_VIDEOBLIND_ITEM = 32,
    };
    bool useIgnoringTime;
    unsigned int ignoreTimeBegin;
    unsigned int ignoreTimeEnd;
    IDIS_CONFIG_EVENT_VIDEOBLIND_ITEM items[MAX_VIDEOBLIND_ITEM];
    FieldInfo fieldInfo;
} IDIS_CONFIG_EVENT_VIDEOBLIND;

typedef struct {
    enum {
        FKEY_SOUND_NUMBER,
        FKEY_MAX,
    };
    int soundNumber;
    FieldInfo fieldInfo;
} IDIS_CONFIG_AUDIO_ALARM_SETTING;

typedef struct {
    enum {
        FKEY_BEGIN_TIME, FKEY_END_TIME, FKEY_AUDIO_ALARM_SETTINGS,
        FKEY_MAX,
    };
    enum {
        MAX_AUDIO_ALARM_SETTINGS = 32,
    };

    unsigned int beginTime;        // minutes from 00:00
    unsigned int endTime;          // minutes from 00:00
    IDIS_CONFIG_AUDIO_ALARM_SETTING audioAlarmSetting[MAX_AUDIO_ALARM_SETTINGS];
    FieldInfo fieldInfo;
} IDIS_CONFIG_AUDIO_ALARM;



// product info query types
// for product capability & information
const int QUERY_CAMERA_COUNT                    = 1;    // unsigned char
const int QUERY_ALARMIN_COUNT                   = 2;    // unsigned char
const int QUERY_ALARMOUT_COUNT                  = 3;    // unsigned char
const int QUERY_TEXTIN_COUNT                    = 4;    // unsigned char
const int QUERY_AUDIO_IN_COUNT                  = 5;    // unsigned char
const int QUERY_AUDIO_OUT_COUNT                 = 6;    // unsigned char
const int QUERY_SUPPORT_EVENT_LOG               = 7;    // bool
const int QUERY_SUPPORT_PARTIAL_SETUP           = 8;    // bool
const int QUERY_MAC_ADDRESS                     = 21;    // 18 bytes including NULL char
const int QUERY_SW_BUILD                        = 22;    // at least 8 bytes including NULL char
const int QUERY_SW_VERSION                      = 23;   // at least 13 bytes including NULL char
const int QUERY_ADMIN_CONNECTABLE               = 24;   // bool
const int QUERY_WATCH_CONNECTABLE               = 25;   // bool
const int QUERY_SEARCH_CONNECTABLE              = 26;   // bool
const int QUERY_AUDIO_CONNECTABLE               = 27;   // bool
const int QUERY_ADMIN_PORT                      = 28;   // unsigned short
const int QUERY_WATCH_PORT                      = 29;   // unsigned short
const int QUERY_SEARCH_PORT                     = 30;   // unsigned short
const int QUERY_AUDIO_PORT                      = 31;   // unsigned short
const int QUERY_PRODUCT_ID                      = 32;   // unsigned int
const int QUERY_SUPPORT_EVENT_LOG_FILTER        = 33;   // unsigned char
const int QUERY_NAME                            = 34;   // at least 16 bytes including NULL char
const int QUERY_SEARCH_TICK_TYPE                = 35;   // unsigned char

#endif // _IDIS_REMOTE_SETUP_SDK_TYPES_H_