#include "SceneFactory.h"
#include "TitleScene.h"
#include "StartMap.h"
#include "BossScene.h"


BaseScene* SceneFactory::CreateScene(const std::string& sceneName) {
	//次のシーンの作成
	BaseScene* newScene = nullptr;
	if (sceneName=="TITLE") {
		newScene=new TitleScene();
	}
	else if (sceneName == "STARTMAP") {
		newScene = new StartMap();
	}
	else if(sceneName == "BOSS"){
		newScene = new BossScene();
	}
	return newScene;
}
