////////////////////////////////////////////////////////////////////////////////
/// @file  f2dInputSysImpl.h
/// @brief fancy2D����ϵͳʵ��
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "f2dInputSysAPI.h"

#include "../f2dInputSys.h"

#include <vector>

class f2dEngineImpl;

////////////////////////////////////////////////////////////////////////////////
/// @brief ����ϵͳʵ��
////////////////////////////////////////////////////////////////////////////////
class f2dInputSysImpl :
	public fcyRefObjImpl<f2dInputSys>
{
private:
	f2dEngineImpl* m_pEngine;

	f2dInputSysAPI m_API;

	IDirectInput8* m_pDInput;
	HWND m_hWinHandle;
	std::vector<DIDEVICEINSTANCEW> m_MouseList;    // ����б�
	std::vector<DIDEVICEINSTANCEW> m_KeyboardList; // �����б�
	std::vector<DIDEVICEINSTANCEW> m_GameCtrlList; // �������б�

	std::vector<f2dInputDevice*> m_pObjList;       // �豸�б�
private:
	static BOOL PASCAL enumMouse(LPCDIDEVICEINSTANCE pInfo, void* pThis);    // ö�����
	static BOOL PASCAL enumKeyboard(LPCDIDEVICEINSTANCE pInfo, void* pThis); // ö�ټ���
	static BOOL PASCAL enumGameCtrl(LPCDIDEVICEINSTANCE pInfo, void* pThis); // ö����Ϸ�ֱ�
private:
	void enumDevice();  // ö�������豸
public:  // �ڲ�����
	f2dEngineImpl* GetEngine()
	{
		return m_pEngine;
	}

	IDirectInput8* GetHandle()
	{
		return m_pDInput;
	}

	void RegisterDevice(f2dInputDevice* pDev)
	{
		m_pObjList.push_back(pDev);
	}
	void UnregisterDevice(f2dInputDevice* pDev)
	{
		std::vector<f2dInputDevice*>::iterator i = m_pObjList.begin();
		while(i != m_pObjList.end())
		{
			if(*i == pDev)
			{
				m_pObjList.erase(i);
				break;
			}
			else
				++i;
		}
	}
	void Update()  // ���������豸״̬
	{
		std::vector<f2dInputDevice*>::iterator i = m_pObjList.begin();
		while(i != m_pObjList.end())
		{
			(*i)->UpdateState();

			++i;
		}
	}
public:  // �ӿ�ʵ��
	fuInt GetDeviceCount(F2DINPUTDEVTYPE Type);
	fcStrW GetDeviceName(F2DINPUTDEVTYPE Type, fuInt Index);
	fcStrW GetDeviceProductName(F2DINPUTDEVTYPE Type, fuInt Index);
	
	fResult CreateMouse(fInt DevIndex, fBool bGlobalFocus, f2dInputMouse** pOut);
	fResult CreateKeyboard(fInt DevIndex, fBool bGlobalFocus, f2dInputKeyboard** pOut);
	fResult CreateDefaultKeyboard(fInt DevIndex, fBool bGlobalFocus, f2dInputKeyboard** pOut);
	fResult CreateJoystick(fInt DevIndex, fBool bGlobalFocus, f2dInputJoystick** pOut);
public:
	f2dInputSysImpl(f2dEngineImpl* pEngine);
protected:
	~f2dInputSysImpl();
};
