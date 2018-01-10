#pragma once

#include <fstream>
#include <iostream>

#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>

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

