#include "fcyModelIndexLabel.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////

const char fcyModelIndexLabel::LABELNAME[8] = { "INDEX" };

fBool fcyModelIndexLabel::IsIndex32()
{
	fBool tRet = false;
	for(fuInt i = 0; i<m_IndexData.size(); ++i)
		if(m_IndexData[i] > 65535)
		{
			tRet = true;
			break;
		}
	
	return tRet;
}

void fcyModelIndexLabel::ReadData(fcyStream* pStream)
{
	fcyBinaryReader tReader(pStream);

	// �������
	m_IndexData.clear();

	// ��ȡͷ��
	fuInt tIndexCount = tReader.ReadUInt32();
	fByte tUseInt32Index = tReader.ReadByte();
	fByte tStreamFlag = tReader.ReadByte();

	// Ŀǰֻ֧��Ĭ�ϵ�������
	if(tStreamFlag != 0)
		throw fcyException("fcyModelIndexLabel::ReadData", "Unsupport Stream Type.");
	
	// ��ȡ��������
	m_IndexData.resize(tIndexCount);
	for(fuInt i = 0; i<tIndexCount; ++i)
	{
		if(tUseInt32Index)
			m_IndexData[i] = tReader.ReadUInt32();
		else
			m_IndexData[i] = tReader.ReadUInt16();
	}
}

void fcyModelIndexLabel::WriteData(fcyStream* pStream)
{
	fcyBinaryWriter tWritter(pStream);

	// ȷ��������ʽ
	fBool tIndex32 = IsIndex32();

	// д��ͷ��
	tWritter.Write((fuInt)m_IndexData.size());
	tWritter.Write((fByte)tIndex32);
	tWritter.Write((fByte)0);                  // �����

	// д������
	for(fuInt i = 0; i<m_IndexData.size(); ++i)
	{
		if(tIndex32)
			tWritter.Write((fuInt)m_IndexData[i]);
		else
			tWritter.Write((fuShort)m_IndexData[i]);
	}
}
