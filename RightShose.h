#pragma once
#include "InterBoss.h"
#include "LeftShose.h"
#include "Foot.h"

class RightShose :public InterBoss{
public:
	RightShose();

	void Initialize(bool shadow = true) override;//初期化
	void Finalize() override;//開放
	void Spec() override;//ボスの行動
	void App(int Timer) override;//導入
	void End(int Timer) override;//撃破
	void specialDraw() override;//このシーンのみの描画
	void SetAct(Foot* foot);
	bool HitShose(LeftShose* leftshose);
	void Follow();
	//足元にパーティクル
	void BirthParticle();
private:

	float y = 0.0f;
	//待機モーションのためのやつ
	enum Motion {
		Up,
		Down
	};

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
	int FollowTimer = 0;
	XMFLOAT2 vel{};
};