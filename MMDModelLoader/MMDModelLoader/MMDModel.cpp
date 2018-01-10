#include "MMDModel.h"
#include "Exception.h"
#include <unordered_map>
#include <queue>

//#include <gl\glut.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#pragma comment(lib, "opengl32.lib")

//L"˜O˜S›·ÍÁ.vmd"
//L"A58_SO ¥â¥Ç¥ëÒÀ´æ ¥Ò¥Ã¥×¥¦¥©©`¥¯¢\\_‘«ƒ~ƒNver1.0.vmd"
//std::wstring wstrVmdPath = L"A58_SO ¥â¥Ç¥ëÒÀ´æ ¥Ò¥Ã¥×¥¦¥©©`¥¯¢\\ƒŒƒA@ver1.12.vmd";
std::wstring wstrVmdPath = L"˜O˜S›·ÍÁ.vmd";

CMMDModel::~CMMDModel() {
	if (pPoser) {
		delete pPoser;
	}
	//if (pReactor) {
	//	delete pReactor;
	//}
	if (pTextureIdxList) {
		delete[]pTextureIdxList;
	}
	if (pTriangleNumList) {
		delete[]pTriangleNumList;
	}
	if (pSubTextureIdxList) {
		delete[]pSubTextureIdxList;
	}
	if (pSubTexEnumType) {
		delete[]pSubTexEnumType;
	}
	if (pBaseShiftList) {
		delete[]pBaseShiftList;
	}
}

void CMMDModel::load(std::string &path) {
	loadModel(path);
	loadMotion(std::wstring(wstrVmdPath));
	pPoser = new mmd::Poser(model);

	//pReactor = new mmd::BulletPhysicsReactor;
	//pReactor->AddPoser(*pPoser);
}

void CMMDModel::load(std::istream &in) {
	throw EXCEPTION_INVALID_CALL(NULL_STR);
}

void CMMDModel::render() {
	if (startTime == 0) {
		startTime = clock();
	}
	time_t currTime = clock();
	double delta = (double)(currTime - startTime) / (double)1000;
	delta = delta >= 2.5 ? delta - 2.5 : 0;
	if (delta * 30.0 > (double) motion.GetLength()) {
		startTime = currTime;
	}

	for (int i = 0; i < model.GetBoneNum(); ++ i) {
		const std::wstring &boneName = model.GetBone(i).GetName();
		mmd::Motion::BonePose bonePose = mmd::Motion::BonePose(motion.GetBonePose(boneName, delta));
		pPoser->SetBonePose(boneName, bonePose);
	}

	pPoser->PrePhysicsPosing();
	//pReactor->React(delta);
	pPoser->PostPhysicsPosing();
	pPoser->Deform();

	for (int i = 0; i < pPoser->pose_image.coordinates.size(); ++i) {
 		mmd::Point3D<float> &v = pPoser->pose_image.coordinates[i].p;
		Vector3f &vv = vList[i];
		vv.v[0] = v.x;
		vv.v[1] = v.y;
		vv.v[2] = v.z;

		mmd::Point3D<float> &n = pPoser->pose_image.normals[i].p;
		Vector3f &vn = nList[i];
		vn.v[0] = n.x;
		vn.v[1] = n.y;
		vn.v[2] = n.z;
	}

	for (int i = 0; i < textureNumber; ++i) {
		glBindTexture(GL_TEXTURE_2D, pTextureIdxList[i]);

		int baseShift = pBaseShiftList[i];
		int triangleUpIdx = pTriangleNumList[i] + baseShift;
		for (int j = baseShift; j < triangleUpIdx; ++j) {
			Triangle &triangle = triangleList[j];

			glBegin(GL_POLYGON);
			for (int k = 0; k < 3; ++ k) {
				int idx = triangle.v[k];
				glNormal3fv(nList[idx].v);
				glTexCoord2fv(tList[idx].v);
				glVertex3fv(vList[idx].v);
			}
			glEnd();
		}
	}
}

float getMirroredVal(float val) {
	int t = (int)val;
	if (t % 2) {
		return val;
	}
	else {
		return - val;
	}
}

