#pragma once

/*#include "GLUtil.h"

#include <string>
#include <iostream>

class CModel
{
public:
	virtual void Load(std::wstring &path);
	virtual void Load(std::wistream &in) = 0;

	virtual void SetMotion(GLuint motionId, GLdouble time) = 0;

	virtual void Render() = 0;
};

*/

#pragma once

#include <iostream>

class CModel
{
public:
	CModel();

	virtual ~CModel();

public:
	virtual void load(std::string &path);

	virtual void load(std::istream &in) = 0;

	virtual void render() = 0;
};

