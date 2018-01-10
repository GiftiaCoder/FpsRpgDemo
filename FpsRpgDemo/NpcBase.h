#pragma once

#include "Renderable.h"

class CNpcBase : public CRenderable
{
public:
	virtual void Update(GLdouble time) override;

	virtual void Render() override;
};

