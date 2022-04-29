#include "SceneFactory.h"
#include "TitleScene.h"
#include "StartMap.h"
#include "SecondMap.h"
#include "FourthMap.h"
#include "BossScene.h"
#include "SecondBoss.h"
#include "FourthBoss.h"
#include "GameoverScene.h"
#include "ClearScene.h"


BaseScene* SceneFactory::CreateScene(const std::string& sceneName) {
	//éüÇÃÉVÅ[ÉìÇÃçÏê¨
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
	else if (sceneName == "FOURTHMAP") {
		newScene = new FourthMap();
	}
	else if(sceneName == "BOSS"){
		newScene = new BossScene();
	}
	else if (sceneName == "SECONDBOSS") {
		newScene = new SecondBoss();
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
