
#include "Camera2D.h"
#include "MathUtil.h"

#define MODIFY_COORDINATE_FB(_dist_, _sig_)				\
{														\
	GLdouble rad = DegToRad(m_FaceH);					\
	m_Loc[EnumCoordinate::X] _sig_##= cos(rad) * dist;	\
	m_Loc[EnumCoordinate::Z] _sig_##= sin(rad) * dist;	\
}														\

#define MODIFY_COORDINATE_RL(_dist_, _sig_)					\
{															\
	GLdouble rad = DegToRad(m_FaceH);						\
	m_Loc[EnumCoordinate::X] _sig_## = - sin(rad) * dist;	\
	m_Loc[EnumCoordinate::Z] _sig_## = cos(rad) * dist;		\
}															\

void CCamera2D::Forward(GLdouble dist) { MODIFY_COORDINATE_FB(dist, +); }

void CCamera2D::Backward(GLdouble dist) { MODIFY_COORDINATE_FB(dist, -); }

void CCamera2D::Rightward(GLdouble dist) { MODIFY_COORDINATE_RL(dist, +); }

void CCamera2D::Leftward(GLdouble dist) { MODIFY_COORDINATE_RL(dist, -); }

#undef MODIFY_COORDINATE_FB
#undef MODIFY_COORDINATE_RL
