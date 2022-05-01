#include "SceneFactory.h"
#include "TitleScene.h"
#include "StartMap.h"
#include "SecondMap.h"
#include "ThirdMap.h"
#include "FourthMap.h"
#include "BossScene.h"
#include "SecondBoss.h"
#include "ThirdBoss.h"
#include "FourthBoss.h"
#include "GameoverScene.h"
#include "ClearScene.h"


BaseScene* SceneFactory::CreateScene(const std::string& sceneName) {
	//���̃V�[���̍쐬
	BaseScene* newScene = nullptr;
	if (sceneName=="TITLE") {
		newScene=new TitleScene();
	}
	else if (sceneName == "STARTMAP") {
		newScene = new StartMap();
	}
	else if (sceneName == "SECONDMAP") {
		newScene = new SecondMap();
	}
	else if (sceneName == "THIRDMAP") {
		//newScene = new ThirdMap();
	}
	else if (sceneName == "FOURTHMAP") {
		newScene = new FourthMap();
	}
	else if(sceneName == "BOSS"){
		newScene = new BossScene();
	}
	else if (sceneName == "SECONDBOSS") {
		newScene = new SecondBoss();
	}
	else if (sceneName == "THIRDBOSS") {
		newScene = new ThirdBoss();
	}
	else if (sceneName == "FOURTHBOSS") {
		newScene = new FourthBoss();
	}
	else if (sceneName == "GAMEOVER") {
		newScene = new GameoverScene();
	}
	else if (sceneName == "CLEAR") {
		newScene = new ClearScene();
	}
	return newScene;
}
