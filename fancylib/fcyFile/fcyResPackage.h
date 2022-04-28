////////////////////////////////////////////////////////////////////////////////
/// @file  fcyResPackage.h
/// @brief fcy��Դ��
/// @note  ��ģ��Ŀǰ��֧����Դ���Ķ�ȡ
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../fcyRefObj.h"
#include "../fcyException.h"
#include "../fcyParser/fcyXml.h"
#include "../fcyIO/fcyDeflate.h"

#include <string>
#include <unordered_map>
#include <vector>

/// @addtogroup fancy���ļ�֧��
/// @brief �ṩ���ָ�ʽ�ļ��Ķ�д֧��
/// @{

class fcyResPackageDataNode;
class fcyResPackageFloderNode;

////////////////////////////////////////////////////////////////////////////////
/// @brief ��Դ���ڵ�
////////////////////////////////////////////////////////////////////////////////
class fcyResPackageNode
{
	friend class fcyResPackageFloderNode;
private:
	fcyResPackageFloderNode* m_pParent;  ///< @brief ���ڵ�
	std::wstring m_Name;                 ///< @brief �ļ���
protected:
	/// @brief     ������ȡ��Xml�����ж�ȡ��
	/// @param[in] pStream  ��
	/// @param[in] pXmlNode Xml�ڵ�
	virtual fResult Read(fcyStream* pStream, fcyXmlElement* pXmlNode)=0;
public: // �ӿ�ת��
	virtual fcyResPackageDataNode* ToDataNode()=0;    ///< @brief ת�����ݽڵ�
	virtual fcyResPackageFloderNode* ToFloderNode()=0;///< @brief ת���ļ��нڵ�
public:
	fcyResPackageFloderNode* GetParent();  ///< @brief ��ø��ڵ�
	fcStrW GetName();                      ///< @brief ���ؼ���
protected: // ���ƸĲ���
	fResult SetName(fcStrW Name);          ///< @brief ���ü���
protected:
	/// @brief     ���캯��
	/// @param[in] pParent ���ڵ�
	/// @param[in] Name    ����
	fcyResPackageNode(fcyResPackageFloderNode* pParent, const std::wstring& Name);
	virtual ~fcyResPackageNode();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief ��Դ�����ݽڵ�
////////////////////////////////////////////////////////////////////////////////
class fcyResPackageDataNode : 
	public fcyResPackageNode
{
	friend class fcyResPackageFloderNode;
private:
	fcyStream* m_pStream;       ///< @brief ����ԭʼ��

	// ����
	fuInt m_DataOffset;         ///< @brief �������������ƫ��
	fuInt m_DataRealSize;       ///< @brief ������ʵ��С
	fuInt m_DataCompressedSize; ///< @brief ����ѹ�����С
	fBool m_bDataCompressed;    ///< @brief �Ƿ�ѹ��

	// ��������
	std::wstring m_AdditionStr; ///< @brief ��������
public:
	fuInt GetDataOffset();           ///< @brief �����������������ƫ��
	fuInt GetDataRealSize();         ///< @brief ����������ʵ��С
	fuInt GetDataCompressedSize();   ///< @brief ��������ѹ�����С
	fBool IsDataCompressed();        ///< @brief ���������Ƿ�ѹ��

	/// @brief      ������
	/// @param[out] pOut ��ŵ�������ָ��
	/// @return     ���ز����Ƿ�ɹ�
	fResult DumpStream(fcyStream** pOut);

	fcStrW GetAdditonStr();          ///< @brief ���ض����ֶ�
	void SetAdditionStr(fcStrW Src); ///< @brief ���ö����ֶ�
protected:
	fResult Read(fcyStream* pStream, fcyXmlElement* pXmlNode);
public:
	fcyResPackageDataNode* ToDataNode();
	fcyResPackageFloderNode* ToFloderNode();
protected:
	/// @brief     ���캯��
	/// @param[in] pParent ���ڵ�
	/// @param[in] Name ����
	fcyResPackageDataNode(fcyResPackageFloderNode* pParent, const std::wstring& Name);
	~fcyResPackageDataNode();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief ��Դ���ļ��нڵ�
////////////////////////////////////////////////////////////////////////////////
class fcyResPackageFloderNode : public fcyResPackageNode
{
	friend class fcyResPackage;
private:
	std::vector<fcyResPackageNode*> m_NodeList; ///< @brief �ڵ��б�
public:
	fuInt GetNodeCount();                       ///< @brief ��ýڵ���Ŀ
	fcyResPackageNode* GetNode(fuInt Index);    ///< @brief ͨ��������ýڵ�
	fcyResPackageNode* GetNode(fcStrW Name);    ///< @brief ��ýڵ�
	fBool Contains(fcStrW Name);                ///< @brief �ڵ��Ƿ����
protected: // ���ƸĲ���
	fBool Append(fcyResPackageNode* pNode);     ///< @brief ׷�ӽڵ�
	fBool Remove(fcStrW Name);                  ///< @brief �Ƴ��ڵ�
	void Clear();                               ///< @brief ��ղ��ͷ��ڴ�
protected:
	fResult Read(fcyStream* pStream, fcyXmlElement* pXmlNode);
public:
	fcyResPackageDataNode* ToDataNode();
	fcyResPackageFloderNode* ToFloderNode();
protected:
	/// @brief     ���캯��
	/// @param[in] pParent ���ڵ�
	/// @param[in] Name    ����
	fcyResPackageFloderNode(fcyResPackageFloderNode* pParent, const std::wstring& Name);
	~fcyResPackageFloderNode();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief ��Դ���ļ�
////////////////////////////////////////////////////////////////////////////////
class fcyResPackage :
	public fcyRefObjImpl<fcyRefObj>
{
private:
	fcyResPackageFloderNode m_Root;  ///< @brief ���ڵ�

	// ����ͷ
	fuInt m_Flag;        ///< @brief �ļ���ʶ��
    fuInt m_Version;     ///< @brief �ļ��汾��
    fuInt m_IndexOffset; ///< @brief �ļ�������λ��
private:
	/// @brief     �����м����ļ�
	/// @param[in] ��
	/// @return    ���ز������
	fResult loadFromStream(fcyStream* pStream);
public:
	fcyResPackageFloderNode* GetRoot(); ///< @brief ��ø��ڵ�
public:
	/// @brief     ���캯��
	/// @param[in] pStream ��
	fcyResPackage(fcyStream* pStream);
protected:
	~fcyResPackage(void);
};
/// @}