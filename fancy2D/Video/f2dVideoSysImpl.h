////////////////////////////////////////////////////////////////////////////////
/// @file  f2dVideoImpl.h
/// @brief fancy2D��Ƶ����ʵ��
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "f2dVideoImpl.h"

class f2dEngineImpl;

////////////////////////////////////////////////////////////////////////////////
/// @brief fancy2D��Ƶϵͳʵ��
////////////////////////////////////////////////////////////////////////////////
class f2dVideoSysImpl :
	public fcyRefObjImpl<f2dVideoSys>
{
	friend class f2dVideoImpl;
private:
	f2dEngineImpl* m_pEngine;

	f2dRenderDevice* m_pDev;
	std::vector<f2dVideoFilterInfo> m_FliterGUIDList;
private:
	GUID strToGUID(fcStrW pGUIDStr);
	static BOOL createInstanceFromDll(HINSTANCE hDll, REFCLSID rclsid, REFIID riid, LPVOID * ppv);
public:
	f2dRenderDevice* GetRenderDevice();
public: // �ӿ�ʵ��
	fResult LoadFilter(fcStrW pGUIDStr);
	fResult LoadFilterFromAX(fcStrW AXFilePath, fcStrW pGUIDStr);
	fResult CreateVideo(f2dStream* pStream, fuInt Flag, f2dVideo** pOut);
public:
	f2dVideoSysImpl(f2dEngineImpl* pEngine);
	~f2dVideoSysImpl();
};
