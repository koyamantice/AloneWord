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
	bool collidePlayer();
	bool collideAttackArm();
	void Fork();
public:
	const int& GetisAlive() { return IsAlive; }

	const int& GetHP() { return BossHP; }

	void SetPlayer(Player*player) { this->player=player; }

	void SetIsAlive(int IsAlive) { this->IsAlive = IsAlive; }

	void SetHP(int BossHP) { this->BossHP = BossHP; }
private:
	XMFLOAT2 HPPos = { 0,0 };
	Texture* texture;

	Sprite* SpriteBossHP = false;
	float rad = 0.4f;

	float Afterrot = 0;
	int IsAlive = 0;
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
	int pat = 0;
};