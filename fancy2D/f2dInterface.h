////////////////////////////////////////////////////////////////////////////////
/// @file  f2dInterface.h
/// @brief fancy2D�ӿڶ���
/// @note  ����������f2d�ӿڵĻ���
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <fcyType.h>
#include <fcyMath.h>

// --- f2dInterface �ȼ��� fcyRefObj ---
#ifdef FCYREFOBJ

typedef fcyRefObj f2dInterface;

#else

////////////////////////////////////////////////////////////////////////////////
/// @brief f2d���ü����ӿڶ���
////////////////////////////////////////////////////////////////////////////////
struct f2dInterface
{
	virtual void AddRef()=0;  ///< @brief ���ӽӿڵ����ü���
	virtual void Release()=0; ///< @brief ���ٽӿڵ����ü���
	                          ///< @note  ����������0ʱ���ٶ���
};

#endif

// --- ��f2d�ж����ӿ����¶��� ---
/// @cond NOFCYLIB

#ifdef FCYSTREAM

typedef FCYSEEKORIGIN F2DSEEKORIGIN;
typedef fcyStream f2dStream;

#else

enum F2DSEEKORIGIN
{
	F2DSEEKORIGIN_BEG = 0,  ///< @brief ��ͷ��ʼѰַ
	                        ///< @note  ָ��Ѱַλ�ÿ�ʼ��0��
	F2DSEEKORIGIN_CUR = 1,  ///< @brief �ӵ�ǰλ�ÿ�ʼѰַ
	F2DSEEKORIGIN_END = 2   ///< @brief �ӽ�β����ʼѰַ
	                        ///< @note  ָ��Ѱַλ�ÿ�ʼ��EOF��
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fcy���ӿ�
////////////////////////////////////////////////////////////////////////////////
struct f2dStream : f2dInterface
{
	/// @brief �������Ƿ��д
	virtual fBool CanWrite()=0;

	/// @brief �������Ƿ�ɱ䳤
	virtual fBool CanResize()=0;

	/// @brief ����������
	virtual fLen GetLength()=0;

	/// @brief     �����³���
	/// @param[in] Length �����³���
	virtual fResult SetLength(fLen Length)=0;
	
	/// @brief ��ö�дָ���λ��
	virtual fLen GetPosition()=0;

	/// @brief     ���ö�дλ��
	/// @param[in] Origin Ѱַ�ο�λ��
	/// @param[in] Offset λ��
	virtual fResult SetPosition(F2DSEEKORIGIN Origin, fLong Offset)=0;

	/// @brief      �����ж�ȡ�ֽ�����
	/// @param[in]  pData      Ŀ�Ļ�����
	/// @param[in]  Length     ���ݳ���
	/// @param[out] pBytesRead ��ʵ��д���ȣ�����ΪNULL
	virtual fResult ReadBytes(fData pData, fLen Length, fLen* pBytesRead=NULL)=0;

	/// @brief      ������д���ֽ�����
	/// @param[in]  pSrc        ԭʼ������
	/// @param[in]  Length      ���ݳ���
	/// @param[out] pBytesWrite ��ʵ��д���ȣ�����ΪNULL
	virtual fResult WriteBytes(fcData pSrc, fLen Length, fLen* pBytesWrite=NULL)=0;

	/// @brief   ������
	/// @note    �ú������ܻ��������
	/// @warning ���һ�����ڶ��̻߳����±�ʹ��ʱ�����ڶ�д�������ֶ�����
	virtual void Lock()=0;
	
	/// @brief   ��ͼ������
	/// @warning ���һ�����ڶ��̻߳����±�ʹ��ʱ�����ڶ�д�������ֶ�����
	/// @return  ʹ��FCYOK��FCYFAILED�ж��Ƿ�ɹ�����
	virtual fResult TryLock()=0;

	/// @brief   ������
	/// @note    �ú���������Lock��TryLock�ɹ��������½��е���
	/// @warning ���һ�����ڶ��̻߳����±�ʹ��ʱ�����ڶ�д�������ֶ�����
	virtual void Unlock()=0;
};

#endif

/// @endcond
