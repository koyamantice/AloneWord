#pragma once
#include"Sprite.h"
#include"Player.h"
#include"Rice.h"
#include"InterBoss.h"

class UI {
public:
	UI(Player* player = nullptr, InterBoss* boss = nullptr, InterBoss* boss2 = nullptr);
	void Update();
	void Finalize();
	const void Draw();

	void SetIsInvisible(const bool isInvisible) { this->isInvisible = isInvisible; }
	void SetUp(const bool& Up) { this->Up = Up; }
	void EaseScale();
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
private:
	Player* player = nullptr;
	InterBoss* boss = nullptr;
	InterBoss* boss2 = nullptr;
	Sprite* BossHp[3]{};//敵のHP
	Sprite* BossHp2[3]{};//敵のHP
	Sprite* PlaHp[3]{};//プレイヤーのHP
	enum {
		max,
		damage,
		now,
	};
	Sprite* HpGauge = nullptr;
	Sprite* Mark[3]{};
	enum  {
		energy,
		pinch,
		weak
	};
	Sprite* Life = nullptr;
	//敵がどの位置にいるか
	Sprite* Arrow = nullptr;
	Sprite* Arrow2 = nullptr;
	Sprite* Vignette = nullptr;
	//数
	Sprite* number[2][10]{};
	Sprite* bairitu = nullptr;
	Sprite* SpinGauge = nullptr;
	Sprite* SpinBar[3]{};
	//スプライトの位置
	XMFLOAT2 bossPos[2]{};
	XMFLOAT2 bossPos2[2]{};
	XMFLOAT2 plaPos[2]{};
	XMFLOAT2 ArrowPos{};
	XMFLOAT2 ArrowPos2{};
	XMFLOAT2 AfterPos[2]{};
	XMFLOAT2 AfterPos2[2]{};
	XMFLOAT2 AfterSpin[3]{};
	XMFLOAT2 SpinPos[2]{};
	XMFLOAT2 SpinSize[3]{};
	//敵の位置のUIのいちを求めるための変数
	const float PI = 3.145265f;
	std::vector<int> power;
	float strong = 20.0f;
	XMFLOAT2 pos{ (float)WinApp::window_width - 140 ,21 + 96 };
	XMFLOAT2 pos2{ (float)WinApp::window_width - 225 ,7 + 80 };
	float speed = 0;
	bool Up = false;
	float vel = 2.0f;
	float frame = 0.0f;
	float scale = 50;
	double a;
	double b;
	XMFLOAT2 basePos = { 1280 / 2,720 / 2 };
	XMFLOAT2 circle = { 640.0f,360.0f };
	XMFLOAT2 circle2 = { 640.0f,360.0f };
	//XMFLOAT3 pos{};
	double posR;
	float Check;
	float Check2;
	int invisible[2]{};
	float convert;
	int nowBar = 0;
	bool isInvisible=false;
private:
	void SeachBoss();
	void SeachBoss2();
};