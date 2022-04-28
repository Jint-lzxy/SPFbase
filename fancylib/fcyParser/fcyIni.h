////////////////////////////////////////////////////////////////////////////////
/// @file  fcyIni.h
/// @brief fcyIni������
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "fcyLexicalParser.h"

#include <unordered_map>
#include <vector>

/// @addtogroup fancy���������
/// @{
////////////////////////////////////////////////////////////////////////////////
/// @brief Ini��
////////////////////////////////////////////////////////////////////////////////
class fcyIniSection
{
	friend class fcyIni;
private:
	std::wstring m_Name;
	std::unordered_map<std::wstring, std::wstring> m_Dict;
	std::vector<std::wstring> m_KeyList;
private:
	void writeToStr(std::wstring& Out);
public:
	/// @brief ��ý�����
	fcStrW GetName();
	
	/// @brief ���Key/Value����
	fuInt GetCount();

	/// @brief ͨ���±��ü���
	/// @note  �����ڣ�����NULL
	fcStrW GetKey(fuInt Index);

	/// @brief ͨ���±��ü�ֵ
	/// @note  �����ڣ�����NULL
	fcStrW GetValue(fuInt Index);
	
	/// @brief     ���ֵ
	/// @note      ͨ����������ֵ���������ڷ���Ĭ��ֵ
	/// @param[in] Key     ��
	/// @param[in] Default Ĭ��ֵ
	fcStrW GetValue(fcStrW Key, fcStrW Default);

	/// @brief     ����ֵ
	/// @note      ���������׷����ֵ
	/// @param[in] Key   ����
	/// @param[in] Value ֵ
	fBool SetValue(fcStrW Key, fcStrW Value);

	/// @brief     �Ƴ���
	/// @param[in] Key ����
	fBool Remove(fcStrW Key);
public:
	/// @brief ���캯��
	fcyIniSection(const std::wstring& Name);
	~fcyIniSection(void);
};

////////////////////////////////////////////////////////////////////////////////
/// @brief Ini�ļ�
////////////////////////////////////////////////////////////////////////////////
class fcyIni
{
private:
	std::unordered_map<std::wstring, fcyIniSection*> m_Dict;
	std::vector<std::wstring> m_SecList;
private:
	fBool ignoreComment(fcyLexicalReader& tReader);
	fcyIniSection* parseIniSection(fcyLexicalReader& tReader);
public:
	/// @brief     ׷��һ����
	/// @note      fcyIni���Ḻ��ɾ����
	/// @param[in] pSec ��
	fBool AppendSection(fcyIniSection* pSec);
	/// @brief     �Ƿ���ڽ�
	/// @param[in] SecName ������
	fBool IsContain(fcStrW SecName);
	/// @brief     �Ƴ���
	/// @param[in] SecName ������
	fBool Remove(fcStrW SecName);
	/// @brief     ��ý�
	/// @note      �����ڷ���NULL
	/// @param[in] SecName ������
	fcyIniSection* GetSection(fcStrW SecName);
	/// @brief     ���ֵ
	/// @param[in] Sec     ������
	/// @param[in] Key     ����
	/// @param[in] Default Ĭ��ֵ
	fcStrW GetValue(fcStrW Sec, fcStrW Key, fcStrW Default);
	/// @brief     ����ֵ
	/// @param[in] Sec     ������
	/// @param[in] Key     ����
	/// @param[in] Value   ��ֵ
	void SetValue(fcStrW Sec, fcStrW Key, fcStrW Value);
	/// @brief     д���ַ���
	/// @param[in] Out Ŀ���ַ���
	void WriteToStr(std::wstring& Out);
	/// @brief д����
	/// @param[in] pStream Ŀ����
	fBool WriteToStream(fcyStream* pStream);
public:
	/// @brief ����һ���µ�INI�ļ�
	fcyIni(void);
	/// @brief ���ı�����INI�ļ�
	fcyIni(const std::wstring& Src);
	/// @brief ��������INI�ļ�
	fcyIni(fcyStream* pStream);
	~fcyIni(void);
};

/// @}
