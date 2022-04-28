////////////////////////////////////////////////////////////////////////////////
/// @file  fcyJson.h
/// @brief fcyJson������
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "fcyLexicalParser.h"

#include <string>
#include <vector>
#include <unordered_map>

/// @addtogroup fancy���������
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief JSONԪ������
////////////////////////////////////////////////////////////////////////////////
enum FCYJSONVALUETYPE
{
	FCYJSONVALUETYPE_NULL,   ///< @brief ������
	FCYJSONVALUETYPE_BOOL,   ///< @brief �߼�����
	FCYJSONVALUETYPE_NUMBER, ///< @brief ��������
	FCYJSONVALUETYPE_STRING, ///< @brief �ַ�������
	FCYJSONVALUETYPE_LIST,   ///< @brief ������
	FCYJSONVALUETYPE_DICT,   ///< @brief �ֵ�����
};

class fcyJsonString;
class fcyJsonList;
class fcyJsonDict;

////////////////////////////////////////////////////////////////////////////////
/// @brief JSONֵ
////////////////////////////////////////////////////////////////////////////////
class fcyJsonValue
{
	friend class fcyJsonList;
	friend class fcyJsonDict;
	friend class fcyJson;
protected:
	FCYJSONVALUETYPE m_Type;  ///< @brief JSON��������

	/// @brief ������
	union
	{
		fBool m_ValueBool;     ///< @brief �߼���
		fDouble m_ValueNumber; ///< @brief ������
	};
protected:
	/// @brief      д���ַ���
	/// @param[out] OutStr �����Ŀ���ַ���
	virtual void writeToStr(std::wstring& OutStr);
public:  // ����ת��
	FCYJSONVALUETYPE GetType(); ///< @brief ��������
	
