
#pragma once

#include <windows.h>
#include <vector>
#include <list>

#include "Model.h"

#define MAX_SUPPORT_FORMAT_NUM 16
#define MAX_SUFFIX_NAME_LEN 8

std::list<CModel *> objList;

extern "C" _declspec(dllexport) void GetSupportFormat(std::vector<char *> &outList);

extern "C" _declspec(dllexport) CModel* CreateObject(int argc, char **argv);

extern "C" _declspec(dllexport) void ReleaseObject(CModel *pModel);

void initModule();

void releaseAllObject() {
	for (std::list<CModel *>::iterator it = objList.begin(); it != objList.end(); ++ it) {
		CModel *pModel = *it;
		delete pModel;
	} 
}

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
		releaseAllObject();
		break;
	}
	return (TRUE);
}