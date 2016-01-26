// DecoderSDK_Sample.cpp : implementation file
//

#include "StdAfx.h"
#include "DecoderSDK_Sample.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#ifdef _DEBUG
#pragma comment(lib, "./Bin/idisdecoder.lib")
#else
#pragma comment(lib, "./Bin/idisdecoder.lib")
#endif

/////////////////////////////////////////////////////////////////////////////

DecoderSDK_Class::DecoderSDK_Class(void)
{
}

DecoderSDK_Class::~DecoderSDK_Class(void)
{
}

/////////////////////////////////////////////////////////////////////////////

IDISHDECODER DecoderSDK_Class::initialize(int max_camera)
{
	return ::decoder_initialize(max_camera);
}

void DecoderSDK_Class::finalize(IDISHDECODER hDecoder)
{
	::decoder_finalize(hDecoder);
}

/////////////////////////////////////////////////////////////////////////////

bool DecoderSDK_Class::doDecompress(IDISHDECODER hDecoder, LPBYTE lpDecParam, UINT decodeMode)
{
	return ::decoder_doDecompress(hDecoder, lpDecParam, decodeMode);
}

void DecoderSDK_Class::setDeInterlaceFilter(IDISHDECODER hDecoder, int typeofFrame)
{
	return ::decoder_setdeinterlacefilter(hDecoder, typeofFrame);
}