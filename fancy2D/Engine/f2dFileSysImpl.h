////////////////////////////////////////////////////////////////////////////////
/// @file  f2dFileSysImpl.h
/// @brief fancy2D�ļ�ϵͳ�ӿ�ʵ��
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "fcyRefObj.h"
#include "fcyIO\fcyStream.h"

#include "../f2dFileSys.h"

#include <fcyFile/fcyResPackage.h>

#include <string>
#include <vector>
#include <unordered_map>

////////////////////////////////////////////////////////////////////////////////
/// @brief ��ʵ�ļ��нڵ�
////////////////////////////////////////////////////////////////////////////////
class f2dFileFolderNodeForReal : 
	public fcyRefObjImpl<f2dFileFolderNode>
{
	friend class f2dFileSysImpl;
private:
	std::wstring m_Name;                                        ///< @brief �ڵ���
	std::wstring m_DirPath;                                     ///< @brief �ļ���·��
	std::vector<f2dFileNode*> m_SubNodes;                       ///< @brief ���������ӽڵ�
	std::unordered_map<std::wstring, f2dFileNode*> m_NodeList;  ///< @brief ���ٲ��ҹ���
public: // �ӿ�ʵ��
	f2dFileFolderNode* ToFolder();
	f2dFileStreamNode* ToStream();

	fcStrW GetName();
	
	fResult Clear();
	fResult Add(f2dFileNode* pNode);
	fResult Contain(fcStrW NodeName);
	fResult Remove(fcStrW NodeName);
	f2dFileNode* GetSubNode(fcStrW NodeName);
	f2dFileNode* GetSubNode(fuInt Index);
	fuInt GetNodeCount();
protected:
	f2dFileFolderNodeForReal(fcStrW NodeName, fcStrW DirPath);
	~f2dFileFolderNodeForReal();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief ��ʵ�ļ��ڵ�
////////////////////////////////////////////////////////////////////////////////
class f2dFileStreamNodeForReal :
	public fcyRefObjImpl<f2dFileStreamNode>
{
	friend class f2dFileFolderNodeForReal;
private:
	std::wstring m_Name;          ///< @brief �ڵ���
	std::wstring m_FileName;      ///< @brief �ļ���
	std::wstring m_AdditionData;  ///< @brief ��������
	fcyStream* m_pStream;         ///< @brief ������
public: // �ӿ�ʵ��
	f2dFileFolderNode* ToFolder();
	f2dFileStreamNode* ToStream();

	fcStrW GetName();

	f2dStream* GetStream();
	fResult CloseStream();
	fcStrW GetAdditionData();
	fResult SetAdditionData(fcStrW Str);
protected:
	f2dFileStreamNodeForReal(fcStrW NodeName, fcStrW FilePath);
	~f2dFileStreamNodeForReal();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy��Դ���ļ��нڵ�
////////////////////////////////////////////////////////////////////////////////
class f2dFileFolderNodeForPackage : 
	public fcyRefObjImpl<f2dFileFolderNode>
{
	friend class f2dFileSysImpl;
private:
	std::wstring m_FloderName;         ///< @brief �����ļ��нڵ�����

	fcyResPackage* m_pPackage;         ///< @brief ����Package
	fcyResPackageFloderNode* m_pNode;  ///< @brief ���ļ��еĽڵ�

	std::unordered_map<std::wstring, f2dFileNode*> m_NodesCache;  ///< @brief ����
public: // �ӿ�ʵ��
	f2dFileFolderNode* ToFolder();
	f2dFileStreamNode* ToStream();
	
	fcStrW GetName();

	fResult Clear();
	fResult Add(f2dFileNode* pNode);
	fResult Contain(fcStrW NodeName);
	fResult Remove(fcStrW NodeName);
	f2dFileNode* GetSubNode(fcStrW NodeName);
	f2dFileNode* GetSubNode(fuInt Index);
	fuInt GetNodeCount();
protected:
	f2dFileFolderNodeForPackage(fcyResPackage* pPackage, fcyResPackageFloderNode* pNode);
	f2dFileFolderNodeForPackage(fcyResPackage* pPackage, fcyResPackageFloderNode* pNode, const std::wstring& NameOverride);
	~f2dFileFolderNodeForPackage();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy��Դ���ļ��ڵ�
////////////////////////////////////////////////////////////////////////////////
class f2dFileStreamNodeForPackage :
	public fcyRefObjImpl<f2dFileStreamNode>
{
	friend class f2dFileFolderNodeForPackage;
private:
	fcyResPackage* m_pPackage;       ///< @brief ��Դ��ָ��
	fcyResPackageDataNode* m_pNode;  ///< @brief ���ڵ�ָ��

	fcyStream* m_pStream;            ///< @brief ������
public: // �ӿ�ʵ��
	f2dFileFolderNode* ToFolder();
	f2dFileStreamNode* ToStream();

	fcStrW GetName();

	f2dStream* GetStream();
	fResult CloseStream();
	fcStrW GetAdditionData();
	fResult SetAdditionData(fcStrW Str);
protected:
	f2dFileStreamNodeForPackage(fcyResPackage* pPackage, fcyResPackageDataNode* pNode);
	~f2dFileStreamNodeForPackage();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy�����ļ��нڵ�
////////////////////////////////////////////////////////////////////////////////
class f2dFileFolderNodeImpl : 
	public fcyRefObjImpl<f2dFileFolderNode>
{
	friend class f2dFileSysImpl;
private:
	std::wstring m_Name;                                       ///< @brief �ڵ���
	std::unordered_map<std::wstring, f2dFileNode*> m_NodeList; ///< @brief ������нڵ�
	std::vector<f2dFileNode*> m_pList;                         ///< @brief ��������
public: // �ӿ�ʵ��
	f2dFileFolderNode* ToFolder();
	f2dFileStreamNode* ToStream();
	
	fcStrW GetName();

	fResult Clear();
	fResult Add(f2dFileNode* pNode);
	fResult Contain(fcStrW NodeName);
	fResult Remove(fcStrW NodeName);
	f2dFileNode* GetSubNode(fcStrW NodeName);
	f2dFileNode* GetSubNode(fuInt Index);
	fuInt GetNodeCount();
protected:
	f2dFileFolderNodeImpl(fcStrW NodeName);
	~f2dFileFolderNodeImpl();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy�����ļ��ڵ�
////////////////////////////////////////////////////////////////////////////////
class f2dFileStreamNodeImpl :
	public fcyRefObjImpl<f2dFileStreamNode>
{
	friend class f2dFileSysImpl;
private:
	std::wstring m_Name;         ///< @brief �ڵ���
	fcyStream* m_pStream;        ///< @brief ��ָ��
	std::wstring m_AdditionStr;  ///< @brief ����������
public: // �ӿ�ʵ��
	f2dFileFolderNode* ToFolder();
	f2dFileStreamNode* ToStream();

	fcStrW GetName();

	f2dStream* GetStream();
	fResult CloseStream();
	fcStrW GetAdditionData();
	fResult SetAdditionData(fcStrW Str);
protected:
	f2dFileStreamNodeImpl(fcStrW NodeName, fcyStream* pStream);
	~f2dFileStreamNodeImpl();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D�ļ�ϵͳ
////////////////////////////////////////////////////////////////////////////////
class f2dFileSysImpl :
	public f2dFileSys
{
private:
	f2dFileFolderNode* m_pRootNode;
private:
	// ���������ظ��ڵ�
	f2dFileNode* traverseNode(fcStrW NodePath, f2dFileFolderNode** pParent);
	f2dFileNode* traverseNode(fcStrW NodePath, std::wstring& NodeName, f2dFileFolderNode** pParent);
	// �����������ڶ��㣬����;����Folder
	fResult makeNode(fcStrW NodePath, fBool MakeDir, std::wstring& NodeName, f2dFileFolderNode** pParent);
public: // �ӿ�ʵ��
	f2dFileFolderNode* GetRootNode();
	f2dFileNode* GetNode(fcStrW Path);
	fResult RemoveNode(fcStrW Path);
	fResult AddFolderNode(fcStrW Path);
	fResult AddMemStreamNode(fcStrW Path, fcData Src, fLen Length, fBool Writable, fBool Resizable);
	fResult AddMemStreamNodeFromFile(fcStrW Path, fcStrW FilePath, fBool Writable, fBool Resizable);
	fResult AddFileStreamNode(fcStrW Path, fcStrW FilePath, fBool Writable);

	f2dStream* GetStream(fcStrW Path);

	fResult LoadResPackage(fcStrW Path, fcyStream* PakStream);
	fResult LoadResPackage(fcStrW Path, fcStrW PakFilePath);

	fResult LoadRealPath(fcStrW Path, fcStrW DirPath);
public:
	f2dFileSysImpl();
	~f2dFileSysImpl();
};
