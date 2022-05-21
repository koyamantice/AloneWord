#pragma once
#include"InterEnemy.h"

class BossEnemy;
class Rice :public InterEnemy {
public:
	Rice();

	void Initialize() override;//初期化
	void Finalize() override;//開放
	void Update()override;//更新
	void Demo(int num=0);//チュートリアル更新
	void Draw() override;//描画
	//ゲッターセッター
	void SetHit(const bool& hit) { this->hit = hit; }
	const bool& GetHit() { return hit; };
	const bool& GetStart() { return start; };
	void SetExP(const XMFLOAT3& exp) { this->exP = exp; }
	
private:
//メンバ関数   
	bool collidePlayer() override;
	bool collideAttackArm() override;
	bool collideArm();
	bool BoundEnemy();
	bool LockOn();
	void Move();
	void Rebound();
//メンバ変数
	//オブジェクトやテクスチャ
	Object3d* Piyopiyo;
	Texture* net[2] = { nullptr };
	//敵のAI関係
	XMFLOAT3 smooth{ pos.x, pos.y,pos.z };
	float speed_y = 3.0f/20.0f;
	const float gravity = speed_y/20.0f;
	float speed_y2 = 1.5f / 20.0f;
	const float gravity2 = speed_y2 / 20.0f;
	bool stun = false;
	bool hit=false;
	bool start = false;
	XMFLOAT3 exP{};
};

