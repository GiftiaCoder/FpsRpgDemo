#pragma once

#include "libmmd\include\mmd\mmd.hxx"
#include "libmmd\include\mmd-bullet\mmd-bullet.hxx"
#include "bullet_lib.h"
#include "Model.h"

#include <string>
#include <unordered_map>
#include <time.h>

typedef GLuint(*LoadTextureFunc)(const std::wstring &);

struct Vector3f {
	float v[3];

	Vector3f(const float (&_val_)[3]) {
		v[0] = _val_[0];
		v[1] = _val_[1];
		v[2] = _val_[2];
	}
};
struct Vector2f {
	float v[2];

	Vector2f(const float(&_val_)[2]) {
		v[0] = _val_[0];
		v[1] = _val_[1];
	}
};
struct Triangle {
	uint32_t v[3];

	Triangle(const uint32_t (&_val_)[3]) {
		v[0] = _val_[0];
		v[1] = _val_[1];
		v[2] = _val_[2];
	}
};

class CMMDModel :
	public CModel
{
public:
	virtual ~CMMDModel();

protected:
	std::vector<Vector3f> vList;
	std::vector<Vector3f> nList;
	std::vector<Vector2f> tList;
	std::vector<Triangle> triangleList;

	int textureNumber = 0;
	GLuint *pTextureIdxList = nullptr;
	GLuint *pSubTextureIdxList = nullptr;
	GLint *pTriangleNumList = nullptr;
	GLint *pBaseShiftList = nullptr;
	mmd::Material::SubTextureTypeEnum *pSubTexEnumType = nullptr;

	mmd::Model model;
	mmd::Motion motion;
	mmd::Poser *pPoser = nullptr;
	mmd::PhysicsReactor *pReactor = nullptr;

	time_t startTime = 0;

	std::unordered_map<std::wstring, GLuint> textureIdxMap;

private:
	virtual void load(std::string &path) override;

	virtual void load(std::istream &in) override;

	virtual void render() override;

private:
	void loadModel(std::string &path);

	void loadMotion(std::wstring &path);

	GLuint loadTexture(const std::wstring &path);

public:
	static HMODULE hTextureLoader;

	static LoadTextureFunc funcLoadTexture;
};

