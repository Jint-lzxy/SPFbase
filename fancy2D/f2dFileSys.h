////////////////////////////////////////////////////////////////////////////////
/// @file  f2dFileSys.h
/// @brief fancy2D�ļ�ϵͳ�ӿڶ���
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "f2dInterface.h"

/// @addtogroup f2d�ļ�ϵͳ
/// @brief fancy2d�����е��ļ�ϵͳ
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D�����ļ�ϵͳ
////////////////////////////////////////////////////////////////////////////////
struct f2dFileFolderNode;
struct f2dFileStreamNode;

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D�ļ�ϵͳ�ڵ�
////////////////////////////////////////////////////////////////////////////////
struct f2dFileNode : public f2dInterface
{
	virtual f2dFileFolderNode* ToFolder()=0; ///< @brief ת�����ļ��нڵ㣨���������ü�����
	virtual f2dFileStreamNode* ToStream()=0; ///< @brief ת�������ڵ㣨���������ü�����

	virtual fcStrW GetName()=0;              ///< @brief ��ýڵ�����
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D�ļ��нڵ�
////////////////////////////////////////////////////////////////////////////////
struct f2dFileFolderNode : public f2dFileNode
{
	/// @brief ��������ӽڵ�
	/// @note  ��������ӽڵ㲢�������ü���
	virtual fResult Clear()=0;

	/// @brief     �����ӽڵ�
	/// @note      ��һ���ڵ����ӵ��ļ����У������������ü���
	/// @param[in] pNode    �ڵ�ָ��
	virtual fResult Add(f2dFileNode* pNode)=0;
	
	/// @brief     �Ƿ�����ӽڵ�
	/// @param[in] NodeName �ڵ�����
	/// @return    FCYERR_OBJEXSITED�������Ѵ��ڣ�FCYERR_OBJNOTEXSIT�����󲻴���
	virtual fResult Contain(fcStrW NodeName)=0;
	
	/// @brief     �Ƴ��ӽڵ�
	/// @note      ���ٽڵ�����ü���
	/// @param[in] NodeName �ڵ�����
	virtual fResult Remove(fcStrW NodeName)=0;
	
	/// @brief     ����ӽڵ�
	/// @note      ���ؽڵ�ָ�룬���������ü�����
	/// @param[in] NodeName �ڵ�����
	/// @return    ��������ڷ���NULL
	virtual f2dFileNode* GetSubNode(fcStrW NodeName)=0;
	
	/// @brief     ����ӽڵ�
	/// @note      ���ؽڵ�ָ�룬���������ü�����
	/// @param[in] Index �ڵ�����
	/// @return    ��������ڷ���NULL
	virtual f2dFileNode* GetSubNode(fuInt Index)=0;
	
	/// @brief ��ýڵ���
	virtual fuInt GetNodeCount()=0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D���ڵ�
////////////////////////////////////////////////////////////////////////////////
struct f2dFileStreamNode : public f2dFileNode
{
	/// @brief �������ӿ�
	/// @note  ���������ü���
	virtual f2dStream* GetStream()=0;
	
	/// @brief �ر���
	/// @note  ����ĳЩ�ڵ���Ч�����ڹرյ����ڵ���GetStreamʱӦ�ÿ��Ա����¼��ء�
	virtual fResult CloseStream()=0;
    
	/// @brief ���ض�������
	/// @note  �����ֶο��Ա�����������������
	virtual fcStrW GetAdditionData()=0;
	
	/// @brief ���ö�������
	virtual fResult SetAdditionData(fcStrW Str)=0;
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D�ļ�ϵͳ
////////////////////////////////////////////////////////////////////////////////
struct f2dFileSys
{
	// --- �ڵ���� ---
	/// @brief ��ø��ڵ�
	virtual f2dFileFolderNode* GetRootNode()=0;

	/// @brief     ��ýڵ�
	/// @param[in] Path �ڵ��·��
	virtual f2dFileNode* GetNode(fcStrW Path)=0;

	/// @brief     ɾ���ڵ�
	/// @param[in] Path �ڵ��·��
	virtual fResult RemoveNode(fcStrW Path)=0;

	/// @brief     �����ļ��нڵ�
	/// @param[in] Path �ڵ��·��
	virtual fResult AddFolderNode(fcStrW Path)=0;

	/// @brief     �����ڴ����ڵ�
	/// @param[in] Path      �ڵ��·��
	/// @param[in] Src       ����Դ����ΪNULL
	/// @param[in] Length    ��ʼ��С
	/// @param[in] Writable  ��д
	/// @param[in] Resizable �ɱ䳤
	virtual fResult AddMemStreamNode(fcStrW Path, fcData Src, fLen Length, fBool Writable, fBool Resizable)=0;
	
	/// @brief     ���ļ������ڴ����ڵ�
	/// @note      ���ļ����ص��ڴ沢�������ڵ�
	/// @param[in] Path      �ڵ��·��
	/// @param[in] FilePath  �ļ�·��
	/// @param[in] Writable  ��д
	/// @param[in] Resizable �ɱ䳤
	virtual fResult AddMemStreamNodeFromFile(fcStrW Path, fcStrW FilePath, fBool Writable, fBool Resizable)=0;

	/// @brief     �����ļ����ڵ�
	/// @note      �ҽ�һ������Ӳ���ϵ��ļ�
	/// @param[in] Path      �ڵ��·��
	/// @param[in] FilePath  �ļ�·��
	/// @param[in] Writable  ��д
	virtual fResult AddFileStreamNode(fcStrW Path, fcStrW FilePath, fBool Writable)=0;

	// --- �������� ---
	/// @brief  ͨ��·��ȡ����
	/// @note   �ò������������ü���
	/// @return �ɹ������������򷵻�NULL
	virtual f2dStream* GetStream(fcStrW Path)=0;

	// --- ������ ---
	/// @brief     ��һ����Դ�����ص��ڵ���
	/// @param[in] Path      ·��
	/// @param[in] PakStream ������
	virtual fResult LoadResPackage(fcStrW Path, f2dStream* PakStream)=0;

	/// @brief     ��һ����Դ�����ص��ڵ���
	/// @param[in] Path        ·��
	/// @param[in] PakFilePath �ļ�·��
	virtual fResult LoadResPackage(fcStrW Path, fcStrW PakFilePath)=0;

	// --- ��ʵĿ¼ӳ�� ---
	/// @brief     ӳ��һ����ʵ���ļ��е��ڵ���
	/// @note      ӳ��ʱ���¼�����ļ��У���Ŀ¼���κβ�����������ӳ���ӳ��
	/// @warning   ��ʵĿ¼�ڵ㲻���ִ�Сд
	/// @param[in] Path    ·��
	/// @param[in] DirPath �ļ���·��
	virtual fResult LoadRealPath(fcStrW Path, fcStrW DirPath)=0;
};
/// @}
