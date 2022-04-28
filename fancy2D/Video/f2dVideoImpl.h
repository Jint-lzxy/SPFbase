////////////////////////////////////////////////////////////////////////////////
/// @file  f2dVideoImpl.h
/// @brief fancy2DVideo�ӿ�ʵ��
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "f2dVideoStream.h"
#include "f2dVideoRenderer.h"

class f2dVideoSysImpl;

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D��Ƶ��������Ϣ
////////////////////////////////////////////////////////////////////////////////
struct f2dVideoFilterInfo
{
	HINSTANCE hDLLInstance; ///< @brief DLLʵ��
	GUID FilterGUID;        ///< @brief ������GUID
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D��Ƶ����ʵ��
////////////////////////////////////////////////////////////////////////////////
class f2dVideoImpl :
	public fcyRefObjImpl<f2dVideo>
{
private:
	// --- ��Ƶ������ ---
	f2dVideoStream* m_pStream;
	f2dVideoStreamReader* m_pReader;

	// --- DEBUG�� ---
	DWORD m_ObjectTableEntry;

	// --- DShow��� ---
	IGraphBuilder* m_pFilterGraph;  ///< @brief ������������
	IMediaControl* m_pMediaControl; ///< @brief ý�������
	IMediaEventEx* m_pMediaEvent;   ///< @brief ý���¼�
	IMediaSeeking* m_pMediaSeek;    ///< @brief ý��Ѱַ
	IVideoFrameStep* m_pVideoStep;  ///< @brief ��Ƶ������Ⱦ����
	IBasicAudio* m_pAudioControl;   ///< @brief ��������

	// --- ������� ---
	f2dVideoRenderer* m_pRenderer;
	f2dTexture2D* m_pTex;

	// --- ״̬ ---
	fBool m_bLoop;
private:
	void clearUp();
	void registerDebug();
	void unregisterDebug();
private:
	fBool addFilter(const f2dVideoFilterInfo& Filter);
	void clearUselessFilter();
public: // �ӿ�ʵ��
	f2dVideoRendererListener* GetRendererListener();
	void SetRendererListener(f2dVideoRendererListener* pListener);

	fResult Update();
	f2dTexture* GetVideoTex();

	fuInt GetVideoWidth();
	fuInt GetVideoHeight();
	fFloat GetVideoDataRate();
	fFloat GetVideoRenderFPS();
	fResult CopyDataToTexture(f2dTexture2D* pTex);

	fBool IsLoop();
	void SetLoop(fBool bLoop);
	F2DVIDEOSTATE GetState();
	fResult Play();
	fResult Pause();
	fResult Stop();

	fDouble GetTotalTime();
	fDouble GetCurTime();
	fResult SetCurTime(fDouble Time);
	fResult Seek(fuInt KeyFrame);
	fDouble GetRate();
	fResult SetRate(fDouble Rate);
	fFloat  GetVolume();
	fResult SetVolume(fFloat Volume);
	fFloat  GetPan();
	fResult SetPan(fFloat Pan);
public:
	f2dVideoImpl(f2dVideoSysImpl* pParent, f2dStream* pStream, fuInt Flag);
	~f2dVideoImpl(void);
};
