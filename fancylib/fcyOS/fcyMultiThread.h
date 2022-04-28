////////////////////////////////////////////////////////////////////////////////
/// @file  fcyMultiThread.h
/// @brief fancy���߳�֧��
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../fcyType.h"
#include "../fcyException.h"

#include <Windows.h>

/// @addtogroup fancy��ײ�֧��
/// @brief ʵ��һϵ���漰ϵͳ�ں˲����ĺ���
/// @{

////////////////////////////////////////////////////////////////////////////////
/// @brief fcy�̻߳���
/// @note  ͨ���̳и��ಢ��дThreadJob��ʵ�ֶ��߳�
////////////////////////////////////////////////////////////////////////////////
class fcyBaseThread
{
private:
	HANDLE m_hThread;  ///< @brief �ڲ����߳̾��
	DWORD m_hThreadID; ///< @brief �߳�ID
private:
	/// @brief     [˽��] ִ���̵߳İ�װ����
	/// @param[in] p ���߳���ָ��
	/// @return    �����߳�ִ��״̬���μ�MSDN
	static DWORD WINAPI execute(void* p);
protected:
	/// @brief  [����] �̹߳�������
	/// @note   ʹ�ö��߳�ʱ���븲д�ĺ���
	/// @return �����߳�ִ��״̬���μ�MSDN
	virtual fuInt ThreadJob()=0;
public:
	/// @brief   �����ڲ��߳̾��
	/// @warning �벻Ҫ�ֶ��رշ��ص��ں˶���
	/// @return  �߳̾��
	HANDLE GetHandle();

	/// @brief  �ָ��߳�ִ��
	/// @return true=�ɹ���false=ʧ��
	fBool Resume();
	
	/// @brief  ��ͣ�߳�ִ��
	/// @return true=�ɹ���false=ʧ��
	fBool Suspend();

	/// @brief     �ȴ��߳�ִ�����
	/// @param[in] TimeLimited �ȴ�ʱ�䣬��Ϊ-1��ʾ���޵ȴ�
	/// @return    true=�ɹ���false=��ʱ������Win32����
	fBool Wait(fInt TimeLimited=-1);

	/// @brief     ��ֹ�߳�
	/// @param[in] ExitCode �̷߳���ֵ��Ĭ��Ϊ-1
	/// @return    true=�ɹ���false=Win32����
	fBool Terminate(fInt ExitCode=-1);

	/// @brief ����̷߳���ֵ
	fuInt GetExitCode();
protected:
	/// @brief     ���캯��
	/// @param[in] PauseThread ����Ϊtrue��ʾ��������ͣ�߳�ִ�У���������ִ���߳�
	fcyBaseThread(fBool PauseThread = true);
	~fcyBaseThread();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fcy�ٽ���
/// @note  �ٽ������������ٶ�һ�δ�����м���
////////////////////////////////////////////////////////////////////////////////
class fcyCriticalSection
{
private:
	CRITICAL_SECTION m_Section; ///< @brief �����ٽ���
public:
	/// @brief �����ٽ���
	void Lock();

	/// @brief  ��ͼ�����ٽ���
	/// @return true=�ɹ���false=ʧ��
	fBool TryLock();

	/// @brief �����ٽ���
	/// @note  Lock�Լ�TryLock�ɹ������ʹ�øú�����ע����
	void UnLock();
public:
	fcyCriticalSection();
	~fcyCriticalSection();
};

////////////////////////////////////////////////////////////////////////////////
/// @brief fcy�¼�
/// @note  ͨ���¼��Զ��̲߳�������ͬ��
////////////////////////////////////////////////////////////////////////////////
class fcyEvent
{
private:
	HANDLE m_hEvent; ///< @brief �����¼����
public:
	/// @brief   �����ڲ��¼����
	/// @warning �벻Ҫ�ֶ��رշ��ص��ں˶���
	/// @return  �¼����
	HANDLE GetHandle();

	/// @brief  ����¼�
	/// @return true=�ɹ���false=Win32����
	fBool Set();

	/// @brief  ȡ���¼����
	/// @return true=�ɹ���false=Win32����
	fBool Reset();

	/// @brief  �¼�����
	/// @return true=�ɹ���flase=Win32����
	fBool Pulse();

	/// @brief     �ȴ��¼�
	/// @param[in] TimeLimited �ȴ��¼���-1��ʾ���޵ȴ�
	/// @return    true=�ɹ���flase=��ʱ��Win32����
	fBool Wait(fInt TimeLimited=-1);
public:
	/// @brief ���캯��
	fcyEvent(fBool AutoReset=false, fBool InitalState=false);
	~fcyEvent();
};
/// @}