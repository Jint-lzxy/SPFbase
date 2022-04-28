#include "fcyIni.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////

fcyIniSection::fcyIniSection(const wstring& Name)
	: m_Name(Name)
{}

fcyIniSection::~fcyIniSection(void)
{}

void fcyIniSection::writeToStr(std::wstring& Out)
{
	Out += (L"[" + m_Name + L"]\n");
	
	vector<wstring>::iterator i = m_KeyList.begin();
	while(i!=m_KeyList.end())
	{
		Out += ((*i) + L"=" + m_Dict[(*i)] + L"\n");
		++i;
	}

	Out += L"\n";
}

fcStrW fcyIniSection::GetName()
{
	return m_Name.c_str();
}

fuInt fcyIniSection::GetCount()
{
	return m_KeyList.size();
}

fcStrW fcyIniSection::GetKey(fuInt Index)
{
	if(Index >= GetCount())
		return NULL;
	else
		return m_KeyList[Index].c_str();
}

fcStrW fcyIniSection::GetValue(fuInt Index)
{
	if(Index >= GetCount())
		return NULL;
	else
		return m_Dict[m_KeyList[Index]].c_str();
}

fcStrW fcyIniSection::GetValue(fcStrW Key, fcStrW Default)
{
	if(m_Dict.find(Key) == m_Dict.end())
		return Default;
	else
		return m_Dict[Key].c_str();
}

fBool fcyIniSection::SetValue(fcStrW Key, fcStrW Value)
{
	if(Key == NULL || Value == NULL)
		return false;
	if(m_Dict.find(Key) == m_Dict.end())
	{
		m_Dict[Key] = Value;
		m_KeyList.push_back(Key);
	}
	else
	{
		m_Dict[Key] = Value;
	}
	return true;
}

fBool fcyIniSection::Remove(fcStrW Key)
{
	unordered_map<wstring, wstring>::iterator i = 
		m_Dict.find(Key);

	if(i == m_Dict.end())
		return false;
	
	m_Dict.erase(i);

	vector<wstring>::iterator j = m_KeyList.begin();
	for(; j!=m_KeyList.end(); j++)
	{
		if((*j) == Key)
			break;
	}

	if(j != m_KeyList.end())
		m_KeyList.erase(j);

	return true;
}

////////////////////////////////////////////////////////////////////////////////

fcyIni::fcyIni(void)
{
}

fcyIni::fcyIni(const wstring& Src)
{
	fcyLexicalReader tReader(Src);
	
	fcyIniSection* pSec = NULL;
	while((pSec = parseIniSection(tReader))!=NULL)
	{
		AppendSection(pSec);
	}
}

fcyIni::fcyIni(fcyStream* pStream)
{
	fcyLexicalReader tReader(pStream);

	fcyIniSection* pSec = NULL;
	while((pSec = parseIniSection(tReader))!=NULL)
	{
		AppendSection(pSec);
	}
}

fcyIni::~fcyIni(void)
{
	unordered_map<wstring, fcyIniSection*>::iterator i = m_Dict.begin();
	while(i != m_Dict.end())
	{
		FCYSAFEDEL(i->second);

		++i;
	}
}

fBool fcyIni::ignoreComment(fcyLexicalReader& tReader)
{
	if(tReader.TryMatch(L';', true, true))
	{
		fCharW tChar;

		// ������ĩ����EOF
		while(!(tReader.IsEOF() || (tChar=tReader.ReadChar())==L'\n')) {}

		return true;
	}
	return false;
}

