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
	LoadModel(Kyusu,"Teapot");
	LoadModel(LeftShoes,"LeftShoes");
	LoadModel(RightShoes,"RightShoes");
	LoadModel(Pastel, "Pestle");
	LoadModel(Platform, "Platform");
	LoadModel(Piyopiyo, "Piyopiyo");
	LoadFBXModel(MottiMove, "Motti_moveF");
	LoadFBXModel(MottiPower, "Motti_Move");
}

void ModelManager::LoadModel(const ModelName modelName, std::string fileName) {
	model[modelName] = new Model();
	model[modelName] = Model::CreateFromOBJ(fileName);
}
void ModelManager::LoadFBXModel(const FBXName modelName, std::string fileName) {
	fbxModel[modelName] = new FBXModel();
	fbxModel[modelName] = FbxLoader::GetInstance()->LoadModelFromFile(fileName);
}

