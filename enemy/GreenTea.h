#pragma once
#include "InterBoss.h"
#include "HotWater.h"
#include "Audio.h"
class GreenTea :public InterBoss {
public:
	GreenTea();
	void Initialize(bool shadow = true) override;//初期化
	void Finalize() override;//開放
	void Spec() override;//ボスの行動
	void App(int Timer) override;//導入
	void End(int Timer) override;//撃破
	void specialDraw() override;//このシーンのみの描画
	void AppearDraw();
private:
	HotWater* hotWater[50];
	Sprite* meter[2]{};
	XMFLOAT3 AfterPos{};
	XMFLOAT3 AttackPos = { 0.0f,0.0f,0.0f };
	float degree=0.0f;
	float y = 0.0f;
	int check = false;
	int count =0;
	float vel = 3;
	float Zma=45;
	float Zmi=-45;
	double speedX = 0.0f;
	double speedZ = 0.0f;
	int MoveCount = 0;
	//待機モーションのためのやつ
	enum Motion {
		Up,
		Down
	};

	enum Hit {
		HitNot,
		HitUp,
		HitDown,
		HitRight,
		HitLeft
	};
	bool Attack = false;
};