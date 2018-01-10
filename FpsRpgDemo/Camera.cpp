#include "Camera.h"
#include "MathUtil.h"

#define MODIFY_DEGREE(_dest_, _delta_, _sig_)	\
{												\
	_dest_ _sig_##= _delta_;					\
	while (_dest_ >= 360.0) {					\
		_dest_ -= 360.0;						\
	}											\
	while (_dest_ < 0.0) {						\
		_dest_ += 360.0;						\
	}											\
}												\


void CCamera::LookUp(GLdouble deg) { MODIFY_DEGREE(m_FaceV, deg, +) }
void CCamera::LookDown(GLdouble deg) { MODIFY_DEGREE(m_FaceV, deg, -) }

void CCamera::LookRight(GLdouble deg){ MODIFY_DEGREE(m_FaceH, deg, +) }
void CCamera::LookLeft(GLdouble deg){ MODIFY_DEGREE(m_FaceH, deg, -) }

void CCamera::TiltRight(GLdouble deg){ MODIFY_DEGREE(m_Tilt, deg, +) }
void CCamera::TiltLeft(GLdouble deg){ MODIFY_DEGREE(m_Tilt, deg, -) }

#undef MODIFY_DEGREE

void CCamera::UpdateLook() {
	
	GLdouble radV = DegToRad(m_FaceV);
	GLdouble cosV = cos(radV);
	GLdouble sinV = sin(radV);

	GLdouble radH = DegToRad(m_FaceH);
	GLdouble cosH = cos(radH);
	GLdouble sinH = sin(radH);

	GLdouble x = m_Loc[EnumCoordinate::X], 
		y = m_Loc[EnumCoordinate::Y], 
		z = m_Loc[EnumCoordinate::Z];

	GLdouble faceX = cosH * cosV, 
		faceY = sinV,
		faceZ = sinH * cosV;

	gluLookAt(x, y, z, 
		faceX + x, faceY + y, faceZ + z, 
		0, 1, 0);
}
