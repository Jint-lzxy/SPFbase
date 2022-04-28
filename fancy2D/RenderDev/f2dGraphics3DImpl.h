////////////////////////////////////////////////////////////////////////////////
/// @file  f2dGraphics3DImpl.h
/// @brief fancy2D ��άͼԪ��Ⱦ��ʵ��
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "f2dRenderDeviceAPI.h"

#include "f2dGraphicsImpl.h"

class f2dEffectImpl;

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D ��ά��Ⱦ��ʵ��
////////////////////////////////////////////////////////////////////////////////
class f2dGraphics3DImpl :
	public f2dGraphicsImpl<f2dGraphics3D>
{
	friend class f2dRenderDeviceImpl;
protected:
	fBool m_bEffectStateDirty;
	f2dEffectImpl* m_pCurEffect;

public: // �ӿ�ʵ��
	fBool IsGraphics3D() { return true; }
	fResult Begin();
	fResult End();
	fResult Flush() { return FCYERR_NOTSUPPORT; }
	void SetWorldTransform(const fcyMatrix4& Mat)
	{
		m_WorldMat = Mat;

		m_bEffectStateDirty = true;
	}
	void SetViewTransform(const fcyMatrix4& Mat)
	{
		m_LookatMat = Mat;

		m_bEffectStateDirty = true;
	}
	void SetProjTransform(const fcyMatrix4& Mat)
	{
		m_ProjMat = Mat;

		m_bEffectStateDirty = true;
	}

	f2dEffect* GetEffect();
	fResult SetEffect(f2dEffect* Effect);
	fResult BeginPass(fuInt PassIndex);
	fResult EndPass();
	fResult CommitState();
	fResult RenderPostEffect();
protected:
	f2dGraphics3DImpl(f2dRenderDeviceImpl* pParent, f2dEffectImpl* pEffect);
	~f2dGraphics3DImpl();
};
