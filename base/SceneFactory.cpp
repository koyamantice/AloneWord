#include "SceneFactory.h"
#include "TitleScene.h"
#include "StageSelect.h"
#include "StartMap.h"
#include "BossScene.h"
#include "SecondBoss.h"
#include "ThirdBoss.h"
#include "FourthBoss.h"
#include "FifthBoss.h"
#include "GameoverScene.h"
#include "ClearScene.h"


BaseScene* SceneFactory::CreateScene(const std::string& sceneName) {
	//éüÇÃÉVÅ[ÉìÇÃçÏê¨
	BaseScene* newScene = nullptr;
	if (sceneName=="TITLE") {
		newScene=new TitleScene();
	}
	else if (sceneName == "StageSelect") {
		newScene = new StageSelect();
	}
	else if (sceneName == "STARTMAP") {
		newScene = new StartMap();
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
	else if (sceneName == "FIFTHBOSS") {
		newScene = new FifthBoss();
	}
	else if (sceneName == "GAMEOVER") {
		newScene = new GameoverScene();
	}
	else if (sceneName == "CLEAR") {
		newScene = new ClearScene();
	}
	return newScene;
}
