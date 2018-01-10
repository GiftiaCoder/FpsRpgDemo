#pragma once

#include "MMDModel.h"
#include "interface.h"

void GetSupportFormat(std::vector<char *> &outList) {
	outList.push_back("pmx");
}

CModel* CreateObject(int argc, char **argv) {
	return new CMMDModel;
}

void initModule() {
	if ((CMMDModel::hTextureLoader = LoadLibrary(TEXT("TextureLoader"))) == INVALID_HANDLE_VALUE) {
		::MessageBoxA(NULL, "cannot load lib", "error", NULL);
		return;
	}
	if ((CMMDModel::funcLoadTexture = (LoadTextureFunc)GetProcAddress(CMMDModel::hTextureLoader, "LoadTextureW")) == nullptr) {
		::MessageBoxA(NULL, "cannot get func", "error", NULL);
		return;
	}
}

void exitModule() {
	FreeLibrary(CMMDModel::hTextureLoader);
	CMMDModel::funcLoadTexture = nullptr;
}