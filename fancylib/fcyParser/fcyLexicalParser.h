////////////////////////////////////////////////////////////////////////////////
/// @file  fcyLexicalParser.h
/// @brief fcy�ʷ�����������
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../fcyException.h"
#include "../fcyIO/fcyStream.h"

#include <string>

/// @addtogroup fancy���쳣
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief �ʷ������쳣
/// @note  ������fcyException�����������ʷ�����
////////////////////////////////////////////////////////////////////////////////
class fcyLexicalException :
	public fcyException
{
private:
	fuInt m_Line; ///< @brief �����쳣��������
	fuInt m_Row;  ///< @brief �����쳣��������
public:
	fuInt GetLine();  ///< @brief ����쳣��������
	fuInt GetRow();   ///< @brief ����쳣��������
public:
	/// @brief          ���캯��
	/// @note           ���캯�����Զ����кź��к���ӵ�Desc�ֶ�
	/// @param[in] Src  �쳣Դ
	/// @param[in] Desc �쳣����
	/// @param[in] Line �쳣�������к�
	/// @param[in] Row  �쳣�������к�
	fcyLexicalException(fcStr Src, fcStr Desc, fuInt Line, fuInt Row);
	~fcyLexicalException();
};
/// @}

/// @addtogroup fancy���������
/// @brief ʵ�ֶ�·����XML��JSON�ȸ�ʽ�Ľ���
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief ��������
////////////////////////////////////////////////////////////////////////////////
class fcyLexicalReader
{
private:
	std::wstring m_Str;  ///< @brief ����쳣��������
	fuInt m_Pos;         ///< @brief ����쳣��������
	fuInt m_Len;         ///< @brief ����쳣��������
private: // BOMͷ����
	fBool checkUTF8(fcyStream* pStream);
	fBool checkUTF16LE(fcyStream* pStream);
	std::wstring preprocess(fcyStream* pStream);
public:
	fuInt GetLine();     ///< @brief �����к�
	fuInt GetRow();      ///< @brief �����к�
	fBool IsEOF();       ///< @brief �Ƿ����

	fCharW ReadChar();   ///< @brief ��ȡһ���ַ�
	fCharW PeekChar();   ///< @brief Ԥ��ȡһ���ַ�

	void IgnoreSpace();  ///< @brief �����հ��ַ�

	/// @brief     ƥ��һ���ַ�
	/// @note      ƥ��һ���ַ���ʧ���׳��쳣
	/// @param[in] Char         Ҫƥ����ַ�
	/// @param[in] bIgnoreSpace ���Կո�
	void Match(fCharW Char, fBool bIgnoreSpace);

	/// @brief     ƥ��һ���ַ���
	/// @note      ƥ��һ���ַ�����ʧ���׳��쳣
	/// @param[in] Str          Ҫƥ����ַ���
	/// @param[in] bIgnoreSpace ���Կո�
	void Match(fcStrW Str, fBool bIgnoreSpace);
	
	/// @brief     ����ƥ��һ���ַ�
	/// @note      ����ƥ��һ���ַ���ʧ�ܷ���false
	/// @param[in] Char         Ҫƥ����ַ�
	/// @param[in] bIgnoreSpace ���Կո�
	/// @param[in] bMatch       �����ƥ��ɹ����Ƿ�ƥ������ַ�
	/// @return    true=����ƥ�䣬false=ƥ��ʧ��
	fBool TryMatch(fCharW Char, fBool bIgnoreSpace, fBool bMatch);

	/// @brief     ����ƥ��һ���ַ���
	/// @note      ����ƥ��һ���ַ�����ʧ�ܷ���false
	/// @param[in] Str          Ҫƥ����ַ���
	/// @param[in] bIgnoreSpace ���Կո�
	/// @param[in] bMatch       �����ƥ��ɹ����Ƿ�ƥ������ַ�
	/// @return    true=����ƥ�䣬false=ƥ��ʧ��
	fBool TryMatch(fcStrW Str, fBool bIgnoreSpace, fBool bMatch);
public:
	/// @brief     ���ı�����
	/// @param[in] SrcText Ҫ����ƥ���ԭʼ�ַ���
	fcyLexicalReader(const std::wstring& SrcText);
	/// @brief     ��������
	/// @param[in] SrcText Ҫ����ƥ���ԭʼ������
	fcyLexicalReader(fcyStream* pStream);
	~fcyLexicalReader(void);
};
/// @}