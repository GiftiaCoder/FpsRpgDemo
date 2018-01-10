
#include "interface.h"
#include "ObjModel.h"

void GetSupportFormat(std::vector<char *> &outList) {
	outList.push_back("obj");
}

CModel* CreateObject(int argc, char **argv) {
	CModel *pModel = new CObjModel;
	objList.push_back(pModel);
	return pModel;
}

void ReleaseObject(CModel *pModel) {
	objList.remove(pModel);
	delete pModel;
}

void initModule() {
	CObjModel::funcMap["v"] = &CObjModel::loadV;
	CObjModel::funcMap["vt"] = &CObjModel::loadVt;
	CObjModel::funcMap["vn"] = &CObjModel::loadVn;
	CObjModel::funcMap["f"] = &CObjModel::loadF;
}
