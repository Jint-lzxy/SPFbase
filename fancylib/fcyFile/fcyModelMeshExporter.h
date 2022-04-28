////////////////////////////////////////////////////////////////////////////////
/// @file  fcyModelMeshExporter.h
/// @brief fcyģ�����񵼳�
/// @note  ʵ�ִ�fmm������f2dģ������
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "fcyModelMeshFile.h"

/// @addtogroup fancy���ļ�֧��
/// @brief �ṩ���ָ�ʽ�ļ��Ķ�д֧��
/// @{

struct f2dRenderDevice;
struct f2dMeshData;

/// @brief ���񵼳�
namespace fcyModelMeshExporter
{
	////////////////////////////////////////////////////////////////////////////////
	/// @brief fancy���񵼳���Ϣ
	////////////////////////////////////////////////////////////////////////////////
	class ModelMeshInfo
	{
		friend ModelMeshInfo ExportMesh(fcyModelMeshFile& Mesh, f2dRenderDevice* pDev, f2dMeshData** pOut);
	private:
		std::unordered_map<std::wstring, fuInt> m_SubsetNameToId;
		std::unordered_map<fuInt, fuInt> m_IdToSubsetIndex;
		std::vector<fcyRefPointer<fcyModelSubsetLabel>> m_SubsetList;
		std::unordered_map<std::wstring, fcyRefPointer<fcyModelMaterialLabel>> m_MaterialList;
	public:
		/// @brief �����Ӽ�����
		fuInt GetSubsetCount()const { return m_SubsetList.size(); }

		/// @brief �����Ӽ�
		/// @note  ����������
		fcyModelSubsetLabel* GetSubset(fuInt Index) { return m_SubsetList[Index]; }
		
		/// @brief ���ٲ�ѯ����
		/// @note  ����������
		fcyModelMaterialLabel* GetMaterial(const std::wstring& Str) { return m_MaterialList[Str]; }

		/// @brief ��ѯ�Ӽ�ID
		fuInt GetSubsetID(const std::wstring& Str)const
		{
			std::unordered_map<std::wstring, fuInt>::const_iterator i = m_SubsetNameToId.find(Str);
			if(i == m_SubsetNameToId.end())
				throw fcyException("ModelMeshInfo::GetSubsetID", "Object not exist.");
			else
				return i->second;
		}

		/// @brief ID�����Ӽ�Index
		fuInt GetIndex(fuInt ID)const
		{
			std::unordered_map<fuInt, fuInt>::const_iterator i = m_IdToSubsetIndex.find(ID);
			if(i == m_IdToSubsetIndex.end())
				throw fcyException("ModelMeshInfo::GetSubsetID", "Object not exist.");
			else
				return i->second;
		}
	public:
		ModelMeshInfo() {}
		ModelMeshInfo(const ModelMeshInfo& Org)
			: m_SubsetNameToId(Org.m_SubsetNameToId), m_IdToSubsetIndex(Org.m_IdToSubsetIndex),
			m_SubsetList(Org.m_SubsetList), m_MaterialList(Org.m_MaterialList) {}
	};


	////////////////////////////////////////////////////////////////////////////////
	/// @brief ����ģ�͵�f2d
	////////////////////////////////////////////////////////////////////////////////
	ModelMeshInfo ExportMesh(fcyModelMeshFile& Mesh, f2dRenderDevice* pDev, f2dMeshData** pOut);
};

/// @}
