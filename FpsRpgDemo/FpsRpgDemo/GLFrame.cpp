#include "GLFrame.h"
#include "Ground.h"

#include "Camera2D.h"
#include "Camera3D.h"

DWORD WINAPI FuncPaintProc(LPVOID lpParameter) {
	CGLFrame *pFrame = (CGLFrame *) lpParameter;
	CCamera *pCamera = pFrame->m_pCamera;
	while (true) {
		Sleep(20);
		switch (pFrame->m_MoveFB) {
		case CGLFrame::EnumMoveFB::FORWARD: pCamera->Forward(0.6); break;
		case CGLFrame::EnumMoveFB::BACKWARD: pCamera->Backward(0.6); break;
		}
		switch (pFrame->m_MoveRL) {
		case CGLFrame::EnumMoveRL::RIGHT: pCamera->Rightward(0.6); break;
		case CGLFrame::EnumMoveRL::LEFT: pCamera->Leftward(0.6); break;
		}
		pFrame->SendMessage(WM_PAINT);
	}
}

CGLFrame::CGLFrame(LPCTSTR wndName) {
	Create(NULL, wndName);
}

BEGIN_MESSAGE_MAP(CGLFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()

typedef CModel* (*CreateObjectFunc)(int argc, char **argv);

int CGLFrame::OnCreate(LPCREATESTRUCT lpCS) {
	int ret = CFrameWnd::OnCreate(lpCS);

	CreateGLEnvironment();
	
	m_pModel = ((CreateObjectFunc)GetProcAddress(LoadLibrary(L"MMDModelLoader"), "CreateObject"))(0, NULL);
	m_pModel->load(std::string("Tda Luka Crazy Ponytail\\Tda Luka Crazy Black PonyTail.pmx"));

	m_pCamera = new CCamera2D;
	m_pCamera->m_Loc[CCamera::EnumCoordinate::X] = -40;
	m_pCamera->m_Loc[CCamera::EnumCoordinate::Y] = 16;
	m_pCamera->m_Loc[CCamera::EnumCoordinate::Z] = 0;

	m_hPaintThread = CreateThread(NULL, 0, FuncPaintProc, this, 0, &m_idPaintThread);

	return ret;
}

void CGLFrame::OnShowWindow(BOOL bShow, UINT nStatus) {
	CFrameWnd::OnShowWindow(bShow, nStatus);
	
	if (bShow) {
		LockCursor();
	}
}

void CGLFrame::OnWindowPosChanging(WINDOWPOS *pos) {
	CFrameWnd::OnWindowPosChanging(pos);
	LockCursor();
}

void CGLFrame::OnDestory() {
	TerminateThread(m_hPaintThread, 0);
	CloseHandle(m_hPaintThread);
	ReleaseGLEnvironment();
	if (m_pCamera) {
		delete m_pCamera;
	}
	if (m_pModel) {
		delete m_pModel;
	}
	CFrameWnd::OnDestroy();
}

void CGLFrame::OnSize(UINT nType, int w, int h){
	CFrameWnd::OnSize(nType, w, h);
	GLResize(w, h);
	LockCursor();
}

void CGLFrame::OnPaint() {
	BeginPaint(&m_stPS);
	wglMakeCurrent(GetDC()->GetSafeHdc(), m_hGLRC);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	DoPaint();

	SwapBuffers(GetDC()->GetSafeHdc());
	glFlush();

	CFrameWnd::OnPaint();
	EndPaint(&m_stPS);
}

void CGLFrame::OnMouseMove(UINT nFlag, CPoint point) {
	if (m_IsLockCursor) {
		if (m_IsCallSetCursorPos) {
			m_IsCallSetCursorPos = false;
		}
		else {
			CPoint &cp = m_ClientRect.CenterPoint();

			m_pCamera->LookDown((point.y - cp.y + m_ClientRect.top) / 5);
			m_pCamera->LookRight((point.x - cp.x + m_ClientRect.left) / 5);

			m_IsCallSetCursorPos = SetCursorPos(cp.x, cp.y);
		}
	}
}

void CGLFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	switch (nChar) {
	case 'W': {m_MoveFB = EnumMoveFB::FORWARD; }; break;
	case 'S': {m_MoveFB = EnumMoveFB::BACKWARD; }; break;
	case 'A': {m_MoveRL = EnumMoveRL::LEFT; }; break;
	case 'D': {m_MoveRL = EnumMoveRL::RIGHT; }; break;
	}
}

void CGLFrame::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) {
	switch (nChar) {
	case 'W': {if (m_MoveFB == EnumMoveFB::FORWARD) m_MoveFB = EnumMoveFB::STAY; }; break;
	case 'S': {if (m_MoveFB == EnumMoveFB::BACKWARD) m_MoveFB = EnumMoveFB::STAY; }; break;
	case 'A': {if (m_MoveRL == EnumMoveRL::LEFT) m_MoveRL = EnumMoveRL::STAY; }; break;
	case 'D': {if (m_MoveRL == EnumMoveRL::RIGHT) m_MoveRL = EnumMoveRL::STAY; }; break;
	case VK_ESCAPE: {LockCursor(false); }; break;
	}
}

void CGLFrame::OnLButtonDown(UINT nFlag, CPoint point) {
	CFrameWnd::OnLButtonDown(nFlag, point);
	LockCursor(true);
}

void CGLFrame::CreateGLEnvironment() {
	m_hGLRC = CGLUtil::CreateRC(GetDC()->GetSafeHdc());
	wglMakeCurrent(GetDC()->GetSafeHdc(), m_hGLRC);

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_FLAT);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
}

void CGLFrame::ReleaseGLEnvironment() {
	if (m_hGLRC != INVALID_HANDLE_VALUE) {
		wglDeleteContext(m_hGLRC);
	}
}

void CGLFrame::GLResize(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	if (w <= h) {
		glOrtho(0.0f, 300.0f, 0.0f, 300.0f * h / w, 1.0f, -1.0f);
	}
	else {
		glOrtho(0.0f, 300.0f * w / h, 0.0f, 300.0f, 1.0f, -1.0f);
	}
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

void CGLFrame::DoPaint() {
	m_pCamera->UpdateLook();
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	m_pModel->render();
	CGround().Render();
}

void CGLFrame::LockCursor() {
	LockCursor(m_IsLockCursor);
}

void CGLFrame::LockCursor(bool isLock) {
	if (m_IsLockCursor = isLock) {
		GetClientRect(&m_ClientRect);
		ClientToScreen(&m_ClientRect);
		m_IsCallSetCursorPos = SetCursorPos(m_ClientRect.CenterPoint().x, m_ClientRect.CenterPoint().y);
		while (ShowCursor(FALSE) >= 0);
	}
	else {
		while (ShowCursor(TRUE) < 0);
	}
}
