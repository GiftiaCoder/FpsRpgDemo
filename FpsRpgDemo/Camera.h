#pragma once

#include "GLUtil.h"

class CCamera
{
public:
	virtual void Forward(GLdouble dist) = 0;
	virtual void Backward(GLdouble dist) = 0;

	virtual void Leftward(GLdouble dist) = 0;
	virtual void Rightward(GLdouble dist) = 0;

	void LookUp(GLdouble deg);
	void LookDown(GLdouble deg);
	
	void LookRight(GLdouble deg);
	void LookLeft(GLdouble deg);

	void TiltRight(GLdouble deg);
	void TiltLeft(GLdouble deg);

public:
	void UpdateLook();

public:
	GLdouble m_Tilt = 0;
	GLdouble m_FaceV = 0;
	GLdouble m_FaceH = 0;
	Vector<GLdouble, 3> m_Loc;

public:
	enum EnumCoordinate {
		X = 0, Y = 1, Z = 2, 
	};
};

