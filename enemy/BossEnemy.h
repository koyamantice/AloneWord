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
	const float& GetHP() { return BossHP; }
	const bool& GetHit() { return BossHit; }
	const bool& GetEffect() { return Effect; }
	void SetHP(float BossHP) { this->BossHP = BossHP; }
	void SetEffect(bool Effect) { this->Effect = Effect; }
private:
	XMFLOAT2 HPPos = { 0,0 };
	Sprite* SpriteBossHP = false;
	float rad = 0.4f;

	float Afterrot = 0;
	int IsTimer = 100;
	int IsMove = 0;
	float BossHP = 50;
	bool BossHit = false;
	bool Effect = false;
	int AttackCount = 0;
	int Standby = 0;
	bool already = false;
	int times = 0;
	bool finish = false;
	int coolT = 0;
	bool bossUp;

	int action = 0;
	bool active = false;
	int pat = 0;
};