#pragma once

#include "Renderable.h"

class CScene : public CRenderable
{
public:
	virtual void Update(GLdouble time) override;

	virtual void Render() override;
};

