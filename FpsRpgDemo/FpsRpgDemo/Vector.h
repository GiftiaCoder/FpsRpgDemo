#pragma once

#include <afxwin.h>

template<typename T, size_t i>  struct Vector {
	T v[i];

	Vector() {
		T *p = &v[i];
		while (-- p >= v) {
			*p = 0.0;
		}
	}

	T& operator[] (size_t i) {
		return v[i];
	}

	size_t size() {
		return i;
	}
};

