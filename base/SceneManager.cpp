#include "SceneManager.h"
#include<cassert>
//SceneManager::~SceneManager() {
//	//最後のシーンの終了と開放
//	scene_->Finalize();
//	delete scene_;
//}

SceneManager* SceneManager::GetInstance() {
	static SceneManager instance;
	return &instance;
}

void SceneManager::Update() {
	//シーン切り替え
	if (nextScene_) {
		//旧シーンの終了
		if (scene_) {
			scene_->Finalize();
			delete scene_;
		}
		scene_ = nextScene_;
		nextScene_ = nullptr;
		scene_->Initialize();
	}
	scene_->Update();
}

void SceneManager::Draw() {
	scene_->Draw();
}

void SceneManager::ChangeScene(const std::string& sceneName) {
	assert(sceneFactory_);
	assert(nextScene_ == nullptr);
	//次のシーン生成
	nextScene_=sceneFactory_->CreateScene(sceneName);
}
