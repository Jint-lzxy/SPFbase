////////////////////////////////////////////////////////////////////////////////
/// @file  f2dGraphics2DImpl.h
/// @brief fancy2D ��άͼԪ��Ⱦ��ʵ��
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "f2dRenderDeviceAPI.h"

#include "f2dGraphicsImpl.h"

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D ��ά��Ⱦ��ʵ��
////////////////////////////////////////////////////////////////////////////////
class f2dGraphics2DImpl :
	public f2dGraphicsImpl<f2dGraphics2D>,
	public f2dRenderDeviceEventListener
{
	friend class f2dRenderDeviceImpl;
protected:
	static const fuInt FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;  // �����ʶ
	struct RenderCommand
	{
		f2dTexture2D* pTex;  // ��Ⱦ�õ������ɿ�
		fuInt VertCount;     // ���ƺķѵĶ�����
		fuInt IndexCount;    // ���ƺķѵ�������
	};
protected:
	IDirect3DVertexBuffer9* m_pVB;
	IDirect3DIndexBuffer9* m_pIB;
	
	fuInt m_VBMaxCount;   // ���㻺���������
	fuInt m_IBMaxCount;   // ���������������
	fuInt m_VBUsedCount;  // ���㻺�������ÿռ�
	fuInt m_IBUsedCount;  // �������������ÿռ�
	fuInt m_VBAlloced;    // ��flush
	fuInt m_IBAlloced;    // ��flush

	f2dGraphics2DVertex* m_pVBData;
	fuShort* m_pIBData;

	// ָ���б�
	std::vector<RenderCommand> m_Commands;

	// ��ǰ���ģʽ
	F2DGRAPH2DBLENDTYPE m_ColorBlendType;
private:
	// ����С��ת����
	// �ѷ���
	static inline long ftol_ieee_M(float x) 
	{ 
		static const float magic_f = (3<<21);
		static const long magic_i = 0x4ac00000;
		float ftmp=x+magic_f;
		return  (*((long*)&ftmp)-magic_i) >> 1; 
	}
	// �����޸�
	void inline coordFix(float& x)
	{
		x = x - 0.5f;
	}
	// ִ�����л�ͼָ��
	void flush(bool Discard=false);
	// �����ڴ�
	bool alloc(fuInt VertCountToAlloc, fuInt IndexCountToAlloc, f2dGraphics2DVertex** pVertexOut, fuShort** pIndexOut);
	// ׷��������кϲ�
	void pushCommand(f2dTexture2D* pTex, fuInt VertCount, fuInt IndexCount);
	
	// ���벢���û��ģʽ
	fResult setColorBlendType(F2DGRAPH2DBLENDTYPE Type);
protected: // �豸��ʧ����
	void OnRenderDeviceLost();
	void OnRenderDeviceReset();
public: // �ӿ�ʵ��
	fBool IsGraphics3D() { return false; }

	fResult Begin();
	fResult Flush();
	fResult End();

	F2DGRAPH2DBLENDTYPE GetColorBlendType();
	fResult SetColorBlendType(F2DGRAPH2DBLENDTYPE Type);

	fResult DrawQuad(
		f2dTexture2D* pTex,
		const f2dGraphics2DVertex& v1, 
		const f2dGraphics2DVertex& v2, 
		const f2dGraphics2DVertex& v3, 
		const f2dGraphics2DVertex& v4,
		fBool bAutoFixCoord = true
		);
	fResult DrawQuad(f2dTexture2D* pTex, const f2dGraphics2DVertex* arr, fBool bAutoFixCoord = true);
	fResult DrawRaw(f2dTexture2D* pTex, fuInt VertCount, fuInt IndexCount, const f2dGraphics2DVertex* VertArr, const fuShort* IndexArr, fBool bAutoFixCoord = true);
public:
	f2dGraphics2DImpl(f2dRenderDeviceImpl* pParent, fuInt VertexBufferCount, fuInt IndexBufferCount);
	~f2dGraphics2DImpl();
};
