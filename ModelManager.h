#pragma once
#include <string>
#include "Model.h"
#include <map>

class ModelManager final {
private:
	ModelManager() = default;
	~ModelManager() = default;
	ModelManager(const ModelManager& r) = default;
	ModelManager& operator= (const ModelManager& r) = default;

public:

	enum ModelName {
		Player,
		Arm,
		EHub,
		Enemy,
		Fork,
	};

public:
	static ModelManager* GetIns();		//取得用

	void Initialize();
	void LoadModel(const ModelName modelName, std::string fileName);
	Model* GetModel(ModelName modelName) { return model[modelName]; }

private:
	static std::map<ModelName, Model*> model;	//モデル格納マップ

};