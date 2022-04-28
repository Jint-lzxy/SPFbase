#include "fcyModelMeshFile.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////

fcyRefPointer<fcyModelLabel> fcyModelMeshFile::FindLabel(fuLong LabelName)
{
	for(fuInt i = 0; i<m_Labels.size(); ++i)
	{
		if(m_Labels[i]->GetLabelName() == LabelName)
			return m_Labels[i];
	}

	return NULL;
}

void fcyModelMeshFile::Load(fcyStream* pStream, fBool IgnoreUnsupportLabel)
{
	fcyBinaryReader tReader(pStream);
	
	// �������
	m_Author.clear();
	m_Description.clear();
	m_Labels.clear();

	// ��ȡ�ļ�ͷ����֤
	if(FMM_MAKE_LABELNAME4("FMM\0") != tReader.ReadUInt32())
		throw fcyException("fcyModelMeshFile::Load", "File format error.");
	if(Version != tReader.ReadUInt32())
		throw fcyException("fcyModelMeshFile::Load", "Version not support.");
	fuInt tBlockCount = tReader.ReadUInt32();
	m_Author = fcyModelLabel::ReadString(pStream);
	m_Description = fcyModelLabel::ReadString(pStream);

	// ��ȡ��
	for(fuInt i = 0; i<tBlockCount; ++i)
	{
		fuLong tLable = tReader.ReadUInt64(); // ���ǩͷ
		fuInt tLen = tReader.ReadUInt32();    // ���С

		// ��¼��ǰ�Ķ�ȡλ��
		fLen tPos = pStream->GetPosition();

		// ��ȡ��ǩ
		fcyModelLabelFactory::CreatorFunction* tFunc = fcyModelLabel::GetFactory().GetCreator(tLable);
		if(!tFunc)
		{
			if(IgnoreUnsupportLabel)
			{
				// ������ʶ��Ŀ�
				pStream->SetPosition(FCYSEEKORIGIN_CUR, tLen);
			}
			else
				throw fcyException("fcyModelMeshFile::Load", "Unsupport label found.");
		}
		else
		{
			// ��ȡ��
			fcyRefPointer<fcyModelLabel> pLabel = tFunc->CreateInstance();
			pLabel->ReadData(pStream);

			m_Labels.push_back(pLabel);

			// ��õ�ǰλ��
			fuInt tBlockLen = (fuInt)(pStream->GetPosition() - tPos);
			if(tBlockLen != tLen)
				throw fcyException("fcyModelMeshFile::Load", "Error detected when read block.");
		}
	}
}


void fcyModelMeshFile::Save(fcyStream* pStream)
{
	fcyBinaryWriter tWritter(pStream);

	// д���ļ�ͷ
	tWritter.Write((fuInt)FMM_MAKE_LABELNAME4("FMM\0"));
	tWritter.Write((fuInt)Version);
	tWritter.Write((fuInt)m_Labels.size());
	fcyModelLabel::WriteString(pStream, m_Author);
	fcyModelLabel::WriteString(pStream, m_Description);

	// д���
	for(fuInt i = 0; i<m_Labels.size(); ++i)
	{
		// д���ǩͷ
		tWritter.Write((fuLong)m_Labels[i]->GetLabelName());
		
		// ���С
		tWritter.Write((fuInt)0);

		// ��õ�ǰλ��
		fLen tStartOfBlockPos = pStream->GetPosition();

		// д������
		m_Labels[i]->WriteData(pStream);

		// ��ȡ��ǰλ��
		fLen tEndOfBlockPos = pStream->GetPosition();
		fLen tLen = tEndOfBlockPos - tStartOfBlockPos;

		// ��ת��д������
		pStream->SetPosition(FCYSEEKORIGIN_BEG, tStartOfBlockPos - 4);
		tWritter.Write((fuInt)tLen);

		// ���ص���һ����ǩ��
		pStream->SetPosition(FCYSEEKORIGIN_BEG, tEndOfBlockPos);
	}
}
