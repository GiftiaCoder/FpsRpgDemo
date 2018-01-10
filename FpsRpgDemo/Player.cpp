#include "Player.h"

void CPlayer::Update(GLdouble time) {
	m_pScene->Update(time);
	SelfUpdate(time);
}

void CPlayer::Render() {
	m_pCamera->UpdateLook();
	m_pScene->Render();
	RenderSelf();
}

void CPlayer::SelfUpdate(GLdouble time) {
	// TODO
}

void CPlayer::RenderSelf() {
	// TODO
}

