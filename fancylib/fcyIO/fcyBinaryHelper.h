////////////////////////////////////////////////////////////////////////////////
/// @file  fcyBinaryHelper.h
/// @brief fancy�����ƶ�д����
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "fcyStream.h"

/// @addtogroup fancy��IOģ��
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief fcy�����ƶ�ȡ����
////////////////////////////////////////////////////////////////////////////////
class fcyBinaryReader
{
private:
	fcyStream* m_pStream;         ///< @ԭʼ��
public:
	/// @brief   ���ػ�����
	/// @warning ��������������ԭʼ�������ü����������Ҫ�������ָ�����ֶ�����AddRef
	fcyStream* GetBaseStream();

	/// @brief ��ȡһ���ַ�
	fChar ReadChar();
	
	/// @brief      ��ȡ����ַ�
	/// @param[out] OutBuffer ���������
	/// @param[in]  Length    Ҫ��ȡ���ַ�����
	void ReadChars(fStr OutBuffer, fLen Length);
	
	/// @brief ��ȡһ�����ַ�
	fCharW ReadCharW();
	
	/// @brief      ��ȡ������ַ�
	/// @param[out] OutBuffer ���������
	/// @param[in]  Length    Ҫ��ȡ���ַ�����
	void ReadCharsW(fStrW OutBuffer, fLen Length);
	
	/// @brief ��ȡһ���ֽ�
	fByte ReadByte();

	/// @brief ��ȡ����ֽ�����
	/// @param[out] OutBuffer ���������
	/// @param[in]  Length    Ҫ��ȡ���ֽ���Ŀ
	void ReadBytes(fData OutBuffer, fLen Length);
	
	/// @brief ��ȡһ��������
	fShort ReadInt16();
	
	/// @brief ��ȡһ���޷��Ŷ�����
	fuShort ReadUInt16();

	/// @brief ��ȡһ������
	fInt ReadInt32();

	/// @brief ��ȡһ���޷�������
	fuInt ReadUInt32();

	/// @brief ��ȡһ��������
	fLong ReadInt64();

	/// @brief ��ȡһ���޷��ų�����
	fuLong ReadUInt64();

	/// @brief ��ȡһ��������
	fFloat ReadFloat();

	/// @brief ��ȡһ��˫���ȸ�����
	fDouble ReadDouble();
public:
	/// @brief     ���캯��
	/// @param[in] pStream ԭʼ��
	fcyBinaryReader(fcyStream* pStream);
	~fcyBinaryReader();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fcy������д�븨��
////////////////////////////////////////////////////////////////////////////////
class fcyBinaryWriter
{
private:
	fcyStream* m_pStream;         ///< @ԭʼ��
public:
	/// @brief   ���ػ�����
	/// @warning ��������������ԭʼ�������ü����������Ҫ�������ָ�����ֶ�����AddRef
	fcyStream* GetBaseStream();
	
	/// @brief д��һ���ַ�
	void Write(fChar Value);
	
	/// @brief д��һ���ַ���
	void Write(fcStr Buffer, fLen Length);
	
	/// @brief д��һ�����ַ�
	void Write(fCharW Value);
	
	/// @brief д��һ�����ַ���
	void Write(fcStrW Buffer, fLen Length);
	
	/// @brief д��һ���ֽ�
	void Write(fByte Value);
	
	/// @brief д��һ���ڴ滺��
	void Write(fcData Buffer, fLen Length);
	
	/// @brief д��һ��������
	void Write(fShort Value);
	
	/// @brief д��һ���޷��Ŷ�����
	void Write(fuShort Value);
	
	/// @brief д��һ������
	void Write(fInt Value);
	
	/// @brief д��һ���޷�������
	void Write(fuInt Value);
	
	/// @brief д��һ��������
	void Write(fLong Value);
	
	/// @brief д��һ���޷��ų�����
	void Write(fuLong Value);
	
	/// @brief д��һ��������
	void Write(fFloat Value);
	
	/// @brief д��һ��˫���ȸ�����
	void Write(fDouble Value);
public:
	/// @brief     ���캯��
	/// @param[in] pStream ԭʼ��
	fcyBinaryWriter(fcyStream* pStream);
	~fcyBinaryWriter();
};

/// @}