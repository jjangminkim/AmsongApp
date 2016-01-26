// IDIS_Decoder.h : header file
//

#ifndef _IDIS_DECODER_INTERFACE_
#define _IDIS_DECODER_INTERFACE_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IDIS_Define.h"

#ifdef __cplusplus
extern "C" {
#endif

/////////////////////////////////////////////////////////////////////////////

IDIS_DLLFUNC IDISHDECODER IDISAPI decoder_initialize(int max_camera);
IDIS_DLLFUNC void IDISAPI decoder_finalize(IDISHDECODER hDecoder);
IDIS_DLLFUNC bool IDISAPI decoder_doDecompress(IDISHDECODER hDecoder, LPBYTE lpvdParam, UINT decodeMode);
IDIS_DLLFUNC bool IDISAPI decoder_doDecompressAudio(IDISHDECODER hDecoder, LPBYTE lpDecParam);
IDIS_DLLFUNC void IDISAPI decoder_setdeinterlacefilter(IDISHDECODER hDecoder, int typeofFilter);
// decoder_requestChangeDecodeMode should be called just before I-frame decoding.
//IDIS_DLLFUNC void IDISAPI decoder_requestChangeDecodeMode(IDISHDECODER hDecoder, int cameraId, BOOL playMode);

/////////////////////////////////////////////////////////////////////////////
#pragma pack(push, 1)

typedef struct {
	DWORD   _dwSize;				// this struct size
	LPBYTE  _lpCompData;			// compressed image data
	UINT32  _lpCompSize;			// compressed image buffer size(bytes)
	UINT16  _camId;					// camera unique index for decompress
	UINT16  _imgFormat;				// video_format(RGB, YUV)
	LPBYTE  _lpDecompData;			// image buffer for save decompressed data
	UINT16  _imgWidth;				// image width
	UINT16  _imgHeight;				// image height
	BYTE    _decoderType;
	BYTE	_byFrameType;
	BYTE    _byField;
	BYTE    _byVolHeader;
	BYTE	_reserved[4];
} PARAMD_DECODERS, *LPPARAMD_DECODERS;

typedef struct {
    DWORD  _dwSize;                 // this struct size
    LPBYTE _lpCompData;             // compressed audio data
    UINT32 _lpCompSize;             // compressed audio buffer size(bytes)
    LPBYTE _lpDecompData;           // audio buffer for save decompressed data
    UINT32 _lpDecompSize;           // decompressed size [out]
    BYTE   _decoderType;           // decoder
    BYTE   _byFrameType;           // frame type (must be IDIF_FRAMETYPE::AUDIO_FRAME)
    BYTE   _bitsPerSample;         // bits per sample [out]
    UINT16 _sampling;              // sample rate e.g. 16000hz
    BYTE   _bytePerSample;
} PARAMD_AUDIO_DECODERS, *LPPARAMD_AUDIO_DECODERS;

typedef struct {
	enum {
		IDIS_YUV420 = 0,
		IDIS_YUY2,
		IDIS_UYVY,
		IDIS_RGB32,
		IDIS_RGB24,
		IDIS_RGB565,
		IDIS_CLRFMT_MAX_DUMMY		// for sentinel
	};
} IDIS_COLORFORMAT;

typedef struct {
	enum {
		IDIS_DEINTERLACE_NONE = 0,
		IDIS_DEINTERLACE_SOFTEN,
		IDIS_DEINTERLACE_SHARPEN,
		IDIS_DEINTERLACE_EDGEDETECT,
		IDIS_DEINTERLACE_MAX_DUMMY	// for sentinel
	};
} IDIS_DEINTERLACE_FILTER;

#define DECODEMODE_SEARCH   0
#define DECODEMODE_WATCH    1

#pragma pack(pop)
/////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

/////////////////////////////////////////////////////////////////////////////

#endif	// !_IDIS_DECODER_INTERFACE_
