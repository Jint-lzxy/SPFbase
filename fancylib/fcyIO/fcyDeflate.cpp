#include "fcyDeflate.h"

extern "C"
{
	#include <zlib.h>
}

#define DEFLATE_BUFFERSIZE 512

using namespace std;
using namespace fcyDeflate;

////////////////////////////////////////////////////////////////////////////////

fResult fcyDeflate::CompressStreamToMem(fcyStream* pIn, fcyStream** pOut, fInt Level)
{
	z_stream tStream;
	int tErr;
	fByte tOutBuffer[DEFLATE_BUFFERSIZE], tInBuffer[DEFLATE_BUFFERSIZE];

	if(!pOut || !pIn || Level<-1 || Level>9)
		return FCYERR_INVAILDPARAM;
	
	// ׼��������
	memset(&tStream, 0, sizeof(z_stream));
	tStream.next_in = tInBuffer;   // ԭʼ������
	tStream.next_out = tOutBuffer; // �����ѹ��������
	
	tStream.avail_out = DEFLATE_BUFFERSIZE;
	
	// ��ʼ����ѹ��
    tErr = deflateInit(&tStream, Level);
	if (tErr != Z_OK) 
		return FCYERR_INTERNALERR;

	// ���������
	fcyMemStream* pOutStream = new fcyMemStream(NULL, 0, true, true);

	// ѹ��ѭ��
	tErr = Z_OK;
	while(tErr != Z_STREAM_END)
	{
		fBool tbEOF = false;
		if(tStream.avail_in == 0)
		{
			// ��ȡһ������������
			fLen tInLen = 0;
			pIn->ReadBytes(tInBuffer, DEFLATE_BUFFERSIZE, &tInLen);

			if(tInLen < DEFLATE_BUFFERSIZE)
				tbEOF = true;

			// ����next_in��avail_in
			tStream.next_in = tInBuffer;
			tStream.avail_in = (fuInt)tInLen;
		}
		
		tErr = deflate(&tStream, tbEOF ? Z_FINISH : Z_NO_FLUSH);
		if(tErr != Z_OK && tErr != Z_STREAM_END) // ��������
		{
			inflateEnd(&tStream);     // �ر���
			FCYSAFEKILL(pOutStream);  // ���ٽ�ѹ��
			if(tErr == Z_DATA_ERROR)
				return FCYERR_INVAILDDATA;
			else
				return FCYERR_INTERNALERR;
		}

		if(tStream.avail_out == 0 || tErr == Z_STREAM_END)
		{
			pOutStream->WriteBytes(tOutBuffer, DEFLATE_BUFFERSIZE - tStream.avail_out, NULL);

			tStream.next_out = tOutBuffer;
			tStream.avail_out = DEFLATE_BUFFERSIZE;
		}
	}

	deflateEnd(&tStream);

	*pOut = pOutStream;
	pOutStream->SetPosition(FCYSEEKORIGIN_BEG, 0);

	return FCYERR_OK;
}

