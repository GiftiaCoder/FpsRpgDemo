#pragma once

#include "GLUtil.h"

class CRenderable
{
public:
	virtual void Update(GLdouble time) = 0;

	virtual void Render() = 0;
};

