////////////////////////////////////////////////////////////////////////////////
/// @file  fcyHTTP.h
/// @brief fancy HTTP֧��
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../fcyType.h"

#include "../fcyIO/fcyStream.h"
#include "../fcyOS/fcySocket.h"

#include <unordered_map>
#include <string>

/// @addtogroup fancy������֧��
/// @{

/// @brief �����
namespace fcyNet
{
	/// @brief HTTP��Ӧ����
	enum HTTPRESPONSE
	{
		HTTPRESPONSE_UNKNWON, // δ֪
		HTTPRESPONSE_GET,     // �����ȡRequest-URI����ʶ����Դ
		HTTPRESPONSE_POST,    // ��Request-URI����ʶ����Դ�󸽼��µ�����
		HTTPRESPONSE_HEAD,    // �����ȡ��Request-URI����ʶ����Դ����Ӧ��Ϣ��ͷ
		HTTPRESPONSE_PUT,     // ����������洢һ����Դ������Request-URI��Ϊ���ʶ
		HTTPRESPONSE_DELETE,  // ���������ɾ��Request-URI����ʶ����Դ
		HTTPRESPONSE_TRACE,   // ��������������յ���������Ϣ����Ҫ���ڲ��Ի����
		HTTPRESPONSE_CONNECT, // ��������ʹ��
		HTTPRESPONSE_OPTIONS  // �����ѯ�����������ܣ����߲�ѯ����Դ��ص�ѡ�������
	};

	/// @brief HTTP��Ϣͷ
	class HttpHeader
	{
	protected:
		std::unordered_map<std::string, std::string> m_Header;
	public:
		/// @brief ����
		HttpHeader& operator=(const HttpHeader& right);
		/// @brief     ���ֵ
		/// @param[in] Key ��
		std::string& operator[](const std::string& Key);
		/// @brief     ���ֵ
		/// @param[in] Key ��
		const std::string& GetValue(const std::string& Key);
		/// @brief     ����ֵ
		/// @param[in] Key   ��
		/// @param[in] Value ֵ
		void SetValue(const std::string& Key, const std::string& Value);
		/// @brief     �Ƴ���
		/// @param[in] Key ��
		fBool RemoveKey(const std::string& Key);
		/// @brief ����Text
		void ToString(std::string& Data);
		/// @brief ��������
		void Send(fcySocket::Client* pClient);
	public:
		/// @brief ����һ���յ�Header
		HttpHeader();
		/// @brief ��Client��ȡHeader
		HttpHeader(fcySocket::Client* pClient);
		~HttpHeader();
	};

	/// @brief      �ָ�URL
	/// @param[in]  URL  ��ַ
	/// @param[out] Host ����
	/// @param[out] Port �˿ڣ�Ĭ�Ϸ���80
	/// @param[out] Path ���·��
	void SplitURL(fcStr URL, std::string& Host, fuShort& Port, std::string& Path);

	/// @brief      ������Ӧͷ
	/// @param[in]  Data        ԭʼ����
	/// @param[out] HTTPVersion HTTP�汾��
	/// @param[out] Code        ����
	/// @param[out] Desc        ����
	void ParseRespondHeader(fcStr Data, std::string& HTTPVersion, fuInt& Code, std::string& Desc);

	/// @brief      һֱ��ȡֱ��/r/n
	/// @param[in]  pClient Socket����
	/// @param[out] Out     ����ַ���
	void RecvUntilCRLF(fcySocket::Client* pClient, std::string& Out);

	/// @brief      ��ȡLength��������
	/// @param[in]  pClient Socket����
	/// @param[in]  Length  ����
	/// @param[out] pOut ����ڴ�Ķ���
	void RecvData(fcySocket::Client* pClient, fuInt Length, fcyStream** pOut);

	/// @brief      ����һ��Get����
	/// @param[in]  pClient Socket����
	/// @param[in]  Host    ��վ
	/// @param[in]  Path    ��Դ·��
	void SendGetRequest(fcySocket::Client* pClient, const std::string& Host, const std::string& Path);

	/// @brief      HTTP���ļ�
	/// @note       ʹ��Chrome��UA������HTTP�ļ�
	/// @param[in]  URL      ����
	/// @param[out] pDataOut ��������
	void HTTPReadFile(fcStr URL, fcyStream** pDataOut);
};

/// @}
