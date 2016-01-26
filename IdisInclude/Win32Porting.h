#if defined(__linux__)

#ifndef _WIN32_PORING_H
#define  _WIN32_PORING_H

#include <time.h>
#include <string.h>
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_PATH 256
#define _MAX_PATH 256
#define FALSE				0
#define TRUE				1
#if defined(_DEBUG)
	#define TRACE printf
#else
	#define TRACE(...)
#endif
#define USES_CONVERSION
#define VERIFY(f) ((void)(f))
#define ASSERT(a) assert(a)
#define _stat stat
#define __stdcall
#define _stdcall

#if defined(UNICODE)
	#if !defined(_TCHAR_DEFINED)
		typedef wchar_t TCHAR;
		typedef const wchar_t* LPCTSTR;
		typedef wchar_t* LPTSTR;
		inline wchar_t* _tcstok(wchar_t *src, const wchar_t *delim)
		{
			static wchar_t *state = NULL;
			return wcstok(src, delim, &state);
		}
		#define _TCHAR_DEFINED
	#endif
	#define _tcscpy  wcscpy
	#define _sntprintf swprintf
	#define _tstof not_supported
	#define __TEXT(quote) L##quote
	#define _T(quote) L##quote
	#define CW2A(quote) not_supported
	#define T2A(quote) not_supported
	#define A2T(quote) not_supported
#else
	#if !defined(_TCHAR_DEFINED)
		typedef char TCHAR;
		typedef const char* LPCTSTR;
		typedef char* LPTSTR;
		#define _TCHAR_DEFINED
	#endif
	#define _tcstok strtok
	#define _tcscpy  strcpy
	#define _sntprintf snprintf
	#define _tstof atof
	#define __TEXT(quote) quote
	#define _T(quote) quote
	#define CW2A(quote) quote
	#define T2A(quote) quote
	#define A2T(quote) quote
#endif
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned char       UINT8;
typedef unsigned short      WORD;
typedef unsigned short      UINT16;
typedef unsigned long 		ULONG;
typedef unsigned long 		UINT32;
typedef unsigned long 		ULONG_PTR;
typedef long 				LONG;
typedef long 				LONG_PTR;
typedef unsigned int      	UINT;
typedef unsigned int      	UINT_PTR;
typedef unsigned long long  ULONGLONG;
typedef unsigned char*		LPBYTE;
typedef const char*         LPCSTR;

#define MAKEWORD(a, b)      ((WORD)(((BYTE)(((DWORD)(a)) & 0xff)) | ((WORD)((BYTE)(((DWORD)(b)) & 0xff))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)(((DWORD)(a)) & 0xffff)) | ((DWORD)((WORD)(((DWORD)(b)) & 0xffff))) << 16))
#define LOWORD(l)           ((WORD)(((DWORD)(l)) & 0xffff))
#define HIWORD(l)           ((WORD)((((DWORD)(l)) >> 16) & 0xffff))
#define LOBYTE(w)           ((BYTE)(((DWORD)(w)) & 0xff))
#define HIBYTE(w)           ((BYTE)((((DWORD)(w)) >> 8) & 0xff))


inline int DecodeBase64Char(unsigned int ch) throw()
{
	// returns -1 if the character is invalid
	// or should be skipped
	// otherwise, returns the 6-bit code for the character
	// from the encoding table
	if (ch >= 'A' && ch <= 'Z')
		return ch - 'A' + 0;	// 0 range starts at 'A'
	if (ch >= 'a' && ch <= 'z')
		return ch - 'a' + 26;	// 26 range starts at 'a'
	if (ch >= '0' && ch <= '9')
		return ch - '0' + 52;	// 52 range starts at '0'
	if (ch == '+')
		return 62;
	if (ch == '/')
		return 63;
	return -1;
}

inline BOOL Base64Decode(LPCSTR szSrc, int nSrcLen, BYTE *pbDest, int *pnDestLen) throw()
{
	// walk the source buffer
	// each four character sequence is converted to 3 bytes
	// CRLFs and =, and any characters not in the encoding table
	// are skiped

	if (szSrc == NULL || pnDestLen == NULL)
	{
		//ATLASSERT(FALSE);
		return FALSE;
	}
	
	LPCSTR szSrcEnd = szSrc + nSrcLen;
	int nWritten = 0;
	
	BOOL bOverflow = (pbDest == NULL) ? TRUE : FALSE;
	
	while (szSrc < szSrcEnd &&(*szSrc) != 0)
	{
		DWORD dwCurr = 0;
		int i;
		int nBits = 0;
		for (i=0; i<4; i++)
		{
			if (szSrc >= szSrcEnd)
				break;
			int nCh = DecodeBase64Char(*szSrc);
			szSrc++;
			if (nCh == -1)
			{
				// skip this char
				i--;
				continue;
			}
			dwCurr <<= 6;
			dwCurr |= nCh;
			nBits += 6;
		}

		if(!bOverflow && nWritten + (nBits/8) > (*pnDestLen))
			bOverflow = TRUE;

		// dwCurr has the 3 bytes to write to the output buffer
		// left to right
		dwCurr <<= 24-nBits;
		for (i=0; i<nBits/8; i++)
		{
			if(!bOverflow)
			{
				*pbDest = (BYTE) ((dwCurr & 0x00ff0000) >> 16);
				pbDest++;
			}
			dwCurr <<= 8;
			nWritten++;
		}

	}
	
	*pnDestLen = nWritten;
	
	if(bOverflow)
	{
		if(pbDest != NULL)
		{
			//ATLASSERT(FALSE);
		}
	
		return FALSE;
	}
	
	return TRUE;
}


#endif // _WIN32_PORTING_H

#endif // __linux__

