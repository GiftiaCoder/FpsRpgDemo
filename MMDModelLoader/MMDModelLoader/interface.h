
#pragma once

#include <windows.h>
#include <vector>

#include "Model.h"

#define MAX_SUPPORT_FORMAT_NUM 16
#define MAX_SUFFIX_NAME_LEN 8

extern "C" _declspec(dllexport) void GetSupportFormat(std::vector<char *> &outList);

extern "C" _declspec(dllexport) CModel* CreateObject(int argc, char **argv);

void initModule();

void exitModule();

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
		initModule();
		break;
	case DLL_PROCESS_DETACH:
	case DLL_THREAD_DETACH:
		exitModule();
		break;
	}
	return (TRUE);
}