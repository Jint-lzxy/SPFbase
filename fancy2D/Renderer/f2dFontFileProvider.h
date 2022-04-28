////////////////////////////////////////////////////////////////////////////////
/// @file  f2dFontFileProvider.h
/// @brief fancy2D �����ṩ��
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <fcyRefObj.h>
#include <fcyIO/fcyStream.h>
#include "../f2dRenderer.h"

#include <unordered_map>

#include <ft2build.h> 
#include FT_FREETYPE_H

////////////////////////////////////////////////////////////////////////////////
/// @brief �����ṩ��ʵ��
////////////////////////////////////////////////////////////////////////////////
class f2dFontFileProvider :
	public fcyRefObjImpl<f2dFontProvider>,
	public f2dRenderDeviceEventListener
{
	friend class f2dRendererImpl;
protected:
	static const int s_Magin;    // ����

	// ���建������
	struct FontCacheInfo
	{
		// ԭʼ����
		fcyRect CacheSize;  // ����λ��

		// ��������
		fCharW Character;   // ��ǰ���ַ�
		fcyRect UV;         // �ַ�UV
		fcyVec2 GlyphSize;  // ���δ�С
		fcyVec2 BrushPos;   // �ʴ�λ��
		fcyVec2 Advance;    // ǰ����

		// ������
		FontCacheInfo* pPrev;
		FontCacheInfo* pNext;
	};
protected:
	f2dRenderDevice* m_pParent;

	// --- Freetype ---
	f2dStream* m_pStream;   // Font�ļ���
	FT_Open_Args m_Args;
	FT_StreamRec m_Stream;
	FT_Library m_FontLib;
	FT_Face m_Face;

	// --- ������������ ---
	fuInt m_TexSize;                // �����С 1024����2048 �������ø���ĳߴ��һЩ��
	fuInt m_CacheXCount;            // �����������
	fuInt m_CacheYCount;            // ������������
	fcyVec2 m_PerGlyphSize;         // �������δ�С
	FontCacheInfo* m_Cache;         // ������
	f2dTexture2D* m_CacheTex;       // ����������

	// --- ���ʹ�� ---
	FontCacheInfo* m_UsedNodeList;  // ʹ���нڵ㣬��֤Ϊѭ������
	FontCacheInfo* m_FreeNodeList;  // ���нڵ㣬��������
	std::wstring m_CharInUsing;     // ���ڻָ�����

	// �ַ���
	std::unordered_map<fCharW, FontCacheInfo*> m_Dict;
private: // freetype ����
	// ʵ��freetype��ȡ����
	static unsigned long streamRead(FT_Stream stream, unsigned long offset, unsigned char* buffer, unsigned long count)
	{
		f2dStream* pStream = (f2dStream*)stream->descriptor.pointer;

		pStream->Lock();

		fLen tRealReaded = 0;
		pStream->SetPosition(FCYSEEKORIGIN_BEG, offset);
		pStream->ReadBytes(buffer, count, &tRealReaded);

		pStream->Unlock();

		return (unsigned long)tRealReaded;
	}
	// ʵ��freetype�ر�������
	static void streamClose(FT_Stream stream)
	{
		// ������������������
	}
protected: // ���建�����
	// ��ȵ�λ������
	float widthSizeToPixel(int Size)
	{
		float tXScale = m_Face->size->metrics.x_scale / 65536.f;
		return (Size / 64.f) * tXScale;
	}
	// �߶ȵ�λ������
	float heightSizeToPixel(int Size)
	{
		float tYScale = m_Face->size->metrics.y_scale / 65536.f;
		return (Size / 64.f) * tYScale;
	}

	void addUsedNode(FontCacheInfo* p);      // �������ʹ�ýڵ�
	void removeFreeNode(FontCacheInfo* p);   // �Ƴ����нڵ�p������
	void removeUsedNode(FontCacheInfo* p);   // �Ƴ�ʹ���нڵ�p������
	f2dGlyphInfo getGlyphInfo(fCharW Char);  // �����������Ϣ��������UV���꣩
	FontCacheInfo* getChar(fCharW Char);     // �������
	bool makeCache(fuInt Size);                           // ���������������XCount * YCount������
	bool renderCache(FontCacheInfo* pCache, fCharW Char); // �ڻ�������pCacheλ�û�������Char
public: // �¼�����
	void OnRenderDeviceLost();
	void OnRenderDeviceReset();
public: // �ӿ�ʵ��
	fFloat GetLineHeight()
	{
		return heightSizeToPixel(m_Face->height);
	}
	fFloat GetAscender()
	{
		return heightSizeToPixel(m_Face->ascender);
	}
	fFloat GetDescender()
	{
		return heightSizeToPixel(m_Face->descender);
	}
	f2dTexture2D* GetCacheTexture()
	{
		return m_CacheTex;
	}
	fResult CacheString(fcStrW String);
	fResult QueryGlyph(f2dGraphics* pGraph, fCharW Character, f2dGlyphInfo* InfoOut);
	fInt GetCacheCount() { return m_CacheXCount * m_CacheYCount; }
	fInt GetCacheTexSize() { return m_TexSize; }
protected:
	f2dFontFileProvider(f2dRenderDevice* pParent, f2dStream* pStream, const fcyVec2& FontSize, const fcyVec2& BBoxSize, fuInt FaceIndex, F2DFONTFLAG Flag);
	~f2dFontFileProvider();
};
