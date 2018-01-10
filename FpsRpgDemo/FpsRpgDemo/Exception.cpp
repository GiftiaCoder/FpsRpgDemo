
#include "Exception.h"

std::wostream& operator << (std::wostream &out, stException &exception) {
	char buff[4096];
	sprintf_s(buff,
		"Exception:%s\n\tFile:%s\n\tFunc:%s\n\tLine:%d\n\tDTAL:%s",
		exception.msg,
		exception.file,
		exception.function,
		exception.line,
		exception.detail.c_str());
	return out << buff;
}