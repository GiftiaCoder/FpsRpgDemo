#pragma once

#include <math.h>

#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679

template<typename T> inline T DegToRad(T v) {
	const T tmp = PI / 180.0;
	return v * tmp;
}

template<typename T> inline T RagToDeg(T v) {
	const T tmp = 180.0 / PI;
	return v * tmp;
}
