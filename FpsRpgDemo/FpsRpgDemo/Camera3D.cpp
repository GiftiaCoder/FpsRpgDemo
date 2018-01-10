#include "Camera3D.h"
#include "MathUtil.h"

#define MODIFY_COORDINATE_FB(_dist_, _sig_)							\
{																	\
	GLdouble radV = DegToRad(m_FaceV);								\
	GLdouble distTimesCosV = cos(radV) * dist;						\
	GLdouble radH = DegToRad(m_FaceH);								\
	m_Loc[EnumCoordinate::Y] _sig_##= sin(radV) * dist;				\
	m_Loc[EnumCoordinate::X] _sig_## = cos(radH) * distTimesCosV;	\
	m_Loc[EnumCoordinate::Z] _sig_## = sin(radH) * distTimesCosV;	\
}																	\

#define MODIFY_COORDINATE_RL(_dist_, _sig_)							\
{																	\
	GLdouble radV = DegToRad(m_FaceV);								\
	GLdouble distTimesCosV = cos(radV) * dist;						\
	GLdouble radH = DegToRad(m_FaceH);								\
	m_Loc[EnumCoordinate::Y] _sig_## = sin(radV) * dist;			\
	m_Loc[EnumCoordinate::X] _sig_## = - sin(radH) * distTimesCosV;	\
	m_Loc[EnumCoordinate::Z] _sig_## = cos(radH) * distTimesCosV;	\
}

void CCamera3D::Forward(GLdouble dist) { MODIFY_COORDINATE_FB(dist, +); }

void CCamera3D::Backward(GLdouble dist) { MODIFY_COORDINATE_FB(dist, -); }

void CCamera3D::Rightward(GLdouble dist) { MODIFY_COORDINATE_RL(dist, +); }

void CCamera3D::Leftward(GLdouble dist) { MODIFY_COORDINATE_RL(dist, -); }

#undef MODIFY_COORDINATE_FB
#undef MODIFY_COORDINATE_RL


