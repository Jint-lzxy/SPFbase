////////////////////////////////////////////////////////////////////////////////
/// @file  f2dSoundSysAPI.h
/// @brief fancy2D��Ƶϵͳ ��̬������
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "fcyRefObj.h"
#include "fcyIO\fcyStream.h"

#include "..\f2dSoundSys.h"

#include <dsound.h>

////////////////////////////////////////////////////////////////////////////////
/// @brief ��̬��������
////////////////////////////////////////////////////////////////////////////////
class f2dSoundBufferStatic :
	public fcyRefObjImpl<f2dSoundBuffer>
{
	friend class f2dSoundSysImpl;
protected:
	IDirectSoundBuffer* m_pBuffer; ///< @brief ��������
	
	fBool m_bLoop;      ///< @brief �Ƿ�ѭ��
	fuInt m_BufferSize; ///< @brief ��������С
	fuInt m_psSize;     ///< @brief һ������ռ�ֽ���
public: // �ӿ�ʵ��
	fBool IsDynamic();

	void Play();
	void Stop();
	void Pause();

	fBool IsLoop();
	void SetLoop(fBool bValue);
	fBool IsPlaying();
	fDouble GetTotalTime();
	fDouble GetTime();
	fResult SetTime(fDouble Time);
	fFloat GetVolume();
	fResult SetVolume(fFloat Value);
	fFloat GetPan();
	fResult SetPan(fFloat Value);
	fuInt GetFrequency();
	fResult SetFrequency(fuInt Value);
protected: // ��ֱֹ��new/delete
	f2dSoundBufferStatic(IDirectSound8* pSound, f2dSoundDecoder* pDecoder, fBool bGlobalFocus);
	f2dSoundBufferStatic(IDirectSoundBuffer* pBuffer);
	~f2dSoundBufferStatic();
};
