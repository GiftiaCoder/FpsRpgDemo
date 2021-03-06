/*#include "Model.h"
#include "Exception.h"

void CModel::Load(std::wstring &path) {
	try {
		std::wifstream in(path);
		Load(in);
		in.close();
	}
	catch (stException &exception) {
		if (exception.msg == MSG_FILE_CANT_ACCESS) {
			exception.detail = path;
		}
		throw exception;
	}
}*/


#include <fstream>

#include "Model.h"
#include "Exception.h"

CModel::CModel() {}

CModel::~CModel() {}

void CModel::load(std::string &path) {
	try {
		std::ifstream in(path);
		load(in);
		in.close();
	}
	catch (stException &exception) {
		if (exception.msg == MSG_FILE_CANT_ACCESS) {
			//exception.detail = path;
		}
		throw exception;
	}
}