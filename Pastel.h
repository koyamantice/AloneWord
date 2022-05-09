#pragma once
#include "InterBoss.h"
#include "Player.h"
#include <array>       // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
class TouchableObject;
class Pastel :public InterBoss {
public:
	Pastel();

	void Initialize() override;
	void Finalize() override;
	void Spec() override;
	void specialDraw() override;
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
	XMFLOAT3 Millpos = {0,0,0};
	array<TouchableObject*, 4> Platformobj;
	Model* Platformmodel = nullptr;
	array<XMFLOAT3, 4> Plapos ={};
	array<bool, 4>SetPlatform = { false };
	array<int, 4> BirthNumber;
	array<Texture*, 4> Plattexture;
};