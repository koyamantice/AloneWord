#pragma once
#include "InterBoss.h"
#include "Player.h"
#include <array>       // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
class TouchableObject;
class Pastel :public InterBoss {
public:
	Pastel();

	void Initialize(bool shadow = true) override;
	void Finalize() override;
	void Spec() override;
	void App(int Timer) override;
	void End(int Timer) override;
	void specialDraw() override;
	void MillUpdate();
	bool collideAttackArm(Player* player);

private:

	float y = 0.0f;
	//待機モーションのためのやつ
	enum Motion {
		Up,
		Down
	};
	int oldpat = 0;
	//ボスではないオブジェクト用
	Object3d* Millobj = nullptr;
	Model* Millmodel = nullptr;
	Object3d* Mottiobj = nullptr;
	Model* Mottimodel = nullptr;
	XMFLOAT3 Millpos = {0,0,0};
	XMFLOAT3 MottiScale = { 0.0f,0.0f,0.0f };
	array<TouchableObject*, 4> Platformobj;
	Model* Platformmodel = nullptr;
	array<XMFLOAT3, 4> Plapos ={};
	array<bool, 4>SetPlatform = { false };
	array<int, 4> BirthNumber;
	array<Texture*, 4> Plattexture;
};