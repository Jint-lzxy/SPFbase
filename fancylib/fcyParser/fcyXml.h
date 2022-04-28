//////////////////////////////////////////////////////////////////////////
/// @file  fcyXml.h
/// @brief fcyXml������
/// @note  ����֧��һ���ʽ��Xml
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "fcyLexicalParser.h"
#include "../fcyOS/fcyMemPool.h"

#include <map>
#include <string>
#include <vector>

/// @addtogroup fancy���������
/// @{

class fcyXmlDocument;
class fcyXmlElement;

/// @brief XML�쳣
class fcyXmlException :
	public fcyException
{
protected:
	fcyXmlDocument* m_pOwner;
public:
	fcyXmlDocument* GetOwner() { return m_pOwner; }
public:
	fcyXmlException(fcStr Src, fcyXmlDocument* pOwner, fcStr Desc, ...);
	fcyXmlException(const fcyXmlException& e)
		: fcyException(e), m_pOwner(e.m_pOwner) {}
};

/// @brief XML�쳣 - ����δ�ҵ�
class fcyXmlAttributeNotFount :
	public fcyXmlException
{
public:
	fcyXmlAttributeNotFount(fcStr Src, fcyXmlDocument* pOwner, fcStrW Name);
};

/// @brief XML�쳣 - �ڵ�δ�ҵ�
class fcyXmlNodeNotFount :
	public fcyXmlException
{
public:
	fcyXmlNodeNotFount(fcStr Src, fcyXmlDocument* pOwner, fcStrW Name);
};

/// @brief XML�쳣 - ����������Χ
class fcyXmlIndexOutOfRange :
	public fcyXmlException
{
public:
	fcyXmlIndexOutOfRange(fcStr Src, fcyXmlDocument* pOwner, fuInt Index);
};

/// @brief XML�쳣 - �ڵ�֮���в�ͬ�������ĵ�
class fcyXmlNodeHasDifferentOwner :
	public fcyXmlException
{
public:
	fcyXmlNodeHasDifferentOwner(fcStr Src, fcyXmlDocument* pOwner, fcStrW NodeA, fcStrW NodeB);
};

/// @brief XML�쳣 - �ڵ����и��ڵ�
class fcyXmlNodeHasParent :
	public fcyXmlException
{
public:
	fcyXmlNodeHasParent(fcStr Src, fcyXmlDocument* pOwner, fcStrW Name);
};

/// @brief XML�쳣 - �ڵ�����ʹ��
class fcyXmlNodeIsInUse :
	public fcyXmlException
{
public:
	fcyXmlNodeIsInUse(fcStr Src, fcyXmlDocument* pOwner, fcStrW Name);
};

// ���Ե�����
class fcyXmlAttributeIterator
{
	friend class fcyXmlElement;
	friend class fcyXmlAttributeConstIterator;
private:
	std::map<std::wstring, std::wstring>::iterator i;
public:
	fcyXmlAttributeIterator& operator=(const fcyXmlAttributeIterator& Right) { i = Right.i; return *this; }
	fBool operator==(const fcyXmlAttributeIterator& Right)const { return (i == Right.i); }
	fBool operator!=(const fcyXmlAttributeIterator& Right)const { return (i != Right.i); }
	fcyXmlAttributeIterator& operator--() { --i; return *this; }
	fcyXmlAttributeIterator& operator++() { ++i; return *this; }
	const std::wstring& operator*()const { return i->second; }
	std::wstring& operator*() { return i->second; }
public:
	const std::wstring& GetName()const { return i->first; }
	const std::wstring& GetContent()const { return i->second; }
	void SetContent(const std::wstring& Content) { i->second = Content; }
protected:
	fcyXmlAttributeIterator(const std::map<std::wstring, std::wstring>::iterator& _i)
		: i(_i) {}
public:
	fcyXmlAttributeIterator() {}
	fcyXmlAttributeIterator(const fcyXmlAttributeIterator& Org)
		: i(Org.i) {}
};

// ֻ�����Ե�����
class fcyXmlAttributeConstIterator
{
	friend class fcyXmlElement;
private:
	std::map<std::wstring, std::wstring>::const_iterator i;
public:
	fcyXmlAttributeConstIterator& operator=(const fcyXmlAttributeConstIterator& Right) { i = Right.i; }
	fBool operator==(const fcyXmlAttributeConstIterator& Right)const { return (i == Right.i); }
	fBool operator!=(const fcyXmlAttributeConstIterator& Right)const { return (i != Right.i); }
	fcyXmlAttributeConstIterator& operator--() { --i; return *this; }
	fcyXmlAttributeConstIterator& operator++() { ++i; return *this; }
	const std::wstring& operator*()const { return i->second; }
public:
	const std::wstring& GetName()const { return i->first; }
	const std::wstring& GetContent()const { return i->second; }
protected:
	fcyXmlAttributeConstIterator(const std::map<std::wstring, std::wstring>::const_iterator& _i)
		: i(_i) {}
public:
	fcyXmlAttributeConstIterator() {}
	fcyXmlAttributeConstIterator(const fcyXmlAttributeIterator& Org)
		: i(Org.i) {}
	fcyXmlAttributeConstIterator(const fcyXmlAttributeConstIterator& Org)
		: i(Org.i) {}
};

// Ԫ���б�
class fcyXmlElementList
{
private:
	std::vector<fcyXmlElement*> m_List;
public:
	fcyXmlElement* operator[](fuInt Index);
	fcyXmlElementList& operator=(const fcyXmlElementList& Right);
public:
	fuInt GetCount() { return m_List.size(); }
	void Append(fcyXmlElement* pObj);
	void Remove(fuInt Index);
	void Clear();
public:
	fcyXmlElementList();
	fcyXmlElementList(const fcyXmlElementList& Org);
	fcyXmlElementList(fcyXmlElementList&& Org);
};

