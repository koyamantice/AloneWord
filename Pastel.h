#pragma once
#include "InterBoss.h"
#include "Player.h"
#include <array>       // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
class TouchableObject;
class Pastel :public InterBoss {
public:
	Pastel();

	void Initialize(bool shadow = true) override;//初期化
	void Finalize() override;//開放
	void Spec() override;//ボスの行動
	void App(int Timer) override;//導入
	void Roll(int Timer) override;//導入
	void End(int Timer) override;//撃破
	void specialDraw() override;//このシーンのみの描画
	void MillUpdate();
	bool collideAttackArm(Player* player);
	//足元にパーティクル
	void BirthParticle();
private:

	float y = 0.0f;
	//待機モーションのためのやつ
	enum Motion {
		Up,
		Down
	};
	int oldpat = 0;
	//ボスではないオブジェクト用
	TouchableObject* Millobj = nullptr;
	Model* Millmodel = nullptr;
	XMFLOAT3 Millpos = {0,0,0};
	array<TouchableObject*, 4> Platformobj;
	array<Texture*, 4>attensiontexture;
	Model* Platformmodel = nullptr;
	array<XMFLOAT3, 4> Plapos ={};
	array<bool, 4>SetPlatform = { false };
	array<int, 4> BirthNumber;
	array<Texture*, 4> Plattexture;
	int FlashTimer = 0;
	int FlashCount = 0;
	int SETimer = 0;
};