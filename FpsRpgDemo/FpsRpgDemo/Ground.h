#pragma once
#include "Renderable.h"
class CGround :
	public CRenderable
{
public:
	virtual void Update(GLdouble time) override;

	virtual void Render() override;
};