fcyIniSection* fcyIni::parseIniSection(fcyLexicalReader& tReader)
{
	// ����ע��
	while(ignoreComment(tReader));

	// ƥ��һ��[
	if(tReader.TryMatch(L'[', true, true))
	{
		wstring tSecName;
		fCharW tChar;

		while(1)
		{
			tChar = tReader.ReadChar();
			if(tChar == L'\n') // ������ĩ
				throw fcyLexicalException("fcyIni::parseIniSection", "expect ']' but found '\\n'", tReader.GetLine(), tReader.GetRow());
			else if(tChar == L']') // �ڶ�ȡ����
				break;
			else
				tSecName += tChar;
		}

		// ����INI��
		fcyIniSection* tSec = new fcyIniSection(tSecName);

		// ��ȡKey-Value
		while(1)
		{
			// ����Comment
			while(ignoreComment(tReader));

			// ���Կո�
			tReader.IgnoreSpace();

			// �Ƿ����
			if(tReader.IsEOF())
				break;

			tChar = tReader.PeekChar();
			if(tChar == L';')
				continue;
			else if(tChar == L'[')
				break;

			wstring Key;
			wstring Value;
			
			// ��ȡkey
			while((tChar = tReader.ReadChar())!=L'=')
			{
				if(tChar == L'\n')
				{
					FCYSAFEDEL(tSec);
					throw fcyLexicalException("fcyIni::parseIniSection", "expect '=' but found ''\n'", tReader.GetLine(), tReader.GetRow());
				}
				else
					Key += tChar;
			}

			// ��ȡValue
			// ���key
			if(Key.empty())
			{
				FCYSAFEDEL(tSec);
				throw fcyLexicalException("fcyIni::parseIniSection", "key is empty but found value", tReader.GetLine(), tReader.GetRow());
			}

			// ��ȡValueֱ����ĩ
			while(!( tReader.IsEOF() || (tChar = tReader.ReadChar())==L'\n'))
			{
				if(tChar == L'\0')
					break;
				else if(tChar != L'\r')
					Value += tChar;
			}

			// ����ֵ
			tSec->SetValue(Key.c_str(), Value.c_str());
		}

		// ���ؽ�
		return tSec;
	}
	else
		return NULL;
}

fBool fcyIni::AppendSection(fcyIniSection* pSec)
{
	if(!pSec || m_Dict.find(pSec->GetName()) != m_Dict.end())
		return false;

	m_SecList.push_back(pSec->GetName());
	m_Dict[pSec->GetName()] = pSec;

	return true;
}

fBool fcyIni::IsContain(fcStrW SecName)
{
	return m_Dict.find(SecName) != m_Dict.end();
}

fBool fcyIni::Remove(fcStrW SecName)
{
	vector<wstring>::iterator i = 
		m_SecList.begin();
	for(; i != m_SecList.end(); ++i)
	{
		if((*i) == SecName)
			break;
	}

	unordered_map<wstring, fcyIniSection*>::iterator j =
		m_Dict.find(SecName);

	if(i == m_SecList.end() && j == m_Dict.end())
		return false;

	if(i != m_SecList.end())
		m_SecList.erase(i);
	if(j != m_Dict.end())
	{
		FCYSAFEDEL(j->second);
		m_Dict.erase(j);
	}

	return true;
}

fcyIniSection* fcyIni::GetSection(fcStrW SecName)
{
	if(IsContain(SecName))
		return m_Dict[SecName];
	else
		return NULL;
}

fcStrW fcyIni::GetValue(fcStrW Sec, fcStrW Key, fcStrW Default)
{
	fcyIniSection* pSec = GetSection(Sec);
	if(!pSec)
		return Default;
	return pSec->GetValue(Key, Default);
}

void fcyIni::SetValue(fcStrW Sec, fcStrW Key, fcStrW Value)
{
	fcyIniSection* pSec = GetSection(Sec);
	if(!pSec)
	{
		AppendSection(new fcyIniSection(Sec));
		pSec = GetSection(Sec);
	}

	pSec->SetValue(Key, Value);
}

void fcyIni::WriteToStr(std::wstring& Out)
{
	vector<wstring>::iterator i = m_SecList.begin();
	while(i!=m_SecList.end())
	{
		m_Dict[(*i)]->writeToStr(Out);

		++i;
	}
}

fBool fcyIni::WriteToStream(fcyStream* pStream)
{
	if(!pStream->CanWrite())
		return false;

	wstring tTemp;
	WriteToStr(tTemp);

	// UTF 16 BOM
	fByte tUTF16LE[2] = { 0xFF, 0xFE };
	pStream->SetLength(0);
	pStream->WriteBytes(tUTF16LE, 2, NULL);
	if(FCYFAILED(pStream->WriteBytes((fcData)&tTemp[0], tTemp.length()*sizeof(wchar_t), NULL)))
		return false;

	return true;
}
