#include "E2DLogSystem.hpp"
#include <Windows.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
	using namespace Eyes2D;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		EYESDEBUG(L"Eyes2D.dll process attach.");
		break;
	case DLL_PROCESS_DETACH:
		EYESDEBUG(L"Eyes2D.dll process detach.");
		break;
	case DLL_THREAD_ATTACH:
		EYESDEBUG(L"Eyes2D.dll thread attach.");
		break;
	case DLL_THREAD_DETACH:
		EYESDEBUG(L"Eyes2D.dll thread detach.");
		break;
	}
	return TRUE;
}
