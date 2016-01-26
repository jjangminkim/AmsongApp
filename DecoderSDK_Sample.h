// WatchSDK_Sample.h : header file
//

#ifndef _DECODERSDK_SAMPLE_SAMPLE_H_
#define _DECODERSDK_SAMPLE_SAMPLE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IDIS_DecoderSDK.h"

//////////////////////////////////////////////////////////////////////////

class DecoderSDK_Class
{
// Constructions
public:
	DecoderSDK_Class(void);
	~DecoderSDK_Class(void);

// Attributes
private:

// Operations
public:
	IDISHDECODER initialize(int max_camera);
	void finalize(IDISHDECODER hDecoder);

	bool doDecompress(IDISHDECODER hDecoder, LPBYTE lpDecParam, UINT decodeMode);
	void setDeInterlaceFilter(IDISHDECODER hDecoder, int typeofFrame);
};

//////////////////////////////////////////////////////////////////////////

#endif	// !_DECODERSDK_SAMPLE_SAMPLE_H_
