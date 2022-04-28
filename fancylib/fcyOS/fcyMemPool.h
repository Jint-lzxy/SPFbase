////////////////////////////////////////////////////////////////////////////////
/// @file  fcyMemPool.h
/// @brief fancy�ڴ��
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../fcyType.h"

#ifdef _DEBUG
#include "fcyDebug.h"
#endif

#include <vector>

/// @addtogroup fancy��ײ�֧��
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief     �����ڴ��ʵ��
/// @param[in] BlockSize �ڴ���С
////////////////////////////////////////////////////////////////////////////////
template <fLen BlockSize>
class fcyMemPool
{
private:
	fLen m_PerPoolLen;                ///< @brief �´η���Ŀ�����
	fLen m_CurAlloctedSize;           ///< @brief ��ǰ����Ĵ�С
	std::vector<void*> m_AllocMemPtr; ///< @brief �ѷ����ڴ�ָ��
	std::vector<void*> m_FreeMemPool; ///< @brief �����ڴ�ָ��
private:
	/// @brief ׷�ӿ����ڴ�
	/// @param[in] BlockCount ������
	void appendMem(fuInt BlockCount)
	{
		// ������Ҫ����Ĵ�С
		fuLong tAllocSize = BlockCount * BlockSize;
		m_CurAlloctedSize += tAllocSize;
		// ���㵱ǰ�Ŀ���ָ���Ӧ���еĿռ�
		fuLong tPoolSize = m_FreeMemPool.size() + BlockCount;
		// �����������Ԥ��
		if(m_FreeMemPool.capacity() < tPoolSize)
			m_FreeMemPool.reserve( (size_t)tPoolSize );
		// ����ռ�
		fByte* tPtr = (fByte*)malloc( (size_t)tAllocSize );
		// ��¼����Ŀռ�
		m_AllocMemPtr.push_back(tPtr);
		// ��¼�����ڴ��
		for(fuInt i = 0; i<BlockCount; ++i)
		{
			m_FreeMemPool.push_back(tPtr);
			tPtr += BlockSize;
		}
	}

	/// @brief �����ڴ��
	void allocPool()
	{
		appendMem((fuInt)m_PerPoolLen);

		// �����´η���ֵ
		m_PerPoolLen = m_PerPoolLen * 2;
	}
public:
	/// @brief  �����ڴ�
	/// @return �ڴ��ָ��
	void* Alloc()
	{
		if(m_FreeMemPool.empty())
			allocPool();
		void* pRet = m_FreeMemPool.back();
		m_FreeMemPool.pop_back();
		return pRet;
	}

	/// @brief     �ͷ��ڴ�
	/// @param[in] Ptr �ڴ��ָ��
	void Free(void* Ptr)
	{
		m_FreeMemPool.push_back(Ptr);
	}

	/// @brief  ����ܷ����С
	/// @return �ܷ�����ڴ�
	fLen GetTotalSize()
	{
		return m_CurAlloctedSize;
	}

	/// @brief  ��ÿ����ڴ��ܴ�С
	/// @return �����ڴ���С
	fLen GetFreeSize()
	{
		return m_FreeMemPool.size() * BlockSize;
	}
public:
	/// @brief     ���캯��
	/// @param[in] InitMemSize ��ʼ�ڴ��С
	fcyMemPool(fuInt InitMemSize = 16)
	{
		m_CurAlloctedSize = 0;  // �ѷ����СΪ0
		m_PerPoolLen = 4;       // Ĭ���´�׷�ӿ�����Ϊ4

		m_AllocMemPtr.reserve(4);
		m_FreeMemPool.reserve(128);

		appendMem(InitMemSize / BlockSize);
	}

	~fcyMemPool()
	{
#ifdef _DEBUG
		if(GetTotalSize()!=GetFreeSize())
			fcyDebug::Trace(L"fcyMemPool(@ %x):: MemLeak!\n", (fuInt)this);
#endif
		for(std::vector<void*>::iterator i = m_AllocMemPtr.begin(); i != m_AllocMemPtr.end(); ++i)
		{
			free((*i));
		}
	}
};
/// @}