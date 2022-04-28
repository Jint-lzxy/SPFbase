////////////////////////////////////////////////////////////////////////////////
/// @file  fcyHash.h
/// @brief fancy��ϣ
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../fcyType.h"
#include <functional>

/// @addtogroup fancy����
/// @{

/// @brief fcyHash֧��
namespace fcyHash
{
	/// @brief     SuperFastHash�㷨
	/// @param[in] pData   ԭʼ����
	/// @param[in] DataLen ԭʼ���ݳ���
	fuInt SuperFastHash(fcData pData, fuInt DataLen);

	/// @brief SuperFastHash�㷨ģ��
	template<typename T>
	fuInt SuperFastHash(const T& Data)
	{
		return SuperFastHash((fcData)&Data, sizeof(T));
	}

	/// @brief HASHֵ���ģ��
	template <typename T>
	inline void HashCombine(fuInt& seed, const T & v)
	{
		std::hash<T> hasher;
		seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
};

/// @}
