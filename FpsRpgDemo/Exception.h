#pragma once

#include <iostream>
#include <fstream>
#include <string>

struct stException {
	wchar_t *msg;
	wchar_t *file;
	wchar_t *function;
	int line;
	std::wstring detail;
};

std::wostream& operator << (std::wostream &out, stException &exception);

#define CREATE_EXCEPTION(_msg_, _dtal_)	\
	stException{						\
		_msg_,							\
		__FILEW__,						\
		__FUNCTIONW__,					\
		__LINE__,						\
		_dtal_							\
	}									\


#define NULL_STR L"(NULL)"

#define MSG_FILE_CANT_ACCESS L"File Not Exist !"
#define MSG_INVALID_CALL L"Invalid Call !"

#define EXCEPTION_FILE_CANT_ACCESS(_dtal_) CREATE_EXCEPTION(MSG_FILE_CANT_ACCESS, _dtal_)
#define EXCEPTION_INVALID_CALL(_dtal_) CREATE_EXCEPTION(MSG_INVALID_CALL, _dtal_)

