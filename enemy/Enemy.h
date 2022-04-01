#pragma once
#include"BaseEnemy.h"

class BossEnemy;
class Enemy :public BaseEnemy {
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
	const XMFLOAT3& GetBoundPower() { return boundpower; }
	const bool& GetHit() { return hit; }
	const int& GetBound() { return bound; }
	const bool& GetIsAlive() { return IsAlive; }
	const int& GetDrawExp() { return DrawExp; }
	void SetPlayer(Player* player) { this->player = player; }
	//bool Collision(XMFLOAT3 position, float radius);
	void SetIsAlive(int IsAlive) { this->IsAlive = IsAlive; }
	void SetEnemyCatch(bool EnemyCatch) { this->EnemyCatch = EnemyCatch; }
	void SetBound(int bound) { this->bound = bound; }
	void SetHit(bool hit) { this->hit = hit; }
	void SetDrawExp(int DrawExp) { this->DrawExp = DrawExp; }
	void Setboundpower(XMFLOAT3 boundpower) { this->boundpower = boundpower; }
	void SetLimit(XMFLOAT4 limit) 	{
		this->z_max = limit.x;
		this->z_min = limit.y;
		this->x_max = limit.z;
		this->x_min = limit.w;
	}

	void SetEnemy();
	void DeadEnemy();
	void RandDeadPower();
	void SetBasePos(XMFLOAT3 basePos) { this->basePos = basePos; }
private:
	XMFLOAT3 playerpos{};
	XMFLOAT3 StartPos{};
	XMFLOAT3 EndPos{};
	XMFLOAT3 EndRot{};
	XMFLOAT3 basePos{};

	float rad = 0.4f;

	float radius = 0.0f;
	float speed = 0.0f;
	float savespeed = 0.0f;
	float scale = 0.0f;
	float savesacale = 0.0f;
	float circleX = 0.0f;
	float circleZ = 0.0f;
	float EnemyWeight = 0.0f;
	bool IsAlive = 0;
	int IsTimer = 200;
	bool EnemyCatch = false;
	bool isMove = false;
	bool hit = false;
	int moveCount = 30;
	int dir = 0;
	bool zmove = false;
	bool bound = false;
	bool add = false;
	bool appearance = false;
	bool Exp = false;
	int DrawExp = false;
};

