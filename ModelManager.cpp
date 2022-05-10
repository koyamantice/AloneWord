#include"ModelManager.h"
#include "FbxLoader.h"

std::map<ModelManager::ModelName, Model*> ModelManager::model;
std::map<ModelManager::FBXName, FBXModel*>  ModelManager::fbxModel;

ModelManager* ModelManager::GetIns() {
	static ModelManager instans;
	return &instans;
}

void ModelManager::Initialize() {
	LoadModel(Player, "Motti");
	LoadModel(Demo, "chr_knight");
	LoadModel(Arm, "Arm");
	LoadModel(EHub, "EHub");
	LoadModel(Enemy, "Enemy");
	LoadModel(Fork, "Fork");
	LoadModel(Water,"Water");
	LoadModel(LeftShoes,"LeftShoes");
	LoadModel(RightShoes,"RightShoes");
	LoadModel(Pastel, "Pestle");
	LoadModel(Platform, "Platform");
	LoadFBXModel(MottiMove, "Motti_move");
	LoadFBXModel(Arm_noCatch, "Arm_noCatch");
	LoadFBXModel(Arm_oneMore, "Arm_oneMore");
	LoadFBXModel(Motti_haveF, "Motti_haveF");
}

void ModelManager::LoadModel(const ModelName modelName, std::string fileName) {
	model[modelName] = new Model();
	model[modelName] = Model::CreateFromOBJ(fileName);
}
void ModelManager::LoadFBXModel(const FBXName modelName, std::string fileName) {
	fbxModel[modelName] = new FBXModel();
	fbxModel[modelName] = FbxLoader::GetInstance()->LoadModelFromFile(fileName);
}

