#ifndef _REMOTE_SETUP_SDK_TYPES_H_
#define _REMOTE_SETUP_SDK_TYPES_H_

// LOCAL_CONST Structure.
// LocalSetup에서 worker를 통해서 가져온 
// 각 Local의 const 값을 저장한다.
typedef struct {
    unsigned int  maxUserGroupCount;
    unsigned int  maxUserCount;
    unsigned char maxUserGroupNameLength;
    unsigned char maxUserNameLength;

    unsigned int  maxRecordScheduleCount;
} LOCAL_CONSTS;

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
        FKEY_SITENAME = 0, FKEY_SYSTEMID, FKEY_SYSLANGUAGE, FKEY_SERIAL_NUMBER, 
        FKEY_SYSTIMEZONE, FKEY_SYSTIMEZONE_DST, 
        FKEY_MAX,
    };
    enum {
        MAX_SITENAME_LEN = 31, // w/o null
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

    enum {  // Time Zone
        Eniwetok_Kwajalein = 0,
        MidwayIsland_Samoa,
        Hawaii,
        Alaska,
        PacificTime_Tijuana,
        MountainTime,
        Arizona,
        Chihuahua_Mazatlan,
        MexicoCity_Tegucigalpa,
        Saskatchewan,
        CentralTime,
        CentralAmerica,
        EasternTime,
        Bogota_Lima_Quito,
        Indiana,
        AtlanticTime,
        Santiago,
        Caracas_LaPaz,
        Newfoundland,
        Greenland,
        BuenosAires_Georgetown,
        Brasilia,
        MidAtlantic,
        CapeVerdeIs,
        Azores,
        Greenwich_Dublin_Edinburgh_Lisbon_London,
        Casablanca_Monrovia,
        Belgrade_Bratislava_Budapest_Ljubljana_Prague,
        Brussels_Copenhagen_Madrid_Paris_Vilnius,
        Sarajevo_Skopje_Sofija_Warsaw_Zagreb,
        WestCentralAfrica,
        Amsterdam_Berlin_Bern_Rome_Stockholm_Vienna,
        Bucharest,
        Athens_Istanbul_Minsk,
        Jerusalem,
        Cairo,
        Harare_Pretoria,
        Helsinki_Riga_Tallinn,
        Nairobi,
        Moscow_StPetersburg_Volgograd,
        Baghdad_Kuwait_Riyadh,
        Kuwait_Riyadh,
        Tehran,
        Baku_Tbilisi,
        AbuDhabi_Muscat,
        Kabul,
        Ekaterinburg,
        Islamabad_Karachi_Tashkent,
        Bombay_Calcutta_Madras_NewDelhi,
        Kathmandu,
        SriJayawardenepura,
        Astana_Almaty_Dhaka,
        Almaty_Novosiirsk,
        Rangoon,
        Bangkok_Hanoi_Jakarta,
        Krasnoyarsk,
        Beijing_Chongqing_HongKong_Urumqi,
        Irkutsk_UlaanBataar,
        Singapore,
        Taipei,
        Perth,
        Seoul,
        Yakutsk,
        Osaka_Sapporo_Tokyo,
        Darwin,
        Adelaide,
        Guam_PortMoresby,
        Brisbane,
        Vladivostok,
        Canberra_Melbourne_Sydney,
        Hobart,
        Magadan_SolomonIs_NewCaledonia,
        Auckland_Wellington,
        Fiji_Kamchatka_MarshallIs,
        Nukualofa,
        PacificTime,

        MAX_TIME_ZONE_COUNT
    };
    
    char siteName[MAX_SITENAME_LEN + 1];
    int  systemId;
    int  systemLanguage;
    char systemSerialNumber[MAX_SITENAME_LEN + 1];
    unsigned int systemTimeZone;
    unsigned char systemTimeZoneDst;
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_SYSINFO;

typedef struct {
    enum {
        FKEY_DELAY_START = 0,
        FKEY_MAX,
    };

    bool powerDelayStart;
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_SYS_POWER;

typedef struct {
    enum {
        MAX_GROUPNAME_LEN = 31,        
    };
    enum {
        FEKY_GROUP_ID, FKEY_GROUP_NAME,
        FKEY_SHUTDOWN, FKEY_UPGRADE, FKEY_COLOR_CONTROL, FKEY_SYSTEM_CHECK,
        FKEY_PTZ_CONTROL, FKEY_ALARM_OUT_CONTORL, FKEY_COVERT_CAMERA_VIEW, FKEY_DIGITAL_DET_CONTROL,
        FKEY_SEARCH, 
        FKEY_CLIP_COPY,
        FKEY_SETUP, 
        FKEY_SYSTEM_TIME_CHANGE, FKEY_DATA_CLEAR, FKEY_PTZ_SETUP, FKEY_ALARM_OUT_SETUP,
        FKEY_COVERT_CAMERA_SETUP, FKEY_RECORD_SETUP, FKEY_SETUP_IMPORT, FKEY_SETUP_EXPORT,
        FKEY_DIGITAL_DET_SETUP, FKEY_VNC_SETUP, FKEY_POWER_MANAGEMENT,
        FKEY_MAX,
    };
    unsigned int groupId;
    char groupName[MAX_GROUPNAME_LEN + 1];
    bool authShutdown;
    bool authUpgrade;
    bool authColorControl;
    bool authSystemCheck;
    bool authPtzControl;
    bool authAlarmOutControl;
    bool authCovertCameraView;
    bool authDigitalDetControl;
    bool authSearch;
    bool authClipCopy;
    bool authSetup;
    bool authSystemTimeChange;
    bool authDataClear;
    bool authPtzSetup;
    bool authAlarmOutSetup;
    bool authCovertCameraSetup;
    bool authRecordSetup;
    bool authSetupImport;
    bool authSetupExport;
    bool authDigitalDetSetup;
    bool authVncSetup;
    bool authPowerManagement;
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_USER_USER_GROUP;

typedef struct {
    enum {
        MAX_USER_NAME_LEN     = 31,
        MAX_USER_PASSWORD_LEN = 31,
    };
    enum {
        FKEY_USER_GROUP_ID, FKEY_USER_NAME, FKEY_USER_PASSWORD,
        FKEY_MAX,
    };

    unsigned int userGroupId;
    char userName[MAX_USER_NAME_LEN + 1];
    char userPassword[MAX_USER_PASSWORD_LEN + 1];
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_USER_USER;

typedef struct {
    enum {
        MAX_USER_GROUP_ENTRY = 64,
        MAX_USER_ENTRY       = 256,        
    };
    enum {
        FKEY_GROUP_INFO, FKEY_USER_INFO, FKEY_AUTO_LOGIN, FKEY_AUTO_LOGOUT,        
        FKEY_MAX,
    };

    REMOTESETUP_CONFIG_USER_USER_GROUP userGroups[MAX_USER_GROUP_ENTRY];
    REMOTESETUP_CONFIG_USER_USER userUsers[MAX_USER_ENTRY];
    unsigned int userAutoLogin;
    unsigned char userAutoLogout;

    unsigned char groupCount;
    unsigned char userCount;
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_USER;

typedef struct {
    bool statRemoteControl;
    bool statZoom;
    bool statNetwork;
    bool statFreezeSequence;
    bool statScreenGroup;
    bool statFreeSpace;
    bool statArchive;
    bool statMirror;
    bool statDate;
    bool statTime;
    bool statUserName;
    bool statBackgroundPanel;
    bool camNo;
    bool camTitle;
    bool camRecord;
    bool camAudio;
    bool camPtz;
    bool camTextIn;
    unsigned short camDisplayDwell;
    bool camNotConnReason;
    
    enum {
        FKEY_REMOTE_CONTROL, FKEY_ZOOM, FKEY_NETWORK, FKEY_FREEZE_SEQ, FKEY_SCREEN_GROUP, FKEY_FREE_SPACE,
        FKEY_ARCHIVE, FKEY_MIRROR, FKEY_DATE, FKEY_TIME, FKEY_USERNAME, FKEY_BACKGROUND_PANEL,
        FKEY_CAMNO, FKEY_CAMTITLE, FKEY_CAMRECORD, FKEY_CAMAUDIO, FKEY_CAMPTZ, FKEY_CAMTEXTIN,
        FKEY_CAMDISPLAY_DWELL, FKEY_DISCONN_REASON, FKEY_SPOT_MONITOR_USE, FKEY_SPOT_MONITOR_DWELL,
        FKEY_MAX
    };

    FieldInfo fieldInfo;

} REMOTESETUP_CONFIG_DISPLAY_OSD;

typedef struct {
    enum {
        MAX_CAMERA_NUMBER = 32,
    };

    unsigned char primarySeqMode;
    unsigned short primarySeqInterval;
    unsigned char primaryEventMonitoringOn;
    unsigned char secondarySeqMode;
    unsigned short secondarySeqInterval;
    bool spotMonitorUse[MAX_CAMERA_NUMBER];
    unsigned short spotMonitorDwellTime[MAX_CAMERA_NUMBER];

    enum {
        FKEY_PRIMARY_SEQ_MODE, FKEY_PRIMARY_SEQ_INTERVAL, FKEY_EVENT_MONITORING, 
        FKEY_SECONDARY_SEQ_MODE, FKEY_SECONDARY_SEQ_INTERVAL, 
        FKEY_SPOT_MONITOR_USE, FKEY_SPOT_MONITOR_DWELL_TIME,
        FKEY_MAX,
    };

    FieldInfo fieldInfo;

} REMOTESETUP_CONFIG_DISPLAY_MONITOR;

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
} REMOTESETUP_CONFIG_CAMERA_GENERAL;
/*
typedef struct {
    typedef struct {

    } CAMERA_ITEM;

} REMOTESETUP_CONFIG_CAMERA_GENERAL;

typedef struct {

} REMOTESETUP_CONFIG_CAMERA_PTZ;
*/
typedef struct {
    enum BaudRate { // serial comm. (ptz, text-in, etc.)
        BRATE_300, BRATE_600, BRATE_1200, BRATE_2400, BRATE_4800, BRATE_9600, BRATE_19200, BRATE_38400,
        BRATE_57600, BRATE_115200, MAX_BRATE,
    };
    enum SerialPort {
        PORT_NONE, PORT_RS232, PORT_RS485, MAX_PORT,
    };
    enum Parity { // serial comm. (ptz, text-in, etc.)
        PTY_NONE, PTY_ODD, PTY_EVEN, MAX_PARITY,
    };
    enum {
        MAX_CAMERA_NUMBER = 32,
        MAX_PTZ_ITEMS = 256,
    };
    enum {
        FKEY_PORTTYPE, FKEY_BAUDRATE, FKEY_DATABIT, FKEY_STOPBIT, FKEY_PARITY,
        FKEY_PRODUCTMODEL, FKEY_PTZID,
        FKEY_MAX,
    };

    unsigned char  ptzPortType;
    unsigned char  ptzBaudRate;
    unsigned char  ptzDataBit;
    unsigned char  ptzStopBit;
    unsigned char  ptzParity;
    unsigned char  ptzProductModel[MAX_CAMERA_NUMBER];    // selected ptz product (one of productId in REMOTE_CONFIG_SUPPORTED_PTZ_INFO array)
    unsigned short ptzId[MAX_CAMERA_NUMBER];  // user can assign id for each camera

    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_CAMERA_PTZ;

typedef struct {
    enum {
        MAX_ALARM_OUT_TITLE_LENGTH = 31,
    };
    enum {
        FKEY_TITLE, FKEY_TYPE, FKEY_MAX,
    };

    char title[MAX_ALARM_OUT_TITLE_LENGTH];
    unsigned char type;
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_ALARM_OUT_ITEM;

typedef struct {
    enum {
        MAX_ALARM_OUT_COUNT = 35,
    };
    enum {
        FKEY_DWELL_TIME, FKEY_ALARM_OUT_ITEMS,
        FKEY_MAX,
    };

    unsigned short dwellTime;
    REMOTESETUP_CONFIG_ALARM_OUT_ITEM alarmOutItems[MAX_ALARM_OUT_COUNT];
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_ALARM_OUT;

typedef struct {
    enum {
        MAX_CAMERA_NUMBER = 32,
    };
    enum {
        FKEY_ASSOCIATED_CAM, FKEY_MAX,
    };
    
    unsigned char associatedCameras[MAX_CAMERA_NUMBER];
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_AUDIO_IN;

typedef struct {
    enum {
        FKEY_ENABLE, FKEY_MAX,
    };

    unsigned char enable;
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_AUDIO_OUT;

typedef struct {
    enum {
        MAX_AUDIO_IN    = 4,
        MAX_AUDIO_OUT   = 2,
    };
    enum {
        FKEY_AUDIO_IN, FKEY_AUDIO_OUT,
        FKEY_MAX,
    };

    REMOTESETUP_CONFIG_AUDIO_IN audioIn[MAX_AUDIO_IN];
    REMOTESETUP_CONFIG_AUDIO_OUT audioOut[MAX_AUDIO_OUT];
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_AUDIO;

// members of this struct cannot be modified.
// just for showing names on UI
typedef struct {
    enum {
        MAX_PTZ_PRODUCT_NAME_LEN = 63, // wo/o null
    };

    char productName[MAX_PTZ_PRODUCT_NAME_LEN + 1];
    unsigned short productId;   // unique id for each ptz product
} REMOTESETUP_CONFIG_SUPPORTED_PTZ_INFO;

typedef struct {
    enum {
        FKEY_TRANS_SPEED = 0, FKEY_TRANS_SPEED_IPS, FKEY_TRANS_UNIT, FKEY_RESOLUTION, FKEY_BANDWIDTH, FKEY_QUALITY, FKEY_REMOTE_AUDIO_CHANNEL, FKEY_SSL_STATE,
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
    float transferSpeedIps;
    int transferUnit;
    int resolution;
    int bandwidthBps;
    unsigned char quality;
    unsigned char remoteAudioChannel;
    unsigned char sslState;
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_NETWORK_COMMON;

typedef struct {
    enum {
        FKEY_TYPE = 0, FKEY_IPADDR, FKEY_GATEWAY, FKEY_SUBNET, FKEY_DNS,
        FKEY_USE_AUTO_DNS_SERVER, FKEY_ADSL_ID, FKEY_ADSL_PASSWORD, FKEY_USE_UPNP,
        FKEY_ADMIN_PORT, FKEY_WATCH_PORT, FKEY_SEARCH_PORT, FKEY_AUDIO_PORT, FKEY_CALLBACK_PORT,
        FKEY_MAX,
    };
    enum {
        MAX_ADDR_LEN = 15,
        MAX_ID_LEN = 63,
        MAX_PASSWORD_LEN = 63,
    };

    unsigned char lanType;
    char ipAddress[MAX_ADDR_LEN+1];
    char gateway[MAX_ADDR_LEN+1];
    char subnetMask[MAX_ADDR_LEN+1];
    char dnsServer[MAX_ADDR_LEN+1];
    bool useAutoDnsServer;    
    char adslId[MAX_ID_LEN+1];
    char adslPassword[MAX_ID_LEN+1];
    bool useUpnp;
    int adminPort;
    int watchPort;
    int searchPort;
    int audioPort;
    int callbackPort;
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_NETWORK_LAN;

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
} REMOTESETUP_CONFIG_NETWORK_DVRNS;

typedef struct {
    enum {
        FKEY_USE_RTSP = 0, FKEY_RTSP_PORT_NUMBER, 
        FKEY_RTP_START_PORT_NUMBER, FKEY_RTP_END_PORT_NUMBER,
        FKEY_USE_MOBILE, FKEY_ALLOW_ANONYMOUS_USERS,
        FKEY_MAX,
    };

    bool useRtsp;
    int rtspPortNumber;
    int rtpStartPortNumber;
    int rtpEndPortNumber;
    bool useMobile;
    bool allowAnonymousUsers;
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_NETWORK_RTSP;

typedef struct {
    enum {
        FKEY_USE_WEB_GUARD = 0, FKEY_USE_HTTPS,
        FKEY_WEB_GUARD_PORT_NUMBER,
        FKEY_MAX,
    };

    bool useWebGuard;
    bool useHttps;
    int webGuardPortNumber;
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_NETWORK_WEB_GUARD;

typedef struct {
    enum {
        FKEY_CALLBACK_ITEM_IP = 0, FKEY_CALLBACK_ITEM_PORT,
        FKEY_MAX,
    };
    enum {
        MAX_IP_LEN = 32,
    };

    char callbackIpAddress[MAX_IP_LEN+1];
    unsigned int callbackPort;
    FieldInfo fieldeInfo;
} REMOTESETUP_CONFIG_NETWORK_CALLBACK_SERVER_ITEMS;

typedef struct {
    enum {
        FKEY_USE_CALLBACK_SERVER = 0,
        FKEY_CALLBACK_IPS, FKEY_CALLBACK_PORTS, FKEY_CALLBACK_RETRY,
        FKEY_MAX,
    };
    enum {
        MAX_ITEM_NUM = 5,
    };

    bool useCallbackServer;
    unsigned int retry;
    REMOTESETUP_CONFIG_NETWORK_CALLBACK_SERVER_ITEMS items[MAX_ITEM_NUM];
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_NETWORK_CALLBACK_SERVER;

typedef struct {
    enum {
        MAX_MAIL_RECIPIENTS = 32,
        MAX_SMTP_SERVER_LEN = 63,  // w/o null
        MAX_MAIL_ADDR_LEN = 63,    // w/o null
        MAX_MAIL_USER_PW_LEN = 31, // w/o null
    };
    enum {
        FKEY_USE_MAIL, FKEY_USE_SMTPLOGIN, FKEY_USE_SMTPTLS, FKEY_SMTPPORT,
        FKEY_SMTPSERVER, FKEY_SENDER, FKEY_SMTPUSER, FKEY_SMTPPASSWORD, FKEY_RECIPIENTS,
        FKEY_MAX,
    };

    bool useMail;
    bool useSmtpLogin;
    bool useSmtpTls;
    unsigned int smtpPort;
    char smtpServer[MAX_SMTP_SERVER_LEN + 1];
    char sender[MAX_MAIL_ADDR_LEN + 1];
    char smtpUser[MAX_MAIL_USER_PW_LEN + 1];
    char smtpPassword[MAX_MAIL_USER_PW_LEN + 1];
    char recipients[MAX_MAIL_RECIPIENTS][MAX_MAIL_ADDR_LEN + 1];
    unsigned int recipientCount;
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_NETWORK_EMAIL;

// general schedule
typedef struct {
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
        MAX_DAY_TYPE,
    };
    enum {
        FKEY_DAY, FKEY_BEGIN, FKEY_END,
        FKEY_MAX,
    };

    unsigned char day;
    unsigned int begin;
    unsigned int end;
    FieldInfo fieldInfo;
} REMOTESETUP_GENERAL_SCHEDULE_ITEM;

typedef struct {
    enum SnsType {
        TWITTER,
        MAX_SNS_TYPES,
    };
    enum {
        MAX_USER_PASSWD_LEN = 31,   // w/o null
        MAX_SNS_ENTRY = 32,
    };
    enum {
        FKEY_USE, FKEY_SNSTYPE, FKEY_SNSUSERNAME, FKEY_SNSPASSWORD,
        FKEY_MAX,
    };

    bool _use;
    unsigned int _snsType;
    char _snsUserName[MAX_USER_PASSWD_LEN + 1];
    char _snsPassword[MAX_USER_PASSWD_LEN + 1];

    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_NETWORK_SNS_ITEM;

typedef struct {
    enum {
        FKEY_RECORD_CHANNELS, FKEY_ALARM_OUT, FKEY_NOTIFY_MAIL, FKEY_NOTIFY_LANCALLBACK, FKEY_PTZ_PRESET_ALL_CAMERA,
        FKEY_NOTIFY_SNS, FKEY_NOTIFY_ALERTWINDOW, FKEY_NOTIFY_SUMMARY, FKEY_SPOT_MONITOR,         
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
    unsigned char ptzPresetAllCamera[MAX_RECORD_CHANNEL];
    bool notifySns;
    bool notifyAlertWindow;
    bool notifySummary;
    unsigned char spotMonitor;
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_EVENT_ACTION;

typedef struct {
    enum {
        FKEY_ANALOG_INTERVALS,
        FKEY_ACTION,
        FKEY_MAX,
    };
    
    float analogInterval;
    REMOTESETUP_CONFIG_EVENT_ACTION action;
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_EVENT_VIDEOLOSS_ITEM;

typedef struct {
    enum {
        FKEY_USE_IGNORING_TIME, FKEY_IGNORETIME_BEGIN, FKEY_IGNORETIME_END,
        FKEY_OBSCURATION, FKEY_VIDEO_LOSS_ITEMS,
        FKEY_MAX,
    };
    enum {
        MAX_VIDEOLOSS_ITEMS = 32,
    };

    bool           useIgnoringTime;
    unsigned int   ignoreTimeBegin;
    unsigned int   ignoreTimeEnd;
    unsigned short obscuration;
    
    REMOTESETUP_CONFIG_EVENT_VIDEOLOSS_ITEM items[MAX_VIDEOLOSS_ITEMS];
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_EVENT_VIDEOLOSS;

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
    REMOTESETUP_CONFIG_EVENT_ACTION action;
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_EVENT_MOTION_ITEM;

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
    REMOTESETUP_CONFIG_EVENT_MOTION_ITEM items[MAX_MOTION_ITEMS];
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_EVENT_MOTION;

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
    REMOTESETUP_CONFIG_EVENT_ACTION action;
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_EVENT_ALARMIN_ITEM;

typedef struct {
    enum {
        MAX_ALARMIN_ITEM = 48,
    };
    enum {
        FKEY_PANIC_ALARM, FKEY_ALARMIN_ITEMS,
        FKEY_MAX,
    };

    char panicAlarm; // < 0 for don't use
    REMOTESETUP_CONFIG_EVENT_ALARMIN_ITEM items[MAX_ALARMIN_ITEM];
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_EVENT_ALARMIN;

typedef struct {
    enum {
        FKEY_USE, FKEY_BLACK_SENSITIVITY, FKEY_WHITE_SENSITIVITY, FKEY_ACTIVATION_TIME,
        FKEY_ACTION,
    };

    bool use;
    unsigned char blackSensitivity;
    unsigned char whiteSensitivity;
    unsigned char activataionTime; // < 0 for none.
    REMOTESETUP_CONFIG_EVENT_ACTION action;
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_EVENT_VIDEOBLIND_ITEM;

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
    REMOTESETUP_CONFIG_EVENT_VIDEOBLIND_ITEM items[MAX_VIDEOBLIND_ITEM];
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_EVENT_VIDEOBLIND;

typedef struct {
    enum {
        MAX_TEXTIN_TITLE_LENGTH = 31,
    };
    enum {
        FKEY_TITLE, FKEY_TEXTINITEMCONFIG, FKEY_ACTION,
        FKEY_MAX,
    };
    typedef struct {
        enum {
            PORT_NONE, PORT_RS232, PORT_RS485,
            USB_SERIAL1, USB_SERIAL2, USB_SERIAL3, USB_SERIAL4,
            USB_SERIAL5, USB_SERIAL6, USB_SERIAL7, USB_SERIAL8,
            LAN1, LAN2, LAN3, LAN4, LAN5, LAN6, LAN7, LAN8,
            LAN9, LAN10, LAN11, LAN12, LAN13, LAN14, LAN15, LAN16,
            MAX_PORT,
        };
        enum {
            MAX_TRANS_WORD_LEN = 15,
            MAX_DELIMITER_LEN = 7,
            MAX_IGNORE_STRING_LEN = 31,
        };
        enum {
            FKEY_PORTCONFIG, FKEY_TEXTIN_PRODUCT, FKEY_ALLOWANYCHAR, FKEY_TRANSTART, 
            FKEY_TRANSEND, FKEY_MORELINES, FKEY_DELIMITER, FKEY_IGNORESTRING, 
            FKEY_CASESENSITIVE, FKEY_TIMEOUTSEC,
            FKEY_MAX,
        };
        typedef struct {
            enum {
                BRATE_300, BRATE_600, BRATE_1200, BRATE_2400, BRATE_4800,
                BRATE_9600, BRATE_19200, BRATE_38400, BRATE_57600, BRATE_115200,
                MAX_BRATE,
            };
            enum {
                PTY_NONE, PTY_ODD, PTY_EVEN,
                MAX_PARITY,
            };
            enum {
                FKEY_PTZPORT, FKEY_BAUDRATE, FKEY_DATABIT, FKEY_STOPBIT, FKEY_PARITY, FKEY_TCP_PORT,
                FKEY_MAX,
            };

            unsigned char portType;
            unsigned char baudRate;
            unsigned char dataBit;
            unsigned char stopBit;
            unsigned char parity;
            unsigned short tcpPort;
            FieldInfo fieldInfo;

        } REMOTESETUP_CONFIG_EVENT_TEXTIN_ITEM_PORT_CONFIG;

        REMOTESETUP_CONFIG_EVENT_TEXTIN_ITEM_PORT_CONFIG textInItemPortSetup;

        unsigned char   textInProduct; 
        bool            allowAnyCharacter;      // allow any character for transaction start
        char            transStart[MAX_TRANS_WORD_LEN + 1];
        char            transEnd[MAX_TRANS_WORD_LEN + 1];
        unsigned char   moreLines;
        char            delimiter[MAX_DELIMITER_LEN + 1];
        char            ignoreString[MAX_IGNORE_STRING_LEN + 1];
        bool            caseSensitive;
        unsigned int    timeOutSeconds;  // use only min, sec field (up to 15min.)
        FieldInfo fieldinfo;
    } REMOTESETUP_CONFIG_EVENT_TEXTIN_ITEM_CONFIG;

    char title[MAX_TEXTIN_TITLE_LENGTH + 1];
    REMOTESETUP_CONFIG_EVENT_TEXTIN_ITEM_CONFIG textInItemConfig;
    REMOTESETUP_CONFIG_EVENT_ACTION action;
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_EVENT_TEXTIN_ITEM;

typedef struct {
    enum {
        MAX_TEXTIN_ITEM = 16,
    };
    enum {
        FKEY_TEXTIN_ITEMS,
        FKEY_MAX,
    };

    REMOTESETUP_CONFIG_EVENT_TEXTIN_ITEM items[MAX_TEXTIN_ITEM];
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_EVENT_TEXTIN;


typedef struct {
    enum {
        INTERVAL_NEVER, INTERVAL_1M, INTERVAL_2M,   // 1M and 2M are only used on record check.(up to 7days)
        INTERVAL_1H, INTERVAL_2H, INTERVAL_3H, INTERVAL_4H, INTERVAL_5H,
        INTERVAL_6H, INTERVAL_7H, INTERVAL_8H, INTERVAL_9H, INTERVAL_10H,
        INTERVAL_11H, INTERVAL_12H, INTERVAL_18H, INTERVAL_1D, INTERVAL_7D,
        INTERVAL_15D, INTERVAL_30D,
        MAX_INTERVAL_TYPE,
    };    
    enum {
        FKEY_GENERAL_SCHEDULE, FKEY_INTERVAL,
        FKEY_MAX,
    };
    
    REMOTESETUP_GENERAL_SCHEDULE_ITEM generalSchedule;
    unsigned short interval;
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_EVENT_SYSTEM_RECORDING_CHECK_SCHEDULE_ITEM;

typedef struct {
    enum {
        MAX_SCHEDULE_ITEM = 20,
    };
    enum {
        FKEY_SCHEDULE_ON, FKEY_SCHEDULES,
        FKEY_MAX,
    };

    bool scheduleOn;
    unsigned char numSchedules;
    REMOTESETUP_CONFIG_EVENT_SYSTEM_RECORDING_CHECK_SCHEDULE_ITEM schedules[MAX_SCHEDULE_ITEM];
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_EVENT_SYSTEM_RECORDING_CHECK;

typedef struct {
    enum {
        MAX_ALARM_IN = 32,
    };
    enum {
        FKEY_INTERVALS,
        FKEY_MAX,
    };
    unsigned char  alarmInCheckCount;
    unsigned short alarmInCheckIntervals[MAX_ALARM_IN];
    FieldInfo fieldInfo;
} REMOTE_SETUP_EVENT_SYSTEM_ALARMIN_CHECK;

typedef struct {
    enum {
        INTERVAL_NEVER, INTERVAL_1M, INTERVAL_2M,   // 1M and 2M are only used on record check.(up to 7days)
        INTERVAL_1H, INTERVAL_2H, INTERVAL_3H, INTERVAL_4H, INTERVAL_5H,
        INTERVAL_6H, INTERVAL_7H, INTERVAL_8H, INTERVAL_9H, INTERVAL_10H,
        INTERVAL_11H, INTERVAL_12H, INTERVAL_18H, INTERVAL_1D, INTERVAL_7D,
        INTERVAL_15D, INTERVAL_30D,
        MAX_INTERVAL_TYPE,
    };
    enum {
        TEMPERATURE_CELCIUS,
        TEMPERATURE_FAHRENHEIT,
    };
    enum {
        FKEY_SYSCHECK_INTERVAL, FKEY_CHECK_REC_SETTING, FKEY_CHECK_ALARMIN_SETTING,
        FKEY_DISK_ALMOSTFULL_PERCENTAGE, FKEY_DISK_BAD_PERCENTAGE, FKEY_DISK_TEMPERATURE_TYPE, FKEY_DISK_TEMPERATURE,
        FKEY_SYS_CHECK_ACTION, FKEY_PANIC_REC_ACTION, FKEY_SYS_BOOTUP_ACTION, FKEY_SYS_RESTART_ACTION, FKEY_CHECK_REC_ACTION,
        FKEY_CHECK_ALARMIN_ACTION, FKEY_DISK_ALMOSTFULL_ACTION, FKEY_DISK_FULL_ACTION,
        FKEY_DISK_BAD_ACTION, FKEY_DISK_TEMPERATURE_ACTION, FKEY_DISK_SMART_ACTION, FKEY_DISK_CONF_CHANGE_ACTION, FKEY_DISK_INOUT_ACTION, FKEY_FAN_ERROR_ACTION, 
        FKEY_ESTATA_ISCSI_DISCONN_ACTION,
        FKEY_MAX,
    };

    unsigned short systemCheckInterval;
    REMOTESETUP_CONFIG_EVENT_SYSTEM_RECORDING_CHECK checkRecordingSetting;
    REMOTE_SETUP_EVENT_SYSTEM_ALARMIN_CHECK checkAlarmInSetting;
    unsigned char diskAlmostFullPercentage;
    unsigned char diskBadPercentage;
    unsigned char diskSmartTemperatureType;
    unsigned char diskSmartTemperature;

    REMOTESETUP_CONFIG_EVENT_ACTION systemCheckAction;
    REMOTESETUP_CONFIG_EVENT_ACTION panicRecordAction;
    REMOTESETUP_CONFIG_EVENT_ACTION sysBootUpAction;
    REMOTESETUP_CONFIG_EVENT_ACTION sysRestartAction;
    REMOTESETUP_CONFIG_EVENT_ACTION checkRecordingAction;
    REMOTESETUP_CONFIG_EVENT_ACTION checkAlarmInAction;
    REMOTESETUP_CONFIG_EVENT_ACTION diskAlmostFullAction;
    REMOTESETUP_CONFIG_EVENT_ACTION diskFullAction;
    REMOTESETUP_CONFIG_EVENT_ACTION diskBadAction;
    REMOTESETUP_CONFIG_EVENT_ACTION diskTemperatureAction;
    REMOTESETUP_CONFIG_EVENT_ACTION diskSMARTAction;
    REMOTESETUP_CONFIG_EVENT_ACTION diskConfigChangeAction;
    REMOTESETUP_CONFIG_EVENT_ACTION diskInOutAction;    // only for ip cameras
    REMOTESETUP_CONFIG_EVENT_ACTION fanErrorAction;
    REMOTESETUP_CONFIG_EVENT_ACTION eSataScsiDisconnectAction;
    FieldInfo fieldInfo;

} REMOTESETUP_CONFIG_EVENT_SYSTEM;

typedef struct {
    enum {
        FKEY_GENERAL_SCHEDULE, FKEY_ACTION = 0,
        FKEY_MAX,
    };
    
    REMOTESETUP_GENERAL_SCHEDULE_ITEM generalSchedule;
    REMOTESETUP_CONFIG_EVENT_ACTION notificationAction;
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_EVENT_NOTIFICATION_SCHEDULE_ITEM;

typedef struct {
    enum {
        FKEY_SCHEDULE_ITEMS = 0,
        FKEY_MAX,
    };
    enum {
        MAX_SCHEDULE_ITEM = 16,
    };

    REMOTESETUP_CONFIG_EVENT_NOTIFICATION_SCHEDULE_ITEM scheduleItems[MAX_SCHEDULE_ITEM];
    unsigned int itemCount;
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_EVENT_NOTIFICATION_SCHEDULE;

typedef struct {
    enum { // record resolution
        RESOLUTION_STANDARD = 0,
        RESOLUTION_HIGH,
        RESOLUTION_VERY_HIGH,
        MAX_RESOLUTION_COUNT,
    };
    enum {  // record quality
        QUALITY_LOW = 0,
        QUALITY_STANDARD,
        QUALITY_HIGH,
        QUALITY_VERY_HIGH,
        MAX_QUALITY_COUNT
    };
    enum {
        FKEY_RECYCLE, FKEY_EVENT_DWELL, FKEY_USE_DEINTERLACE, FKEY_AUTODELEATION_PERIOD,
        FKEY_TIMELAPSE_LIMIT, FKEY_RECORD_AUDIO, FKEY_PANIC_RECORD, FKEY_PANIC_RECORD_DURATION,
        FKEY_PANIC_RECORD_IPS, FKEY_PANIC_RECORD_QUALITY, FKEY_PANIC_RECORD_RESOLUTION,
        FKEY_MAX,
    };

    bool            recycle;
    unsigned short  eventDwellSec;      // up to 30 min.
    bool            useDeInterlace;
    unsigned short  autoDeletionPeriod; // 0~999 days
    unsigned short  timeLapseRecordLimit; // 0~99 days
    bool            recordAudio;

    bool            usePanicRecord;
    unsigned char   panicRecordDuration;    // in minutes. up to 1 hour.
    unsigned char   panicRecordIps;
    unsigned char   panicRecordQuality;
    unsigned char   panicRecordResolution;
    FieldInfo       fieldInfo;
} REMOTESETUP_CONFIG_RECORDING_GENERAL;

typedef struct {
    enum {
        MAX_RECORD_CHANNEL = 32,
    };
    enum {
        FKEY_GENERAL_SCHEDULE, FKEY_MODE, FKEY_CHANNELS,
        FKEY_TIMELAPSE_IPS, FKEY_TIMELAPSE_QUALITY, FKEY_TIMELAPSE_RESOLUTION,
        FKEY_EVENT_IPS, FKEY_EVENT_QUALITY, FKEY_EVENT_RESOLUTION,
        FKEY_MAX,
    };
    REMOTESETUP_GENERAL_SCHEDULE_ITEM generalSchedule;
    unsigned char mode;
    //unsigned int  channels;
    bool          channels[MAX_RECORD_CHANNEL];
    unsigned char timelapseIps;
    unsigned char timelapseQuality;
    unsigned char timelapseResolution;
    unsigned char eventIps;
    unsigned char eventQuality;
    unsigned char eventResolution;
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_RECORDING_SIMPLE_SCHEDULE_ITEM;

typedef struct {
    enum {
        FKEY_IPS, FKEY_QUALITY, FKEY_RESOLUTION, FKEY_DWELLTIME,
        FKEY_MAX,
    };

    unsigned char ips;
    unsigned char quality;
    unsigned char resolution;
    unsigned short dwellTime;
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_RECORDING_SETTING;

typedef struct {
    enum {
        // actual number of camera, and text-in count can be found by calling admin_getProductInfo function.
        MAX_SCHEDULE_ITEM = 32,
    };    
    enum {
        FKEY_TIMELAPSE_SCHEDULE, FKEY_ALARMIN_SCHEDULE, FKEY_MOTION_SCHEDULE,
        FKEY_VIDEOLOSS_SCHEDULE, FKEY_VIDEOBLIND_SCHEDULE, FKEY_TEXTIN_SCHEDULE,
        FKEY_MAX,
    };
    
    REMOTESETUP_GENERAL_SCHEDULE_ITEM generalSchedule;
    REMOTESETUP_CONFIG_RECORDING_SETTING timeLapseSchedule[MAX_SCHEDULE_ITEM];
    REMOTESETUP_CONFIG_RECORDING_SETTING alarmInSchedule[MAX_SCHEDULE_ITEM];
    REMOTESETUP_CONFIG_RECORDING_SETTING motionSchedule[MAX_SCHEDULE_ITEM];
    REMOTESETUP_CONFIG_RECORDING_SETTING videoLossSchedule[MAX_SCHEDULE_ITEM];
    REMOTESETUP_CONFIG_RECORDING_SETTING videoBlindSchedule[MAX_SCHEDULE_ITEM];
    REMOTESETUP_CONFIG_RECORDING_SETTING textInSchedule[MAX_SCHEDULE_ITEM];
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_RECORDING_SCHEDULE_ITEM;

typedef struct {
    enum {
        MAX_SCHEDULE = 20,
    };
    enum {
        FKEY_SCHEDULE_ON, FKEY_SCHEDULE_COUNT, FKEY_SIMPLE_SCHEDULE_COUNT,
        FKEY_SCHEDULES, FKEY_SIMPLE_SCHEDULE,
        FKEY_MAX,
    };

    bool scheduleOn;
    int scheduleCount;
    int simpleScheduleCount;
    REMOTESETUP_CONFIG_RECORDING_SCHEDULE_ITEM schedules[MAX_SCHEDULE];
    REMOTESETUP_CONFIG_RECORDING_SIMPLE_SCHEDULE_ITEM simpleSchedules[MAX_SCHEDULE];
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_RECORDING_SCHEDULE;

typedef struct {
    enum {
        FKEY_PRE_EVENT_USE, FKEY_PRE_EVENT_SCHEDULE_ITEM,
        FKEY_MAX,
    };

    bool use;
    REMOTESETUP_CONFIG_RECORDING_SETTING recSetting;
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_RECORDING_PREEVENT_ITEM;

typedef struct {
    enum {
        MAX_PREEVENT = 32,
    };
    enum {
        FKEY_PRE_EVENTS, FKEY_MAX,
    };
    
    REMOTESETUP_CONFIG_RECORDING_PREEVENT_ITEM preEvents[MAX_PREEVENT];
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_RECORDING_PREEVENT;

typedef struct {
    typedef struct {
         enum {
            PORT_NONE, PORT_RS232, PORT_RS232_1 = PORT_RS232, PORT_RS485,
            LAN1, LAN2, LAN3, LAN4, LAN5, LAN6, LAN7, LAN8,
            MAX_PORT,
         };
         enum {
             FKEY_PORT_TYPE, FKEY_BAUD_RATE, FKEY_DATA_BIT, FKEY_STOP_BIT, FKEY_PARITY, FKEY_TCP_PORT
         };

            unsigned char portType;
            unsigned char baudRate;
            unsigned char dataBit;
            unsigned char stopBit;
            unsigned char parity;
            unsigned short tcpPort;

            FieldInfo fieldInfo;

        } REMOTESETUP_CONFIG_GPS_PORT_DEVICE;

    enum {
         KPH = 0, MPH,
     };

    enum {
        FKEY_REMOTESETUP_CONFIG_GPS_PORT_DEVICE, FKEY_ENABLE_RECORDING, FKEY_USE_GPS_TIME_SYNC,
        FKEY_SPEED_UNIT, FKEY_CHECK_INTERVAL, FKEY_MAX,
    };
    REMOTESETUP_CONFIG_GPS_PORT_DEVICE portInfo;
    bool enableRecording;
    bool useGpsTimeSync;
    unsigned char speedUnit;
    unsigned int checkInterVal;
    FieldInfo fieldInfo;
} REMOTESETUP_CONFIG_NETWORK_GPS;
#endif // _REMOTE_SETUP_SDK_TYPES_H_
