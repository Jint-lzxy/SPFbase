////////////////////////////////////////////////////////////////////////////////
/// @file  f2dVideoSys.h
/// @brief fancy2D��Ƶ����֧��
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "f2dInterface.h"

#include "f2dRenderer.h"

/// @addtogroup f2d��Ƶ֧��
/// @brief fancy2d��Ƶ����֧��
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D��Ƶ����״̬
////////////////////////////////////////////////////////////////////////////////
enum F2DVIDEOSTATE
{
	F2DVIDEOSTATE_STOPPED,  ///< @brief ֹͣ
	F2DVIDEOSTATE_PAUSED,   ///< @brief ��ͣ
	F2DVIDEOSTATE_PLAYING   ///< @brief ���ڲ���
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D��Ƶ�����ʼ����ʶ
/// @note  ����Ϊһ�±�ʶ���
////////////////////////////////////////////////////////////////////////////////
enum F2DVIDEOFLAG
{
	F2DVIDEOFLAG_DEBUG        = 1, ///< @brief �Ƿ�����ҽ�GraphEdit���е��ԣ�WinVista������Ҫע������DLL��
	F2DVIDEOFLAG_NOMANAGEDTEX = 2  ///< @brief �������ڲ�����
};

////////////////////////////////////////////////////////////////////////////////
/// @brief   fancy2D��Ƶ���ش��������
/// @note    �ýӿ�������CPU�϶���Ƶ���ؽ��д���
/// @warning �ýӿ������ڶ��߳���
////////////////////////////////////////////////////////////////////////////////
struct f2dVideoRendererListener
{
	/// @brief ��Ⱦһ֡
	virtual void OnVideoStartRender() {}
	/// @brief ����һ������
	virtual void OnVideoDrawPixel(fuInt X, fuInt Y, fcyColor* pColor) {}
	/// @brief ����һ֡��Ⱦ
	virtual void OnVideoEndRender() {}
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D��Ƶ����
////////////////////////////////////////////////////////////////////////////////
struct f2dVideo : public f2dInterface
{
	/// @brief �����Ƶ��Ⱦ��������
	virtual f2dVideoRendererListener* GetRendererListener()=0;

	/// @brief     ������Ƶ��Ⱦ��������
	/// @param[in] pListener ������
	virtual void SetRendererListener(f2dVideoRendererListener* pListener)=0;

	/// @brief ����
	/// @note  ���ú������������ڲ�״̬����Ⱦ����
	virtual fResult Update()=0;

	/// @brief ����ڲ��й�����
	/// @note  ���������ü���
	virtual f2dTexture* GetVideoTex()=0;

	/// @brief �����Ƶ���
	virtual fuInt GetVideoWidth()=0;
	
	/// @brief �����Ƶ�߶�
	virtual fuInt GetVideoHeight()=0;

	/// @brief �����Ƶ��Ⱦ������������
	/// @note  ���ֽ�Ϊ��λ
	virtual fFloat GetVideoDataRate()=0;

	/// @brief �����Ƶ��ȾFPS
	virtual fFloat GetVideoRenderFPS()=0;

	/// @brief     ������Ƶ���ݵ���̬����
	/// @param[in] pTex ��̬����ָ��
	virtual fResult CopyDataToTexture(f2dTexture2D* pTex)=0;

	/// @brief ���״̬
	virtual F2DVIDEOSTATE GetState()=0;

	/// @brief �Ƿ�ѭ��
	virtual fBool IsLoop()=0;

	/// @brief ����ѭ��
	virtual void SetLoop(fBool bLoop)=0;

	/// @brief ����
	virtual fResult Play()=0;

	/// @brief ��ͣ
	virtual fResult Pause()=0;

	/// @brief ֹͣ
	virtual fResult Stop()=0;

	/// @brief ��ò���ʱ��
	virtual fDouble GetTotalTime()=0;

	/// @brief ��õ�ǰʱ��
	virtual fDouble GetCurTime()=0;

	/// @brief ��õ�ǰʱ��
	virtual fResult SetCurTime(fDouble Time)=0;

	/// @breif ���չؼ�֡��Ѱʱ��
	virtual fResult Seek(fuInt KeyFrame)=0;

	/// @brief ��ò�������
	/// @note  1.0Ϊ�����ٶ�
	virtual fDouble GetRate()=0;

	/// @brief     ���ò�������
	/// @note      1.0Ϊ�����ٶ�
	/// @warning   �������еĽ�������֧�ָò���
	/// @param[in] Rate ��������
	virtual fResult SetRate(fDouble Rate)=0;

	/// @brief ��������
	virtual fFloat  GetVolume()=0;

	/// @brief     ��������
	/// @param[in] Volume ������С[0~1]
	virtual fResult SetVolume(fFloat Volume)=0;

	/// @brief ����ƽ��
	virtual fFloat GetPan()=0;

	/// @brief     ����ƽ��
	/// @param[in] Pan ƽ��ֵ[-1~1]
	virtual fResult SetPan(fFloat Pan)=0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D��Ƶϵͳ
////////////////////////////////////////////////////////////////////////////////
struct f2dVideoSys
{
	/// @brief      ���ع�������������
	/// @note       ����һ��DirectShow�Ĺ������������������Խ������߽�����Ƶ
	/// @param[in]  pGUIDStr ָ��DirectShow�����������GUID�ַ�������"1B544C20-FD0B-11CE-8C63-00AA0044B51E"
	virtual fResult LoadFilter(fcStrW pGUIDStr)=0;

	/// @brief      ��AX�ļ����ع�����
	/// @param[in]  AXFilePath ax�������ļ�·��
	/// @param[in]  pGUIDStr   ָ��DirectShow�����������GUID�ַ�������"1B544C20-FD0B-11CE-8C63-00AA0044B51E"
	virtual fResult LoadFilterFromAX(fcStrW AXFilePath, fcStrW pGUIDStr)=0;

	/// @brief      ������Ƶ����
	/// @param[in]  pStream ��Ƶ��
	/// @param[in]  Flag    F2DVIDEOFLAGö�ٵ�һ�����߶�����
	/// @param[out] pOut    �����������Ƶ����ָ��
	virtual fResult CreateVideo(f2dStream* pStream, fuInt Flag, f2dVideo** pOut)=0;
};

/// @}
