////////////////////////////////////////////////////////////////////////////////
/// @file  fcyRandom.h
/// @brief fancy�����
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../fcyType.h"

/// @addtogroup fancy����
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief WELL512������㷨
/// @note  ժ�ԡ���Ϸ��̾��� 7��
////////////////////////////////////////////////////////////////////////////////
class fcyRandomWELL512
{
private:
	fuInt m_State[16];   ///< @brief �ڲ�״̬��
	fuInt m_Index;       ///< @brief �±�
	fuInt m_RSeed;       ///< @brief ���������
public:
	/// @brief ������������
	fuInt GetRandSeed();
	/// @brief     �������������
	/// @param[in] Seed ���������
	void SetSeed(fuInt Seed);
	/// @brief �����޷�������
	fuInt GetRandUInt();
	/// @brief     ����[0, Max]֮����޷�������
	/// @param[in] Max �����
	fuInt GetRandUInt(fuInt Max);
	/// @brief ����[0, 1]֮������С��
	fFloat GetRandFloat();
	/// @brief ����[MinBound, MaxBound]֮������С��
	/// @param[in] MinBound �½�
	/// @param[in] MaxBound �Ͻ�
	fFloat GetRandFloat(fFloat MinBound, fFloat MaxBound);
public:
	/// @brief Ĭ�Ϲ��캯��
	/// @note  ����GetTickCount()���г�ʼ��
	fcyRandomWELL512();
	/// @brief ָ�����ӳ�ʼ�������������
	fcyRandomWELL512(fuInt Seed);
	~fcyRandomWELL512();
};
/// @}
