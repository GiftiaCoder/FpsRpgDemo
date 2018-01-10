#include "AppEntry.h"

#include <iostream>

#include "GLFrame.h"
#include "Camera2D.h"

CAppEntry::CAppEntry() {}

CAppEntry::~CAppEntry() {}

BOOL CAppEntry::InitApplication() {
	FILE *pConsoleFile;
	::AllocConsole();
	freopen_s(&pConsoleFile, "CONOUT$", "w", stdout);
	std::wcout.imbue(std::locale("chs"));

	return CWinApp::InitApplication();
}

BOOL CAppEntry::InitInstance() {
	m_pMainWnd = new CGLFrame(L"FPSDemo");
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return CWinApp::InitInstance();
}

int CAppEntry::Run() {
	return CWinApp::Run();
}

int CAppEntry::ExitInstance() {
	return CWinApp::ExitInstance();
}

CAppEntry theApp;