fResult fcyDeflate::DecompressStreamToMem(fcyStream* pIn, fcyStream** pOut)
{
	z_stream tStream;
	int tErr;
	fByte tOutBuffer[DEFLATE_BUFFERSIZE], tInBuffer[DEFLATE_BUFFERSIZE];

	if(!pOut || !pIn)
		return FCYERR_INVAILDPARAM;

	// ׼��������
	memset(&tStream, 0, sizeof(z_stream));
	tStream.next_in = tInBuffer;   // ѹ��������
	tStream.next_out = tOutBuffer; // �����
	
	tStream.avail_out = DEFLATE_BUFFERSIZE;
	
	// ��ʼ����ѹ��
    tErr = inflateInit(&tStream);
	if (tErr != Z_OK) 
		return FCYERR_INTERNALERR;

	// ���������
	fcyMemStream* pOutStream = new fcyMemStream(NULL, 0, true, true);

	// ��ѹ��ѭ��
	tErr = Z_OK;
	while(tErr != Z_STREAM_END)
	{
		if(tStream.avail_in == 0)
		{
			// ��ȡһ������������
			fLen tInLen = 0;
			pIn->ReadBytes(tInBuffer, DEFLATE_BUFFERSIZE, &tInLen);

			// ���������ˣ�����
			if(tInLen == 0)
				break;

			// ����next_in��avail_in
			tStream.next_in = tInBuffer;
			tStream.avail_in = (fuInt)tInLen;
		}
		
		tErr = inflate(&tStream, Z_SYNC_FLUSH);
		if(tErr != Z_OK && tErr != Z_STREAM_END) // ��������
		{
			if(tErr == Z_DATA_ERROR)
			{
				// ���Բ���һ����ͷ

				static char tFalseHeader[2] =
				{
					0x8 + 0x7 * 0x10,
					(((0x8 + 0x7 * 0x10) * 0x100 + 30) / 31 * 31) & 0xFF,
				};
				inflateReset(&tStream);
				tStream.next_in = (Bytef*)tFalseHeader;
				tStream.avail_in = sizeof(tFalseHeader);

				pOutStream->SetLength(0);
				pIn->SetPosition(FCYSEEKORIGIN_BEG, 0);

				tErr = inflate(&tStream, Z_NO_FLUSH);

				continue;
			}
			else
			{
				inflateEnd(&tStream);     // �ر���
				FCYSAFEKILL(pOutStream);  // ���ٽ�ѹ��
				if(tErr == Z_DATA_ERROR)
					return FCYERR_INVAILDDATA;
				else
					return FCYERR_INTERNALERR;
			}
		}

		if(tStream.avail_out != DEFLATE_BUFFERSIZE)
		{
			pOutStream->WriteBytes(tOutBuffer, DEFLATE_BUFFERSIZE - tStream.avail_out, NULL);

			tStream.next_out = tOutBuffer;
			tStream.avail_out = DEFLATE_BUFFERSIZE;
		}
	}

	inflateEnd(&tStream);

	*pOut = pOutStream;
	pOutStream->SetPosition(FCYSEEKORIGIN_BEG, 0);

	return FCYERR_OK;
}

fResult fcyDeflate::DecompressStreamToMemEx(fcyStream* pIn, fInt Flag, fcyStream** pOut)
{
	z_stream tStream;
	int tErr;
	fByte tOutBuffer[DEFLATE_BUFFERSIZE], tInBuffer[DEFLATE_BUFFERSIZE];

	if(!pOut || !pIn)
		return FCYERR_INVAILDPARAM;

	// ׼��������
	memset(&tStream, 0, sizeof(z_stream));
	tStream.next_in = tInBuffer;   // ѹ��������
	tStream.next_out = tOutBuffer; // �����
	
	tStream.avail_out = DEFLATE_BUFFERSIZE;
	
	// ��ʼ����ѹ��
    tErr = inflateInit2(&tStream, Flag);
	if (tErr != Z_OK) 
		return FCYERR_INTERNALERR;

	// ���������
	fcyMemStream* pOutStream = new fcyMemStream(NULL, 0, true, true);

	// ��ѹ��ѭ��
	tErr = Z_OK;
	while(tErr != Z_STREAM_END)
	{
		if(tStream.avail_in == 0)
		{
			// ��ȡһ������������
			fLen tInLen = 0;
			pIn->ReadBytes(tInBuffer, DEFLATE_BUFFERSIZE, &tInLen);

			// ���������ˣ�����
			if(tInLen == 0)
				break;

			// ����next_in��avail_in
			tStream.next_in = tInBuffer;
			tStream.avail_in = (fuInt)tInLen;
		}
		
		tErr = inflate(&tStream, Z_SYNC_FLUSH);
		if(tErr != Z_OK && tErr != Z_STREAM_END) // ��������
		{
			inflateEnd(&tStream);     // �ر���
			FCYSAFEKILL(pOutStream);  // ���ٽ�ѹ��
			if(tErr == Z_DATA_ERROR)
				return FCYERR_INVAILDDATA;
			else
				return FCYERR_INTERNALERR;
		}

		if(tStream.avail_out != DEFLATE_BUFFERSIZE)
		{
			pOutStream->WriteBytes(tOutBuffer, DEFLATE_BUFFERSIZE - tStream.avail_out, NULL);

			tStream.next_out = tOutBuffer;
			tStream.avail_out = DEFLATE_BUFFERSIZE;
		}
	}

	inflateEnd(&tStream);

	*pOut = pOutStream;
	pOutStream->SetPosition(FCYSEEKORIGIN_BEG, 0);

	return FCYERR_OK;
}
