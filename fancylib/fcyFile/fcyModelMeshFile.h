////////////////////////////////////////////////////////////////////////////////
/// @file  fcyModelMeshFile.h
/// @brief fcyģ������
/// @note  ֧����fancyģ�������ļ��Ķ�д
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../fcyIO/fcyStream.h"
#include "../fcyIO/fcyBinaryHelper.h"
#include "../fcyMisc/fcyStringHelper.h"

#include <vector>

#include "fcyModelVertexLabel.h"
#include "fcyModelIndexLabel.h"
#include "fcyModelMaterialLabel.h"
#include "fcyModelSubsetLabel.h"
#include "fcyModelBoundingBoxLabel.h"

/// @addtogroup fancy���ļ�֧��
/// @brief �ṩ���ָ�ʽ�ļ��Ķ�д֧��
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy����ģ���ļ�
////////////////////////////////////////////////////////////////////////////////
class fcyModelMeshFile
{
public:
	static const fuInt Version = 100;  ///< @brief �汾��1.00
protected:
	std::wstring m_Author;             ///< @brief ����
	std::wstring m_Description;        ///< @brief ģ������

	std::vector< fcyRefPointer<fcyModelLabel> > m_Labels;   ///< @brief ��ǩ������
public:
	/// @brief ��������
	fcStrW GetAuthor()const { return m_Author.c_str(); }
	/// @brief ��������
	fcStrW GetDescription()const { return m_Description.c_str(); }
	/// @brief ��������
	void SetAuthor(const std::wstring& Str) { m_Author = Str; }
	/// @brief ��������
	void SetDescription(const std::wstring& Str) { m_Description = Str; }
	
	/// @brief ���ر�ǩ�б�
	std::vector< fcyRefPointer<fcyModelLabel> >& GetLabelList() { return m_Labels; }
	
	/// @brief ���ص�һ����ǩ
	fcyRefPointer<fcyModelLabel> FindLabel(fuLong LabelName);

	/// @brief ��������
	void Load(fcyStream* pStream, fBool IgnoreUnsupportLabel = true);

	/// @brief ��������
	void Save(fcyStream* pStream);

	/// @brief ������fancy2Dģ��
	// void Export();
public:
	fcyModelMeshFile() {}
	/// @brief ǳ����
	fcyModelMeshFile(const fcyModelMeshFile& Right)
		: m_Author(Right.m_Author), m_Description(Right.m_Description),
		m_Labels(Right.m_Labels) {}
	~fcyModelMeshFile() {}
};

/// @}
