#pragma once
#include "InterBoss.h"
#include "Human.h"
#include <array>   
using namespace std;         //  名前空間指定
class RightHand :public InterBoss {
public:
	RightHand();

	void Initialize(bool shadow = true) override;//初期化
	void Finalize() override;//開放
	void Spec() override;//ボスの行動
	void App(int Timer) override;//導入
	void End(int Timer) override;//撃破
	void specialDraw() override;//このシーンのみの描画
	void SetAct(Human* human);
	bool collideMottiPlayer(Player* player);
private:
	bool Attack = false;

	enum Hit {
		HitNot,
		HitUp,
		HitDown,
		HitRight,
		HitLeft
	};
	double speedX = 0.0f;
	double speedZ = 0.0f;
	int MoveCount = 0;
	bool LeftAct = false;

	enum state {
		Open,
		Close,
	};

	int stateNumber = 0;
	Object3d* hand_closeobj = nullptr;
	Model* hand_closemodel = nullptr;
	int count = 0;
};