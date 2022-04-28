////////////////////////////////////////////////////////////////////////////////
/// @file  fcyModelMaterialLabel.h
/// @brief fcyģ�Ͳ������ݱ�ǩ����
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "fcyModelLabel.h"

/// @addtogroup fancy���ļ�֧��
/// @brief �ṩ���ָ�ʽ�ļ��Ķ�д֧��
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief fcyģ�Ͳ������ݱ�ǩ
////////////////////////////////////////////////////////////////////////////////
class fcyModelMaterialLabel :
	public fcyModelLabel
{
public:
	/// @brief ��ǩ��
	static const fChar LABELNAME[8];
protected:
	// ��������
	std::wstring m_MatName;    ///< @brief ��������
	std::wstring m_MatXMLData; ///< @brief ��������
public:
	/// @brief ���ز�������
	fcStrW GetMaterialName()const { return m_MatName.c_str(); }
	
	/// @brief ���ز���XML����
	fcStrW GetMaterialXMLData()const { return m_MatXMLData.c_str(); }

	/// @brief ���ò�������
	void SetMaterialName(const std::wstring& Name) { m_MatName = Name; }

	/// @brief ����XML����
	void SetMaterialXMLData(const std::wstring XMLData) { m_MatXMLData = XMLData; }
public: // �ӿ�ʵ��
	void ReadData(fcyStream* pStream);
	void WriteData(fcyStream* pStream);
public:
	fcyModelMaterialLabel()
		: fcyModelLabel(FMM_MAKE_LABELNAME8(LABELNAME)) {}
protected:
	~fcyModelMaterialLabel() {}
};

/// @}