	fBool ToNull();             ///< @brief ��NULL
	                            ///< @note  true��ʾNULL, false��ʾ��NULL
	fBool ToBool();             ///< @brief ��Bool
	                            ///< @note  true��ʾtrue, false��ʾfalse���Bool��
	fDouble ToNumber();         ///< @brief ������
	                            ///< @note  ��Number����0��ʾ
public:  // ���ڽӿ�ת��
	virtual fcyJsonString* ToString(); ///< @brief ת�����ַ���
	virtual fcyJsonList* ToList();     ///< @brief ת��������
	virtual fcyJsonDict* ToDict();     ///< @brief ת�����ֵ�
public: // ֵ���Ͳ���, ��ֵ���ͷ���false
	fBool SetValue();                  ///< @brief  ����Ϊnull
	                                   ///< @return ���������ֵ���ͣ��򷵻ؼ�
	fBool SetValue(fBool Value);       ///< @brief  ����Ϊbool
	                                   ///< @return ���������ֵ���ͣ��򷵻ؼ�
	fBool SetValue(fDouble Value);     ///< @brief  ����Ϊ����
	                                   ///< @return ���������ֵ���ͣ��򷵻ؼ�
public: // �����ֶ�����
	fcyJsonValue();                      ///< @brief ����Ϊnullֵ����
	fcyJsonValue(fBool Value);           ///< @brief ����Ϊboolֵ����
	fcyJsonValue(fDouble Value);         ///< @brief ����Ϊ��ֵ����
	fcyJsonValue(FCYJSONVALUETYPE Type); ///< @brief ����ΪString/List/Dict
	virtual ~fcyJsonValue();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief JSON�ַ���
////////////////////////////////////////////////////////////////////////////////
class fcyJsonString :
	public fcyJsonValue
{
protected:
	std::wstring m_Str;   ///< @brief �ַ�������ֵ
protected:
	void writeToStr(std::wstring& OutStr);
public:
	fcyJsonString* ToString();
public:
	fcStrW GetStr();           ///< @brief ����ַ���ָ��
	void SetStr(fcStrW Value); ///< @brief �����ַ���
public:
	/// @brief     ���캯��
	/// @param[in] Value �ַ���ֵ
	fcyJsonString(fcStrW Value);
	~fcyJsonString();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief JSON����
/// @note  JsonList���Ḻ�������Ӷ���
////////////////////////////////////////////////////////////////////////////////
class fcyJsonList : 
	public fcyJsonValue
{
protected:
	std::vector<fcyJsonValue*> m_ObjList;   ///< @brief �ڲ�����
protected:
	void writeToStr(std::wstring& OutStr);
public:
	fcyJsonList* ToList();
public:
	/// @brief     ��ö���
	/// @param[in] Index ����
	/// @return    ������������ڷ���NULL�����򷵻ض���ָ��
	fcyJsonValue* GetValue(fuInt Index);

	/// @brief     ���ö���
	/// @param[in] Index ����
	/// @param[in] pNew  ����ָ��
	/// @return    ���ز����Ƿ�ɹ�
	fResult SetValue(fuInt Index, fcyJsonValue* pNew);

	/// @brief     ������ĩ��׷�Ӷ���
	/// @param[in] pNew ����ָ��
	void Append(fcyJsonValue* pNew);

	/// @brief     ɾ��Index������
	/// @param[in] Index ��������
	fResult Remove(fuInt Index);

	/// @brief ���
	void Clear();

	/// @brief ���ض�������
	fuInt GetCount();
public:
	/// @brief ���캯��
	fcyJsonList();
	~fcyJsonList();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief JSON�ֵ�
////////////////////////////////////////////////////////////////////////////////
class fcyJsonDict :
	public fcyJsonValue
{
protected:
	std::vector<std::wstring> m_ObjList;                      ///< @brief ��������
	std::unordered_map<std::wstring, fcyJsonValue*> m_Cache;  ///< @brief �����ֵ仺��
protected:
	void writeToStr(std::wstring& OutStr);
public:
	fcyJsonDict* ToDict();
public:
	/// @brief      ���ض���
	/// @param[in]  Index ��������
	/// @param[out] pKeyOut ��
	/// @return     ���ض���ָ�룬������Խ�緵��NULL
	fcyJsonValue* GetValue(fuInt Index, fcStrW* pKeyOut = NULL);

	/// @brief     ���ض���
	/// @param[in] Name �������
	/// @return    ���ض���ָ�룬�������ڶ��󷵻�NULL
	fcyJsonValue* GetValue(fcStrW Name);

	/// @brief     ���ö���
	/// @note      ��������Ѿ���������ͷ�ԭ�ж���
	/// @param[in] Name �������
	/// @param[in] pNew ����ָ��
	void SetValue(fcStrW Name, fcyJsonValue* pNew);

	/// @brief     �Ƿ��������
	/// @param[in] Name ����ļ���
	/// @return    true=��������false=û��������
	fBool Contain(fcStrW Name);

	/// @brief     �Ƴ�����
	/// @param[in] Index �������
	/// @return    true=�ɹ���false=ʧ��
	fBool Remove(fcStrW Index);

	/// @brief ���
	void Clear();

	/// @brief ����Ԫ�ظ���
	fuInt GetCount();
public:
	/// @brief ���캯��
	fcyJsonDict();
	~fcyJsonDict();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief JSON������
/// @note  ע��ý�����ֻ�������һ��Ԫ�ء�
////////////////////////////////////////////////////////////////////////////////
class fcyJson
{
private:
	fcyJsonValue* m_Root;  ///< @brief ���ڵ�
private: // ��������
	fcyJsonValue* parseValue(fcyLexicalReader& Context);   ///< @brief ����һ��ֵ
	fcyJsonValue* parseNumber(fcyLexicalReader& Context);  ///< @brief ����һ����ֵ
	fcyJsonString* parseString(fcyLexicalReader& Context); ///< @brief ����һ���ַ���
	fcyJsonList* parseList(fcyLexicalReader& Context);     ///< @brief ����һ����
	fcyJsonDict* parseDict(fcyLexicalReader& Context);     ///< @brief ����һ���ֵ�
public:
	fcyJsonValue* GetRoot();             ///< @brief ����һ�����ڵ�
	void SetRoot(fcyJsonValue* pValue);  ///< @brief ���ø��ڵ�

	void WriteToStr(std::wstring& pOut); ///< @brief д���ַ���
	void WriteToStream(fcyStream* pOut); ///< @brief д����
public:
	fcyJson();                           ///< @brief ���캯��
	fcyJson(const std::wstring& Str);    ///< @brief ���ı�����JSON
	fcyJson(fcyStream* pStream);         ///< @brief ��������JSON
	~fcyJson();
};
/// @}
