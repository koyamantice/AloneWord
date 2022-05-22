#pragma once
#include "InterBoss.h"
#include "Human.h"

class LeftHand :public InterBoss {
public:
	LeftHand();//コンストラクタ

	void Initialize(bool shadow = true) override;//初期化
	void Finalize() override;//開放
	void Spec() override;//ボスの行動
	void App(int Timer) override;//導入
	void End(int Timer) override;//撃破
	void specialDraw() override;//このシーンのみの描画
	void SetAct(Human* human);
private:
	enum state {
		Open,
		Close,
	};

	int stateNumber = 0;

	Model* hand_closemodel = nullptr;
};