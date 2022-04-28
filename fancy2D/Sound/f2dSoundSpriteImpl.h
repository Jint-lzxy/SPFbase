////////////////////////////////////////////////////////////////////////////////
/// @file  f2dSoundSpriteImpl.h
/// @brief fancy2D��Ƶϵͳ ��Ч����
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "fcyRefObj.h"
#include "fcyIO\fcyStream.h"

#include "..\f2dSoundSys.h"

#include <dsound.h>

#include <deque>

////////////////////////////////////////////////////////////////////////////////
/// @brief ��Ч����
////////////////////////////////////////////////////////////////////////////////
class f2dSoundSpriteImpl : 
	public fcyRefObjImpl<f2dSoundSprite>
{
	friend class f2dSoundSysImpl;
private:
	IDirectSound8* m_pParent;
	IDirectSoundBuffer* m_pBuffer;                 ///< @brief ԭʼ����
	std::deque<IDirectSoundBuffer*> m_BufferList;  ///< @brief ʹ���л���
	fuInt m_BufferSize;
	fuInt m_psSize;

	fuInt m_MaxCount;
public: // �ӿ�ʵ��
	void Play();
	void Stop();
	void Pause();
	fDouble GetTotalTime();

	fResult PlayNewSound(fFloat Volume, fFloat Pan);
protected: // ��ֱֹ��new/delete
	f2dSoundSpriteImpl(IDirectSound8* pSound, f2dSoundDecoder* pDecoder, fBool bGlobalFocus, fuInt MaxCount = 10);
	~f2dSoundSpriteImpl();
};
