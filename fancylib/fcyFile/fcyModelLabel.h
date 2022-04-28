////////////////////////////////////////////////////////////////////////////////
/// @file  fcyModelLabel.h
/// @brief fcyģ���ļ���ǩ����
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../fcyRefObj.h"
#include "../fcyMath.h"
#include "../fcyIO/fcyStream.h"
#include "../fcyIO/fcyBinaryHelper.h"
#include "../fcyMisc/fcyStringHelper.h"

#include <unordered_map>
#include <string>

/// @addtogroup fancy���ļ�֧��
/// @brief �ṩ���ָ�ʽ�ļ��Ķ�д֧��
/// @{

/// @brief ��ǩ����
#define FMM_LABELNAME fuLong

/// @brief ������ǩ
#define FMM_MAKE_LABELNAME8(Str) (*((fuLong*)Str))

/// @brief ������ǩ_4�ֽ�
#define FMM_MAKE_LABELNAME4(Str) (*((fuInt*)Str))

/// @brief ģ�����ݱ�ǩ
class fcyModelLabel;

////////////////////////////////////////////////////////////////////////////////
/// @brief ģ�ͱ�ǩ����
////////////////////////////////////////////////////////////////////////////////
class fcyModelLabelFactory
{
public:
	/// @brief �Զ�ע��
	template<typename T, typename U = fcyModelLabel>  // FIXME!
	class AutoRegister
	{
	public:
		AutoRegister()
		{
			U::GetFactory().RegisterLabel<T>(FMM_MAKE_LABELNAME8(T::LABELNAME));
		}
	};
public:
	/// @brief ��ǩ��������
	struct CreatorFunction :
		public fcyRefObj
	{
		virtual fcyRefPointer<fcyModelLabel> CreateInstance()=0;
	};
protected:
	/// @brief ��ǩ��������ģ��ʵ��
	template<typename T>
	class CreatorFunctionImpl :
  		public fcyRefObjImpl<CreatorFunction>
	{
	public:
		fcyRefPointer<fcyModelLabel> CreateInstance()
		{
			fcyRefPointer<fcyModelLabel> tRet; 
			(*&tRet) = new T();
			return tRet;
		}
	};
protected:
	std::unordered_map< FMM_LABELNAME, fcyRefPointer<CreatorFunction> > m_ConstructFunc;
public:
	/// @brief ��ñ�ǩ����
	CreatorFunction* GetCreator(FMM_LABELNAME Name)
	{
		return m_ConstructFunc[Name];
	}
	/// @brief ע���ǩ����
	template<typename T>
	void RegisterLabel(FMM_LABELNAME Name)
	{
		if(m_ConstructFunc[Name])
			FCYSAFEKILL(m_ConstructFunc[Name]);
		(*&m_ConstructFunc[Name]) = new CreatorFunctionImpl<T>();
	}
	/// @brief ȡ����ǩ����ע��
	void UnregisterLabel(FMM_LABELNAME Name)
	{
		if(m_ConstructFunc[Name])
			m_ConstructFunc[Name] = NULL;
	}
public:
	fcyModelLabelFactory();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief ģ�����ݱ�ǩ
////////////////////////////////////////////////////////////////////////////////
class fcyModelLabel :
	public fcyRefObjImpl<fcyRefObj>
{
public:
	/// @brief ���ع�������
	static fcyModelLabelFactory& GetFactory()
	{
		static fcyModelLabelFactory s_Factory;
		return s_Factory;
	}

	/// @brief �ַ������ݶ�ȡ��������
	static std::wstring ReadString(fcyStream* pStream)
	{
		fcyBinaryReader tReader(pStream);

		fuInt tStrSize = tReader.ReadUInt32();
		std::string pBuffer;
		pBuffer.resize(tStrSize);
		if(tStrSize)
			tReader.ReadChars(&pBuffer[0], tStrSize);
		
		return fcyStringHelper::MultiByteToWideChar(pBuffer, CP_UTF8);
	}
	/// @brief �ַ�������д�븨������
	static void WriteString(fcyStream* pStream, const std::wstring& Str)
	{
		fcyBinaryWriter tWritter(pStream);

		std::string tStr = fcyStringHelper::WideCharToMultiByte(Str, CP_UTF8);
		tWritter.Write((fuInt)tStr.size());
		tWritter.Write(&tStr[0], tStr.size());
	}
protected:
	FMM_LABELNAME m_LabelName;
public:
	/// @brief ��ñ�ǩ��
	FMM_LABELNAME GetLabelName() { return m_LabelName; }

	/// @brief ������ȡ����
	/// @note  ������ǩͷ
	virtual void ReadData(fcyStream* pStream)=0;
	/// @brief д������
	/// @note  ������ǩͷ
	virtual void WriteData(fcyStream* pStream)=0;
protected:
	fcyModelLabel(const fcyModelLabel& Org);
public:
	fcyModelLabel(FMM_LABELNAME LabelName)
		: m_LabelName(LabelName) {}
protected:
	virtual ~fcyModelLabel() {}
};
/// @}
