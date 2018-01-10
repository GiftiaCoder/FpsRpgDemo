#pragma once

#include "Renderable.h"
#include "Camera.h"
#include "Scene.h"

class CPlayer : public CRenderable
{
public:
	virtual void Update(GLdouble time) override;

	virtual void Render() override;

private:
	void SelfUpdate(GLdouble time);

	void RenderSelf();

private:
	CCamera *m_pCamera = nullptr;
	CScene *m_pScene = nullptr;
};