// XMLԪ��
class fcyXmlElement
{
	friend class fcyXmlDocument;
private:
	// ���游����ָ��
	fcyXmlDocument* m_pParent;
	// ���游�ڵ�
	fcyXmlElement* m_pParentNode;

	// ����ڵ�����
	std::wstring m_Name;
	// ����ڵ�����
	std::wstring m_Content;
	// ����ڵ�����ֵ
	std::map<std::wstring, std::wstring> m_Attribute;
	// �����ӽڵ�
	std::vector<fcyXmlElement*> m_Subnodes;

	typedef std::vector<fcyXmlElement*>::iterator SubnodeIter;
	typedef std::vector<fcyXmlElement*>::const_iterator SubnodeConstIter;
	typedef std::map<std::wstring, std::wstring>::iterator AttrIter;
	typedef std::map<std::wstring, std::wstring>::const_iterator AttrConstIter;
public:
	fcyXmlDocument* GetDocument()const { return m_pParent; }
	fcyXmlElement* GetParent()const { return m_pParentNode; }

	const std::wstring& GetName()const { return m_Name; }
	const std::wstring& GetContent()const { return m_Content; }
	void SetContent(const std::wstring& Content) { m_Content = Content; }
	void SetContent(std::wstring&& Content) { m_Content = Content; }

	fuInt GetNodeCount()const { return m_Subnodes.size(); }
	fcyXmlElement* GetNode(fuInt Index)const;
	fcyXmlElement* GetFirstNode(const std::wstring& Name)const;  // ��δ�ҵ�����NULL
	fcyXmlElementList GetNodeByName(const std::wstring& Name)const;
	void AppendNode(fcyXmlElement* pNode);
	void RemoveNode(fcyXmlElement* pNode);
	void RemoveNodeAt(fuInt Index);
	void ClearNodes();

	fuInt GetAttributeCount()const { return m_Attribute.size(); }
	const std::wstring& GetAttribute(const std::wstring& Name)const;
	void SetAttribute(const std::wstring& Name, const std::wstring& Value);
	void SetAttribute(std::wstring&& Name, std::wstring&& Value);
	fBool HasAttribute(const std::wstring& Name)const;
	fcyXmlAttributeIterator GetAttributeIter(const std::wstring& Name);
	const fcyXmlAttributeConstIterator GetAttributeIter(const std::wstring& Name)const;
	fcyXmlAttributeIterator GetFirstAttributeIter();
	const fcyXmlAttributeConstIterator GetFirstAttributeIter()const;
	fcyXmlAttributeIterator GetLastAttributeIter();
	const fcyXmlAttributeConstIterator GetLastAttributeIter()const;
	void RemoveAttribute(const std::wstring& Name);
	fcyXmlAttributeIterator RemoveAttribute(const fcyXmlAttributeIterator& Iter);

	void Save(std::wstring& pOut, fuInt Indentation)const;

	fcyXmlElement* Clone(fcyXmlDocument* pDoc)const;
protected:
	fcyXmlElement(fcyXmlDocument* pParent, const std::wstring& Name);
	~fcyXmlElement();
};

// XML�ĵ�
class fcyXmlDocument
{
private:
	fcyMemPool<sizeof(fcyXmlElement)> m_ElementMem;
	std::vector<fcyXmlElement*> m_ElementPool;

	fcyXmlElement* m_pRootElement;
private: // Ԥ����
	fBool checkUTF8(fcyStream* pStream);
	fBool checkUTF16LE(fcyStream* pStream);
	std::wstring preprocessXml(fcyStream* pStream);                      ///< @brief Ԥ����������ַ�����
private: // ����
	fBool ignoreComment(fcyLexicalReader& tReader);                      ///< @brief ����ע��
	fBool ignorePreprocess(fcyLexicalReader& tReader);                   ///< @brief ����Ԥ����ָ��
	fBool tryReadCDATA(fcyLexicalReader& tReader, std::wstring& tOut);   ///< @brief ��ͼ��ȡCDATA
	fCharW praseEscape(fcyLexicalReader& tReader);                       ///< @brief ����ת���
	std::wstring readName(fcyLexicalReader& tReader);                    ///< @brief ��ȡ����
	std::wstring readString(fcyLexicalReader& tReader);                  ///< @brief ��ȡ�ַ���
	void readAttribute(fcyLexicalReader& tReader, fcyXmlElement* pNode); ///< @brief ��ȡ����
	void readNodes(fcyLexicalReader& tReader, fcyXmlElement* pNode);     ///< @brief ��ȡ�ڵ�
	fcyXmlElement* parserNode(fcyLexicalReader& tReader);                ///< @brief �����ڵ�
public:
	fcyXmlElement* GetRootElement()const { return m_pRootElement; }
	void SetRootElement(fcyXmlElement* pRoot);

	fcyXmlElement* CreateElement(const std::wstring& Name);
	void DeleteElement(fcyXmlElement* pObj);

	void Save(std::wstring& Out)const;
	void Save(fcyStream* pOut)const;     // ����ָ�봦��ʼд��
protected:
	fcyXmlDocument& operator=(const fcyXmlDocument& Org);
	fcyXmlDocument(const fcyXmlDocument& Org);
public:
	fcyXmlDocument();
	fcyXmlDocument(const std::wstring& Str);
	fcyXmlDocument(fcyStream* pStream);      // ����ָ�봦��ʼ��ȡ
	fcyXmlDocument(fcyXmlDocument&& Org);
	~fcyXmlDocument();
};

/// @}
