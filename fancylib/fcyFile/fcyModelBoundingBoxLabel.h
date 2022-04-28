////////////////////////////////////////////////////////////////////////////////
/// @file  fcyModelBoundingBoxLabel.h
/// @brief fcyģ�Ͱ�Χ�����ݱ�ǩ����
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "fcyModelLabel.h"

/// @addtogroup fancy���ļ�֧��
/// @brief �ṩ���ָ�ʽ�ļ��Ķ�д֧��
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief fcyģ�Ͱ�Χ�����ݱ�ǩ
////////////////////////////////////////////////////////////////////////////////
class fcyModelBoundingBoxLabel :
	public fcyModelLabel
{
public:
	/// @brief ��ǩ��
	static const fChar LABELNAME[8];
protected:
	// ��Χ����Ϣ
	fcyVec3 m_Min;   ///< @brief ��С����
	fcyVec3 m_Max;   ///< @brief �������
public:
	/// @brief ������С����
	const fcyVec3& GetMin()const { return m_Min; }
	/// @brief �����������
	const fcyVec3& GetMax()const { return m_Max; }
	/// @brief ������С����
	void SetMin(const fcyVec3& Value) { m_Min = Value; }
	/// @brief �����������
	void SetMax(const fcyVec3& Value) { m_Max = Value; }
public: // �ӿ�ʵ��
	void ReadData(fcyStream* pStream);
	void WriteData(fcyStream* pStream);
public:
	fcyModelBoundingBoxLabel()
		: fcyModelLabel(FMM_MAKE_LABELNAME8(LABELNAME)) {}
protected:
	~fcyModelBoundingBoxLabel() {}
};

/// @}
