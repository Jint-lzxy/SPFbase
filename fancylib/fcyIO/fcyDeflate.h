////////////////////////////////////////////////////////////////////////////////
/// @file  fcyDeflate.h
/// @brief ��zlib���з�װ����ʵ�ֶ�����ѹ���ͽ�ѹ����
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "fcyStream.h"

/// @addtogroup fancy��IOģ��
/// @{

/// @brief Deflate�㷨֧��
namespace fcyDeflate
{
	/// @brief      ѹ����
	/// @param[in]  pIn   ����ѹ������
	/// @param[out] pOut  �����ѹ����
	/// @param[in]  Level ѹ���ȼ�(-1~9��-1��Ĭ�ϣ�0����ѹ����9�����ѹ���ȣ�
	/// @note       ���������ȡָ������лص�Begin��
	/// @return     ���ز����Ƿ�ɹ�
	fResult CompressStreamToMem(fcyStream* pIn, fcyStream** pOut, fInt Level=-1);
	
	/// @brief      ��ѹ��
	/// @param[in]  pIn  ������ѹ����
	/// @param[out] pOut �����ԭʼ������
	/// @note       ���������ȡָ������лص�Begin��
	/// @return     FCYERR_INVAILDDATA����Ч���ݣ�FCYERR_INTERNALERR��zlib�ڲ�����FCYERR_INVAILDPARAM����Ч����
	fResult DecompressStreamToMem(fcyStream* pIn, fcyStream** pOut);

	/// @brief      ��ѹ��
	/// @param[in]  pIn  ������ѹ����
	/// @param[in]  Flag ����
	/// @param[out] pOut �����ԭʼ������
	/// @note       ���������ȡָ������лص�Begin��
	/// @return     FCYERR_INVAILDDATA����Ч���ݣ�FCYERR_INTERNALERR��zlib�ڲ�����FCYERR_INVAILDPARAM����Ч����
	fResult DecompressStreamToMemEx(fcyStream* pIn, fInt Flag, fcyStream** pOut);
};
/// @}