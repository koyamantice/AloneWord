#pragma once
#include"BaseEnemy.h"

class BossEnemy;
class Enemy :public BaseEnemy{
public:
	Enemy();

	void Initialize() override;
	void Finalize() override;
	void Update()override;
	void Draw() override;
private:
	bool collidePlayer() override;
	bool collideAttackArm() override;
	bool collideArm();
	bool LockOn();
	void Follow();
	void Move();

public:
	const bool& GetEnemyCatch() { return EnemyCatch; }
	const bool& GetHit() { return hit; }

	void SetPlayer(Player* player) { this->player=player; }
	//bool Collision(XMFLOAT3 position, float radius);
	void SetPlayer(Player* player) { this->player = player; }
	void SetIsAlive(int IsAlive) { this->IsAlive = IsAlive; }
	void SetEnemyCatch(bool EnemyCatch) {this-> EnemyCatch = EnemyCatch; }
	void SetHit(bool hit) { this->hit = hit; }

private:
	XMFLOAT3 playerpos{};
	XMFLOAT3 StartPos{};
	XMFLOAT3 EndPos{};
	XMFLOAT3 EndRot{};
	XMFLOAT3 basePos{};
	float rad = 0.4f;

	float radius = 0.0f;
	float speed = 0.0f;
	float scale = 0.0f;// LaneNum‚Æˆê‚É•Ï‚¦‚é‚±‚Æ
	float circleX = 0.0f;
	float circleZ = 0.0f;
	float EnemyWeight = 0.0f;
	bool IsAlive = 0;
	int IsTimer = 100;
	int Interval = 0;
	bool EnemyCatch = false;
	bool isMove = false;
	bool hit = false;
	int moveCount = 30;
	int dir = 0;
	bool zmove = false;
	
};

