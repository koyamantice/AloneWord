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
	bool collideArm();
	bool collidePlayer();
	bool collideAttackArm();
	bool LockOn();
	void Follow();
	void Move();

public:
	const int& GetisAlive() { return IsAlive; }
	const bool& GetEnemyCatch() { return EnemyCatch; }
	const bool& GetHit() { return hit; }
	const int& Getplayerhit() { return playerhit; }
	const XMFLOAT3& GetRebound() { return rebound; }

	void SetPlayer(Player* player) { this->player=player; }
	void SetIsAlive(int IsAlive) { this->IsAlive = IsAlive; }

	void SetEnemyCatch(bool EnemyCatch) {this-> EnemyCatch = EnemyCatch; }

	void SetHit(bool hit) { this->hit = hit; }

private:
	Texture* texture = nullptr;
	XMFLOAT3 playerpos{};
	XMFLOAT3 StartPos{};
	XMFLOAT3 EndPos{};
	XMFLOAT3 EndRot{};
	XMFLOAT3 basePos{};
	XMFLOAT3 distance{};
	XMFLOAT3 rebound{};

	float rad = 0.4f;

	float x_min=-25;
	float x_max=25;
	float z_min=-20;
	float z_max=20;

	float radius = 0.0f;
	float speed = 0.0f;
	float scale = 0.0f;// LaneNumÇ∆àÍèèÇ…ïœÇ¶ÇÈÇ±Ç∆
	float circleX = 0.0f;
	float circleZ = 0.0f;
	float EnemyWeight = 0.0f;
	bool IsAlive = 0;
	int IsTimer = 100;
	bool EnemyCatch = false;
	bool isMove = false;
	bool hit = false;
	int moveCount = 30;
	int dir = 0;
	bool zmove = false;
	int playerhit = 0;
};

