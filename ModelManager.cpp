#include"ModelManager.h"
#include "FbxLoader.h"

std::map<ModelManager::ModelName, Model*> ModelManager::model;

ModelManager* ModelManager::GetIns() {
	static ModelManager instans;
	return &instans;
}

void ModelManager::Initialize() {
	LoadModel(Player, "Motti");
	LoadModel(Arm, "Arm");
	LoadModel(EHub, "EHub");
	LoadModel(Enemy, "Enemy");
	LoadModel(Fork, "Fork");



}

void ModelManager::LoadModel(const ModelName modelName, std::string fileName) {
	model[modelName] = new Model();
	model[modelName] = Model::CreateFromOBJ(fileName);

}