void CMMDModel::loadModel(std::string &path) {
	mmd::PmxReader(mmd::FileReader(path)).ReadModel(model);

	for (size_t i = 0; i < model.GetVertexNum(); ++i) {
		mmd::Model::Vertex<mmd::ref> &vertex = model.GetVertex(i);

		const mmd::Vector3f &c = vertex.GetCoordinate();
		vList.push_back(c.v);

		const mmd::Vector3f &n = vertex.GetNormal();
		nList.push_back(n.v);

		const mmd::Vector2f &uvCrd = vertex.GetUVCoordinate();
		tList.push_back(Vector2f({ uvCrd.v[0], getMirroredVal(uvCrd.v[1]), }));
	}
	
	std::wcout << L"load model success" << std::endl;

	for (size_t i = 0; i < model.GetTriangleNum(); ++i) {
		const mmd::Vector3D<uint32_t> &triangle = model.GetTriangle(i);
		triangleList.push_back(triangle.v);
	}

	textureNumber = model.GetPartNum();
	std::wcout << L"Texture Num = " << textureNumber << std::endl;
	pTextureIdxList = new GLuint[textureNumber];
	pSubTextureIdxList = new GLuint[textureNumber];
	pTriangleNumList = new GLint[textureNumber];
	pBaseShiftList = new GLint[textureNumber];
	pSubTexEnumType = new mmd::Material::SubTextureTypeEnum[textureNumber];
	for (size_t i = 0; i < textureNumber; ++i) {
		std::wcout << L"Load part " << i << std::endl;
		mmd::Model::Part &part = model.GetPart(i);
		std::wcout << L"Meta : " << part.GetMaterial().GetMetaInfo() << std::endl;
		std::wcout << L"Material Name : " << part.GetMaterial().GetName() << std::endl;
		std::wcout << L"Triangle Num : " << part.GetTriangleNum() << std::endl;
		if (part.GetMaterial().GetTexture() != nullptr) {
			std::wcout << L"load texutre : " << part.GetMaterial().GetTexture()->GetTexturePath() << std::endl;
			pTextureIdxList[i] = loadTexture(part.GetMaterial().GetTexture()->GetTexturePath());
			if (pTextureIdxList[i] == 0) {
				std::wcout << L"load textrue failed !" << std::endl;
			}
		}
		else {
			std::wcout << L"Texture of part [" << i << L"] 0" << std::endl;
			pTextureIdxList[i] = 0;
		}
		
		if (part.GetMaterial().GetSubTexture() != nullptr) {
			std::wcout << L"load sub texutre : " << part.GetMaterial().GetSubTexture()->GetTexturePath() << std::endl;
			pSubTextureIdxList[i] = loadTexture(part.GetMaterial().GetSubTexture()->GetTexturePath());
		}
		else {
			std::wcout << L"SubTexture of part [" << i << L"] 0" << std::endl;
			pSubTextureIdxList[i] = 0;
		}
		pSubTexEnumType[i] = part.GetMaterial().GetSubTextureType();

		pTriangleNumList[i] = part.GetTriangleNum();
		pBaseShiftList[i] = part.GetBaseShift();

		std::wcout << std::endl;
	}

	textureIdxMap.clear();
}

void CMMDModel::loadMotion(std::wstring &path) {
	mmd::VmdReader(mmd::FileReader(path)).ReadMotion(motion);

	for (size_t i = 0; i < model.GetBoneNum(); ++ i) {
		motion.RegisterBone(model.GetBone(i).GetName());
	}

	for (size_t i = 0; i < model.GetMorphNum(); ++ i) {
		motion.RegisterMorph(model.GetMorph(i).GetName());
	}

	std::wcout << L"Motion Length : " << motion.GetLength() << std::endl;
}

GLuint CMMDModel::loadTexture(const std::wstring &path) {
	std::unordered_map<std::wstring, GLuint>::iterator it = textureIdxMap.find(path);
	if (it != textureIdxMap.end()) {
		return it->second;
	}
	GLuint texid = funcLoadTexture(path);
	if (texid) {
		textureIdxMap[path] = texid;
	}
	return texid;
}

LoadTextureFunc CMMDModel::funcLoadTexture = nullptr;

HMODULE CMMDModel::hTextureLoader = (HMODULE) INVALID_HANDLE_VALUE;