////////////////////////////////////////////////////////////////////////////////
/// @file  f2dVideoRenderer.h
/// @brief fancy2D��Ƶ��Ⱦ������
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "f2dVideoStream.h"

#include "../f2dVideoSys.h"
#include "../f2dRenderer.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D��Ƶ��Ⱦ������
////////////////////////////////////////////////////////////////////////////////
class f2dVideoRenderer : 
	public CBaseVideoRenderer
{
private:
	// {598256BC-185B-4F8C-9881-DA12AB50CC74}
	static const GUID GUID_f2dVideoRenderer;
	enum SUPPORTMEDIATYPE
	{
		SUPPORTMEDIATYPE_RGB24,
		SUPPORTMEDIATYPE_RGB32,
		SUPPORTMEDIATYPE_ARGB32,
		SUPPORTMEDIATYPE_YUY2
	};
private:
	fInt m_TexWidth;                 // ������
	fInt m_TexHeight;                // ����߶�

	SUPPORTMEDIATYPE m_RawDataType;  // ԭʼ��ʽ
	fuInt m_lVideoWidth;             // ��Ƶ���
	fuInt m_lVideoHeight;            // ��Ƶ�߶�
	fuInt m_lVideoPitch;             // ��Ƶ���ݲ���ֵ

	CCritSec m_Lock;                 // ��

	// ������
	fInt m_BufferFlag;           // ��������ʶ���������ʹ�õĻ�����
	fcyColor* m_TexBuffer[2];    // ������������
	CCritSec m_BufferLock[2];    // ��������

	f2dVideoRendererListener* m_pListener; // ������

	// ����������
	fcyStopWatch m_Watch;
	fFloat m_TimeTotal;
	fLen m_DataTotal;
	fLen m_FPSTotal;
	fFloat m_DataPerSecond;
	fFloat m_FPS;
private:
	FCYINLINE fByte clip255(fInt value)
	{
		if(value < 0)
			return 0;
		else if(value > 255)
			return 255;
		return (fByte)value;
	}

	void renderRGBSample(fcData pVideo, fcyColor* pTex);
	void renderYUY2Sample(fcData pVideo, fcyColor* pTex);
public:
	f2dVideoRendererListener* GetRendererListener();
	void SetRendererListener(f2dVideoRendererListener* pListener);
	fcyColor* GetInternalPtr(fuInt Index);
	fuInt GetVideoWidth();
	fuInt GetVideoHeight();
	fResult CopyDataToTexture(f2dTexture2D* pTex);
	fFloat GetDataPerSecond();
	fFloat GetVideoRenderFPS();
public: // �ӿ�ʵ��
	HRESULT CheckMediaType(const CMediaType *pMediaType);
	HRESULT SetMediaType(const CMediaType *pMediaType);
	HRESULT DoRenderSample(IMediaSample *pMediaSample);
public:
	f2dVideoRenderer(HRESULT *phr = NULL);
	~f2dVideoRenderer();
};
