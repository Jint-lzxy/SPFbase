////////////////////////////////////////////////////////////////////////////////
/// @file  fcyDebug.h
/// @brief fancy���Ը�����
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../fcyType.h"

/// @addtogroup fancy��ײ�֧��
/// @{

/// @brief �������쳣
#ifdef _DEBUG
#define FCYDEBUGEXCPT(e)                                          \
{                                                                 \
	fcyDebug::Trace("[ TimeTick = %u ] fcyException @%s : %s\n",  \
		e.GetTime(), e.GetSrc(), e.GetDesc());                    \
}                                                                 
#else
#define FCYDEBUGEXCPT(e) { e; }
#endif

/// @brief fcy���Ը�����
namespace fcyDebug
{
    /// @brief     ��������ı�
	/// @note      ʹ�ø�ʽ����������������������ı�
	/// @param[in] Format ��ʽ���ı�
	/// @param[in] ...    ��������
	void Trace(fcStr Format, ...);

	/// @brief     ��������ı������ַ��汾
	/// @note      ʹ�ø�ʽ����������������������ı�
	/// @param[in] Format ��ʽ���ı�
	/// @param[in] ...    ��������
	void Trace(fcStrW Format, ...);
};

/// @}