////////////////////////////////////////////////////////////////////////////////
/// @file  fcyStringHelper.h
/// @brief fancy�ַ���������
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../fcyType.h"

#include <vector>
#include <string>

/// @addtogroup fancy����
/// @brief δ�������
/// @{

/// @brief fcy�ַ�������
namespace fcyStringHelper
{
	/// @brief      �ַ����ָ�
	/// @param[in]  Source   Դ�ַ���
	/// @param[in]  SplitStr ���ڷָ���ַ���
	/// @param[in]  AutoTrim �Զ��޳��հ׵ķָ���
	/// @param[out] Out      ������б�
	/// @return     ���ָ������
	fuInt StringSplit(const std::string& Source, const std::string& SplitStr, fBool AutoTrim, std::vector<std::string>& Out);
	
	/// @brief      �ַ����ָ���ַ��汾
	/// @param[in]  Source   Դ�ַ���
	/// @param[in]  SplitStr ���ڷָ���ַ���
	/// @param[in]  AutoTrim �Զ��޳��հ׵ķָ���
	/// @param[out] Out      ������б�
	/// @return     ���ָ������
	fuInt StringSplit(const std::wstring& Source, const std::wstring& SplitStr, fBool AutoTrim, std::vector<std::wstring>& Out);
	
	/// @brief     �ַ�����Сд
	/// @param[in] Source   Դ�ַ���
	/// @return    ��ת�����ַ���
	std::string ToLower(const std::string& Source);

	/// @brief     �ַ�����Сд�����ַ��汾
	/// @param[in] Source   Դ�ַ���
	/// @return    ��ת�����ַ���
	std::wstring ToLower(const std::wstring& Source);

	/// @brief     ���ֵ��ַ���
	/// @param[in] Number ����
	/// @param[in] Scale  ����
	/// @return    ������ַ���
	std::string ToStr(fInt Number, fInt Scale=10);

	/// @brief     ���ֵ��ַ���
	/// @param[in] Number ����
	/// @return    ������ַ���
	std::string ToStr(fDouble Number);

	/// @brief     ���ֵ��ַ��������ַ��汾
	/// @param[in] Number ����
	/// @param[in] Scale  ����
	/// @return    ������ַ���
	std::wstring ToWideStr(fInt Number, fInt Scale=10);
	
	/// @brief     ���ֵ��ַ��������ַ��汾
	/// @param[in] Number ����
	/// @return    ������ַ���
	std::wstring ToWideStr(fDouble Number);

	/// @brief     ʱ�䵽�ַ���
	/// @note      ��������ת����h:m:s.ms��ʽ
	/// @param[in] Seconds ������
	/// @return    ������ַ���
	std::string TimeToStr(fDouble Seconds);

	/// @brief     ʱ�䵽�ַ��������ַ��汾
	/// @note      ��������ת����h:m:s.ms��ʽ
	/// @param[in] Seconds ������
	/// @return    ������ַ���
	std::wstring TimeToWideStr(fDouble Seconds);

	/// @brief     �޳����հ��ַ�
	/// @param[in] Org ԭʼ�ַ���
	std::wstring TrimLeft(const std::wstring &Org);
	
	/// @brief     �޳��Ҳ�հ��ַ�
	/// @param[in] Org ԭʼ�ַ���
	std::wstring TrimRight(const std::wstring &Org);
	
	/// @brief     �޳��հ��ַ�
	/// @param[in] Org ԭʼ�ַ���
	std::wstring Trim(const std::wstring &Org);

	/// @brief     �޳����հ��ַ�
	/// @param[in] Org ԭʼ�ַ���
	std::string TrimLeft(const std::string &Org);
	
	/// @brief     �޳��Ҳ�հ��ַ�
	/// @param[in] Org ԭʼ�ַ���
	std::string TrimRight(const std::string &Org);
	
	/// @brief     �޳��հ��ַ�
	/// @param[in] Org ԭʼ�ַ���
	std::string Trim(const std::string &Org);

	/// @brief     string��wstring
	/// @param[in] Org ԭʼ�ַ���
	/// @param[in] CodePage ����ҳ���������MSDN
	/// @return    ���ر�ת�����ַ���
	std::wstring MultiByteToWideChar(const std::string& Org, fuInt CodePage=1);

	/// @brief     wstring��string
	/// @param[in] Org ԭʼ�ַ���
	/// @param[in] CodePage ����ҳ���������MSDN
	/// @return    ���ر�ת�����ַ���
	std::string WideCharToMultiByte(const std::wstring& Org, fuInt CodePage=1);
}
/// @}
