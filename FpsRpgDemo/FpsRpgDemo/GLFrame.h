#pragma once

#include "Model.h"
#include "GLUtil.h"

#include "Camera.h"

DWORD WINAPI FuncPaintProc(LPVOID lpParameter);

class CGLFrame :
	public CFrameWnd
{
public:
	CGLFrame(LPCTSTR wndName);

public:
	DECLARE_MESSAGE_MAP();

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCS);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDestory();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int w, int h);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnWindowPosChanging(WINDOWPOS *pos);
	afx_msg void OnLButtonDown(UINT nFlag, CPoint point);
	afx_msg void OnMouseMove(UINT nFlag, CPoint point);

private:
	PAINTSTRUCT m_stPS;

private:
	void CreateGLEnvironment();
	HGLRC m_hGLRC = (HGLRC)INVALID_HANDLE_VALUE;
	void ReleaseGLEnvironment();

private:
	void GLResize(int w, int h);

private:
	bool m_IsCallSetCursorPos = false;
	bool m_IsLockCursor = true;
	CRect m_ClientRect;
	void LockCursor();
	void LockCursor(bool isLock);

public:
	virtual void DoPaint();

private:
	CCamera *m_pCamera;
	CModel *m_pModel;

private:
	DWORD m_idPaintThread = 0;
	HANDLE m_hPaintThread = INVALID_HANDLE_VALUE;

private:
	enum class EnumMoveFB {
		STAY, FORWARD, BACKWARD, 
	};
	enum class EnumMoveRL {
		STAY, RIGHT, LEFT, 
	};
	EnumMoveFB m_MoveFB = EnumMoveFB::STAY;
	EnumMoveRL m_MoveRL = EnumMoveRL::STAY;

private:
	friend DWORD WINAPI FuncPaintProc(LPVOID lpParameter);
};

