#include "fcyModelVertexLabel.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////

const char fcyModelVertexLabel::LABELNAME[8] = { "VERTEX" };

fuInt fcyModelVertexLabel::CalcuVertexSize()const
{
	fuInt tVertSize = 0;

	for(fuInt i = 0; i<m_VertElementList.size(); ++i)
	{
		switch(m_VertElementList[i].Type)
		{
		case ELEMENTTYPE_FLOAT:
			tVertSize += 4; 
			break;
		case ELEMENTTYPE_FLOAT2:
			tVertSize += 4 * 2; 
			break;
		case ELEMENTTYPE_FLOAT3:
			tVertSize += 4 * 3; 
			break;
		case ELEMENTTYPE_FLOAT4:
			tVertSize += 4 * 4; 
			break;
		case ELEMENTTYPE_COLOR:
		case ELEMENTTYPE_UBYTE4:
			tVertSize += 4; 
			break;
		case ELEMENTTYPE_SHORT2:
			tVertSize += 2 * 2; 
			break;
		case ELEMENTTYPE_SHORT4:
			tVertSize += 2 * 4; 
			break;
		default:
			throw fcyException("fcyModelVertexLabel::CalcuVertexSize", "Unrecognized element type.");
		}
	}

	return tVertSize;
}

void fcyModelVertexLabel::PushVertex(void* pData, fuInt VertexSize)
{
	// ����ռ�
	m_VertexData.resize(m_VertexData.size() + VertexSize);

	// �����ڴ�
	memcpy(&m_VertexData[m_VertexData.size() - VertexSize], pData, VertexSize);
}

void fcyModelVertexLabel::ReadData(fcyStream* pStream)
{
	fcyBinaryReader tReader(pStream);

	// �������
	m_VertElementList.clear();
	m_VertexData.clear();

	// ��ȡͷ��
	fuInt tVertexCount = tReader.ReadUInt32();
	fuInt tVertexElementCount = tReader.ReadUInt32();
	fByte tStreamFlag = tReader.ReadByte();

	// Ŀǰֻ֧��Ĭ�ϵ�����־
	if(tStreamFlag != 0)
		throw fcyException("fcyModelVertexLabel::ReadData", "Unsupport Stream Type.");
	
	// ���ض�������
	m_VertElementList.resize(tVertexElementCount);
	for(fuInt i = 0; i<tVertexElementCount; ++i)
	{
		m_VertElementList[i].Type = (ELEMENTTYPE)tReader.ReadUInt32();
		m_VertElementList[i].Usage = tReader.ReadUInt64();
		m_VertElementList[i].UsageIndex = tReader.ReadByte();
	}

	// ���㶥���С
	fuInt tVertSize = CalcuVertexSize();

	// ���ض�������
	m_VertexData.resize(tVertSize * tVertexCount);

	// ֱ�Ӷ�ȡsize���ݲ����
	tReader.ReadBytes((fByte*)GetVertexDataPointer(), GetVertexDataSize());
}

void fcyModelVertexLabel::WriteData(fcyStream* pStream)
{
	fcyBinaryWriter tWritter(pStream);

	// �������ݼ��
	fuInt tVertSize = CalcuVertexSize();
	if(tVertSize == 0 || m_VertexData.size() % tVertSize != 0)
		throw fcyException("fcyModelVertexLabel::WriteData", "Size of vertex is not correctly.");

	// д������ͷ
	tWritter.Write((fuInt)m_VertexData.size() / tVertSize);
	tWritter.Write((fuInt)m_VertElementList.size());
	tWritter.Write((fByte)0);  // �����

	// д����������
	for(fuInt i = 0; i<m_VertElementList.size(); ++i)
	{
		tWritter.Write((fuInt)m_VertElementList[i].Type);
		tWritter.Write((fuLong)m_VertElementList[i].Usage);
		tWritter.Write((fByte)m_VertElementList[i].UsageIndex);
	}

	// д����������
	tWritter.Write((fcData)GetVertexDataPointer(), GetVertexDataSize());
}
