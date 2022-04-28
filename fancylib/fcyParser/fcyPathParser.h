////////////////////////////////////////////////////////////////////////////////
/// @file  fcyPathParser.h
/// @brief fcy·��������
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../fcyType.h"

#include <string>

/// @addtogroup fancy���������
/// @{

/// @brief Fcy·����������
namespace fcyPathParser
{
	/// @brief     ��ú�׺
	/// @param[in] Path ·��
	/// @return    ���غ�׺
	std::string GetExtension(const std::string& Path);
	
	/// @brief     ���Сд��׺
	/// @param[in] Path ·��
	/// @return    ����Сд��׺
	std::string GetExtensionLower(const std::string& Path);

	/// @brief     ����ļ���
	/// @param[in] Path ·��
	/// @return    �����ļ���
	std::string GetFileName(const std::string& Path);

	/// @brief     ���ȥ��׺�ļ���
	/// @param[in] Path ·��
	/// @return    ����ȥ��׺�ļ���
	std::string GetFileNameWithoutExt(const std::string& Path);

	/// @brief     ���Ŀ¼
	/// @param[in] Path ·��
	/// @return    ����Ŀ¼
	std::string GetPath(const std::string& Path);

	/// @brief     ��ú�׺�����ַ���
	/// @param[in] Path ·��
	/// @return    ���غ�׺
	std::wstring GetExtension(const std::wstring& Path);
	
	/// @brief     ���Сд��׺�����ַ���
	/// @param[in] Path ·��
	/// @return    ����Сд��׺
	std::wstring GetExtensionLower(const std::wstring& Path);

	/// @brief     ����ļ��������ַ���
	/// @param[in] Path ·��
	/// @return    �����ļ���
	std::wstring GetFileName(const std::wstring& Path);

	/// @brief     ���ȥ��׺�ļ��������ַ���
	/// @param[in] Path ·��
	/// @return    ����ȥ��׺�ļ���
	std::wstring GetFileNameWithoutExt(const std::wstring& Path);

	/// @brief     ���Ŀ¼�����ַ���
	/// @param[in] Path ·��
	/// @return    ����Ŀ¼
	std::wstring GetPath(const std::wstring& Path);
};
/// @}