#pragma once
#include "Camera.h"
class CCamera3D :
	public CCamera
{
public:
	virtual void Forward(GLdouble dist) override;
	virtual void Backward(GLdouble dist) override;

	virtual void Leftward(GLdouble dist) override;
	virtual void Rightward(GLdouble dist) override;
};

