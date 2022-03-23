#pragma once
#include"BaseEnemy.h"
#include"Enemy.h"

class BossEnemy :public BaseEnemy {
public:
	BossEnemy();

	void Initialize() override;
	void Finalize() override;
	void Update()override;
	void Draw() override;
private:
	bool collidePlayer() override;
	bool collideAttackArm() override;
	void Fork();
public:
	void SetPlayer(Player* player) { this->player = player; }
	const int& GetHP() { return BossHP; }

	void SetHP(int BossHP) { this->BossHP = BossHP; }
private:
	XMFLOAT2 HPPos = { 0,0 };
	Sprite* SpriteBossHP = false;
	float rad = 0.4f;

	float Afterrot = 0;
	int IsTimer = 100;
	int IsMove = 0;
	int BossHP = 50;
	bool BossHit = false;
	int AttackCount = 0;
	int Standby = 0;
	bool already = false;
	int times = 0;
	bool finish = false;
	int action = 0;
	bool active = false;
	int Interval = 0;
	int FlashCount = 0;
	int pat = 0;
};