////////////////////////////////////////////////////////////////////////////////
/// @file  f2dVideoStream.h
/// @brief fancy2D��Ƶ��
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "fcyRefObj.h"
#include "fcyIO/fcyStream.h"
#include "fcyOS/fcyMultiThread.h"
#include "fcyMisc/fcyStopWatch.h"

#include <dshow.h>

// DirectShow BaseClasses
#include <streams.h>

#include <asyncrdr.h>
#include <asyncio.h>

////////////////////////////////////////////////////////////////////////////////
/// @brief  fcyStream�ķ�װ
////////////////////////////////////////////////////////////////////////////////
class f2dVideoStream : 
	public CAsyncStream
{
private:
    CCritSec       m_csLock;      ///< @ brief ��
	fcyStream*     m_pStream;     ///< @ brief ������
	fLen           m_Pointer;     ///< @ brief ��ָ��
public:
	fcyStream* GetStream();
public:
    HRESULT SetPointer(LONGLONG llPos);
    HRESULT Read(PBYTE pbBuffer, DWORD dwBytesToRead, BOOL bAlign, LPDWORD pdwBytesRead);
	LONGLONG Size(LONGLONG *pSizeAvailable);
    DWORD Alignment();
    void Lock();
    void Unlock();
public:
    f2dVideoStream(fcyStream* pStream);
	~f2dVideoStream();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief  fcyStream������
////////////////////////////////////////////////////////////////////////////////
class f2dVideoStreamReader : 
	public CAsyncReader
{
private:
	fBool checkIsAVIFormat(fcyStream* pStream);
public:
    STDMETHODIMP Register();
    STDMETHODIMP Unregister();
    f2dVideoStreamReader(f2dVideoStream *pStream, HRESULT *phr);
};
