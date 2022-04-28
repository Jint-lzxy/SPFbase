////////////////////////////////////////////////////////////////////////////////
/// @file  f2dWaveDecoder.h
/// @brief fancy2D Wave������ʵ��
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "fcyRefObj.h"
#include "fcyIO\fcyBinaryHelper.h"

#include "../f2dSoundSys.h"

#include <string>
#include <vector>
#include <unordered_map>

////////////////////////////////////////////////////////////////////////////////
/// @brief Wave������
////////////////////////////////////////////////////////////////////////////////
class f2dWaveDecoder :
	public fcyRefObjImpl<f2dSoundDecoder>
{
private:
	static const char* tagRIFF;
	static const char* tagFMT;
	static const char* tagFACT;
	static const char* tagDATA;
private:
	class IChunk
	{
	public:
		char m_ID[5];
		fuInt m_Size;
	public:
		IChunk(fChar* ID, fuInt Size)
			: m_Size(Size)
		{
			memset(m_ID, 0, 5);
			memcpy(m_ID, ID, 4);
		}
		~IChunk() {}
	};
	class CWaveChunk :
		public IChunk
	{
	public:
		char m_Type[4];
	public:
		CWaveChunk(fChar* ID, fuInt Size, fcyBinaryReader* pReader);
		~CWaveChunk();
	};
	class CFormatChunk :
		public IChunk
	{
	public:
		fuShort m_FormatTag;     ///< @brief ���뷽ʽ��һ��Ϊ0x0001
        fuShort m_Channels;      ///< @brief ������Ŀ 1����������/2��˫������
		fuInt m_SamplesPerSec;   ///< @brief ����Ƶ��
		fuInt m_AvgBytesPerSec;  ///< @brief ÿ�������ֽ���
		fuShort m_BlockAlign;    ///< @brief ���ݿ���뵥λ��ÿ��������Ҫ���ֽ���)
		fuShort m_BitsPerSample; ///< @brief ÿ��������Ҫ��bit��
		fuShort m_Reserved;      ///< @brief ����
	public:
		CFormatChunk(fChar* ID, fuInt Size, fcyBinaryReader* pReader);
		~CFormatChunk();
	};
	class CFactChunk :
		public IChunk
	{
	public:
		fuInt m_Data;  // ����
	public:
		CFactChunk(fChar* ID, fuInt Size, fcyBinaryReader* pReader);
		~CFactChunk();
	};
	class CDataChunk :
		public IChunk
	{
	public:
		fLen m_BasePointer;
	public:
		CDataChunk(fChar* ID, fuInt Size, fcyBinaryReader* pReader);
		~CDataChunk();
	};
private:
	std::vector<IChunk*> m_ChunkList;
	std::unordered_map<std::string, IChunk*> m_Chunk;
	fuInt m_cPointer;
	f2dStream* m_pStream;
private:
	void clear();
public: // �ӿ�ʵ��
	fuInt GetBufferSize();
	fuInt GetAvgBytesPerSec();
	fuShort GetBlockAlign();
	fuShort GetChannelCount();
	fuInt GetSamplesPerSec();
	fuShort GetFormatTag();
	fuShort GetBitsPerSample();

	fLen GetPosition();
	fResult SetPosition(F2DSEEKORIGIN Origin, fInt Offset);
	fResult Read(fData pBuffer, fuInt SizeToRead, fuInt* pSizeRead);
public:
	f2dWaveDecoder(f2dStream* pStream);
	~f2dWaveDecoder();
};
