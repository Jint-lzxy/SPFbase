////////////////////////////////////////////////////////////////////////////////
/// @file  fcyModelVertexLabel.h
/// @brief fcyģ�Ͷ������ݱ�ǩ����
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "fcyModelLabel.h"

/// @addtogroup fancy���ļ�֧��
/// @brief �ṩ���ָ�ʽ�ļ��Ķ�д֧��
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief fcyģ�Ͷ������ݱ�ǩ
////////////////////////////////////////////////////////////////////////////////
class fcyModelVertexLabel :
	public fcyModelLabel
{
public:
	/// @brief ��ǩ��
	static const fChar LABELNAME[8];

	/// @brief FMM����Ԫ������
	enum ELEMENTTYPE 
	{
		ELEMENTTYPE_FLOAT,   ///< @brief 4�ֽڸ���
		ELEMENTTYPE_FLOAT2,  ///< @brief 2*4�ֽڸ���
		ELEMENTTYPE_FLOAT3,  ///< @brief 3*4�ֽڸ���
		ELEMENTTYPE_FLOAT4,  ///< @brief 4*4�ֽڸ���
		ELEMENTTYPE_COLOR,   ///< @brief 4*1�ֽ�BGRA��ɫ����
		ELEMENTTYPE_UBYTE4,  ///< @brief 4*1�ֽ�
		ELEMENTTYPE_SHORT2,  ///< @brief 2*2�з��Ŷ�����
		ELEMENTTYPE_SHORT4   ///< @brief 4*2�з��Ŷ�����
	};

	/// @brief FMM����Ԫ��
	struct VertexElement
	{
		ELEMENTTYPE Type;  ///< @brief ����Ԫ�ص����ݸ�ʽ����������
		fuLong Usage;      ///< @brief ����Ԫ�ص���;
		fByte UsageIndex;  ///< @brief ����Ԫ�ص���;����
	};
protected:
	// ������������
	std::vector<VertexElement> m_VertElementList;
	
	// ��������
	std::vector<fByte> m_VertexData;
public:
	/// @brief     ���ݶ����������㶥���С
	fuInt CalcuVertexSize()const;

	/// @brief     ׷��һ������
	/// @param[in] pData      ��������
	/// @param[in] VertexSize �����С
	void PushVertex(void* pData, fuInt VertexSize);

	/// @brief     ׷��һ������(ģ��)
	template<typename T>
	void PushVertex(T* Vertex)
	{
		PushVertex(Vertex, sizeof(T));
	}

	/// @brief     ����Vertex����ָ��
	/// @warning   �����·����С��Ӧ�����»��ָ��
	void* GetVertexDataPointer() { return (m_VertexData.size() == 0) ? NULL : m_VertexData.data(); }

	/// @brief     ���ض��㻺���С
	fuInt GetVertexDataSize()const { return m_VertexData.size(); }

	/// @brief     ���·��䶥�����ݴ�С
	/// @note      ����ԭʼ����
	/// @param[in] NewSize �ֽڣ��µĶ��㻺���С
	void ResizeVertex(fuInt NewSize) { m_VertexData.resize(NewSize); }
	
	/// @brief     ׷��һ����������
	/// @param[in] Element ����Ԫ��
	void PushVertexElement(const VertexElement& Element) { m_VertElementList.push_back(Element); }

	/// @brief     ����Ԫ��
	/// @param[in] Index Ԫ������
	VertexElement& GetVertexElement(fuInt Index) { return m_VertElementList[Index]; }

	/// @brief     ���ض�������Ԫ������
	fuInt GetVertexElementSize()const { return m_VertElementList.size(); }

	/// @brief     ���·������ݴ�С
	/// @param[in] Ԫ������
	void ResizeElement(fuInt Count) { m_VertElementList.resize(Count); }
public: // �ӿ�ʵ��
	void ReadData(fcyStream* pStream);
	void WriteData(fcyStream* pStream);
public:
	fcyModelVertexLabel()
		: fcyModelLabel(FMM_MAKE_LABELNAME8(LABELNAME)) {}
protected:
	~fcyModelVertexLabel() {}
};
/// @}
