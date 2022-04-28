////////////////////////////////////////////////////////////////////////////////
/// @file  fcyModelSubsetLabel.h
/// @brief fcyģ���Ӽ����ݱ�ǩ����
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "fcyModelLabel.h"

/// @addtogroup fancy���ļ�֧��
/// @brief �ṩ���ָ�ʽ�ļ��Ķ�д֧��
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief fcyģ���Ӽ����ݱ�ǩ
////////////////////////////////////////////////////////////////////////////////
class fcyModelSubsetLabel :
	public fcyModelLabel
{
public:
	/// @brief ��ǩ��
	static const fChar LABELNAME[8];

	/// @brief ͼԪ����
	enum PRIMTYPE
	{
		PRIMTYPE_NULL          = 0,  ///< @brief ��Чֵ
		PRIMTYPE_POINTLIST     = 1,  ///< @brief �㼯
		PRIMTYPE_LINELIST      = 2,  ///< @brief �߼�
		PRIMTYPE_LINESTRIP     = 3,  ///< @brief �ߴ���
		PRIMTYPE_TRIANGLELIST  = 4,  ///< @brief �����μ�
		PRIMTYPE_TRIANGLESTRIP = 5,  ///< @brief �����δ�
		PRIMTYPE_TRIANGLEFAN   = 6   ///< @brief ��������
	};
protected:
	// �Ӽ�����
	std::wstring m_SubsetName;      ///< @brief �Ӽ����ƣ���ģ�������в����ظ�
	std::wstring m_MaterialName;    ///< @brief ��������
	PRIMTYPE m_PrimitiveType;       ///< @brief ͼԪ����
	fuInt m_StartIndex;             ///< @brief ������ʼ�±�
	fuInt m_PrimitiveCount;         ///< @brief ͼԪ����
public:
	fcStrW GetSubsetName()const { return m_SubsetName.c_str(); }
	fcStrW GetMaterialName()const { return m_MaterialName.c_str(); }
	PRIMTYPE GetPrimitiveType()const { return m_PrimitiveType; }
	fuInt GetStartIndex()const { return m_StartIndex; }
	fuInt GetPrimitiveCount()const { return m_PrimitiveCount; }

	void SetSubsetName(const std::wstring& Str) { m_SubsetName = Str; }
	void SetMaterialName(const std::wstring& Str) { m_MaterialName = Str; }
	void SetPrimitiveType(PRIMTYPE Type) { m_PrimitiveType = Type; }
	void SetStartIndex(fuInt Value) { m_StartIndex = Value; }
	void SetPrimitiveCount(fuInt Count) { m_PrimitiveCount = Count; }
public: // �ӿ�ʵ��
	void ReadData(fcyStream* pStream);
	void WriteData(fcyStream* pStream);
public:
	fcyModelSubsetLabel()
		: fcyModelLabel(FMM_MAKE_LABELNAME8(LABELNAME)) {}
protected:
	~fcyModelSubsetLabel() {}
};
/// @}
