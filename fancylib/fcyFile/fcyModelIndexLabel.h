////////////////////////////////////////////////////////////////////////////////
/// @file  fcyModelIndexLabel.h
/// @brief fcyģ���������ݱ�ǩ����
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "fcyModelLabel.h"

/// @addtogroup fancy���ļ�֧��
/// @brief �ṩ���ָ�ʽ�ļ��Ķ�д֧��
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief fcyģ���������ݱ�ǩ
////////////////////////////////////////////////////////////////////////////////
class fcyModelIndexLabel :
	public fcyModelLabel
{
public:
	/// @brief ��ǩ��
	static const fChar LABELNAME[8];
protected:
	// ��������
	std::vector<fuInt> m_IndexData;
public:
	/// @brief ���������ʽ
	fBool IsIndex32();

	/// @brief     ׷��һ������
	/// @param[in] Index ����
	void Push(fuInt Index) { m_IndexData.push_back(Index); }

	/// @brief �����������
	fuInt* GetDataPointer() { return m_IndexData.data(); }

	/// @brief     ����Ԫ��
	/// @param[in] Index Ԫ������
	fuInt& GetElement(fuInt Index) { return m_IndexData[Index]; }

	/// @brief     ���ض�������Ԫ������
	fuInt GetSize()const { return m_IndexData.size(); }

	/// @brief     ���·������ݴ�С
	/// @param[in] Ԫ������
	void Resize(fuInt Count) { m_IndexData.resize(Count); }
public: // �ӿ�ʵ��
	void ReadData(fcyStream* pStream);
	void WriteData(fcyStream* pStream);
public:
	fcyModelIndexLabel()
		: fcyModelLabel(FMM_MAKE_LABELNAME8(LABELNAME)) {}
protected:
	~fcyModelIndexLabel() {}
};
/// @}
