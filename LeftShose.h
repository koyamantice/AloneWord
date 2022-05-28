#pragma once
#include "InterBoss.h"
#include "Foot.h"

class LeftShose :public InterBoss {
public:
	LeftShose();//コンストラクタ

	void Initialize(bool shadow = true) override;//初期化
	void Finalize() override;//開放
	void Spec() override;//ボスの行動
	void App(int Timer) override;//導入
	void Roll(int Timer) override;//導入
	void End(int Timer) override;//撃破
	void specialDraw() override;//このシーンのみの描画
	void SetAct(Foot* foot);
	void Follow();
	//足元にパーティクル
	void BirthParticle();
public:
	//追従のためのやつ
	int FollowTimer = 0;
	XMFLOAT2 vel{};
	enum State {
		Down,
		Up,
	};
	int StateNumber = 0;
};