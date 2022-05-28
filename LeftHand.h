#pragma once
#include "InterBoss.h"
#include "Human.h"
#include <array>   
using namespace std;         //  名前空間指定
class LeftHand :public InterBoss {
public:
	LeftHand();//コンストラクタ

	void Initialize(bool shadow = true) override;//初期化
	void Finalize() override;//開放
	void Spec() override;//ボスの行動
	void App(int Timer) override;//導入
	void Roll(int Timer) override;//導入
	void End(int Timer) override;//撃破
	void specialDraw() override;//このシーンのみの描画
	void SetAct(Human* human);
	bool collideMottiPlayer(Player* player);
private:

	enum Hit {
		HitNot,
		HitUp,
		HitDown,
		HitRight,
		HitLeft
	};
	enum state {
		Open,
		Close,
	};
	int stateNumber = 0;
	Model* hand_closemodel = nullptr;
	double speedX = 0.0f;
	double speedZ = 0.0f;
	int MoveCount = 0;
	bool Attack = false;

};