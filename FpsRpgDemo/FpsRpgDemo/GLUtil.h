#pragma once

#include <afxwin.h>

#include <GL\GL.h>
#include <GL\GLU.h>

#include "Vector.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

class CGLUtil
{
public:
	static HGLRC CreateRC(HDC hDC);

private:
	static PIXELFORMATDESCRIPTOR s_stPixelFormatDescriptor;
};
