#pragma once
#include <DirectXMath.h>
#include"CollisionPrimitive.h"
#include "Object3d.h"
#include"Model.h"
#include"Sprite.h"
#include "Player.h"
#include "Texture.h"
#include "Audio.h"
#include"Rice.h"
#include"ModelManager.h"


#define DIRECTINPUT_VERSION 0x0800

class InterBoss {
protected:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	void SetPlayer(Player* player) { this->player = player; }
	/// ���W�E��]�̎擾
	const XMFLOAT3& GetPosition() { return  enemyobj->GetPosition(); }
	const XMFLOAT3& GetRotation() { return enemyobj->GetRotation(); }

	/// ���W�E��]�̐ݒ�
	void SetPosition(XMFLOAT3 position) { enemyobj->SetPosition(position); }
	void SetRotation(XMFLOAT3 rotation) { enemyobj->SetRotation(rotation); }

	const bool& GetEnemyCatch() { return EnemyCatch; }
	const XMFLOAT3& GetBoundPower() { return boundpower; }
	const bool& GetHit() { return hit; }
	const int& GetBound() { return bound; }
	const bool& GetIsAlive() { return IsAlive; }
	const int& GetDrawExp() { return DrawExp; }
	//bool Collision(XMFLOAT3 position, float radius);
	void SetIsAlive(int IsAlive) { this->IsAlive = IsAlive; }
	void SetEnemyCatch(bool EnemyCatch) { this->EnemyCatch = EnemyCatch; }
	void SetBound(bool bound) { this->bound = bound; }
	void SetHit(bool hit) { this->hit = hit; }
	void Back();
	void SetDrawExp(int DrawExp) { this->DrawExp = DrawExp; }
	void Setboundpower(XMFLOAT3 boundpower) { this->boundpower = boundpower; }
	void SetEnemy();
	void DeadEnemy();
	void RandDeadPower();
	void SetBasePos(XMFLOAT3 basePos) { this->basePos = basePos; }
	void Respawn(float speed);
	void Follow();
	void Reborn();
	bool CollidePos(XMFLOAT3 pos, float radius);
public:
	const float& GetHP() { return BossHP; }
	const bool& GetEffect() { return Effect; }
	void SetHP(float BossHP) { this->BossHP = BossHP; }
	void SetEffect(bool Effect) { this->Effect = Effect; }

/// <summary>
/// ������
/// </summary>
	virtual void Initialize() = 0;
	/// <summary>
	/// �I��
	/// </summary>
	virtual void Finalize() = 0;
	/// <summary>
	/// ���t���[���X�V
	/// </summary>
	void Update();
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	virtual void Spec()=0;//�{�X���L�̏���
	bool collidePlayer();
	bool collideAttackArm();

	void Pause(const int& Timer);
protected:
	const float PI = 3.14f;

	Object3d* enemyobj = nullptr;
	Model* model = nullptr;

	Texture* texture = nullptr;
	Texture* Restexture = nullptr;
	XMFLOAT3 pos = { 0,0,0 };
	XMFLOAT3 oldpos = { 0,0,0 };
	XMFLOAT3 rot = { 0,0,0 };
	XMFLOAT3 boundpower{};
	XMFLOAT3 Deadbound = {};
	XMFLOAT3 enescale{ 0.4f,0.4f,0.4f };
	XMFLOAT3 shosepos;
	Player* player = nullptr;
	XMFLOAT3 playerpos{};

	XMFLOAT3 StartPos{};
	XMFLOAT3 EndPos{};
	XMFLOAT3 EndRot{};
	XMFLOAT3 basePos{};

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
	double posR;
	double Check;
	double Check2;

	float frame = 0;
	int Interval = 0;
	int FlashCount = 0;
	float x_min = -25;
	float x_max = 25;
	float z_min = -20;
	float z_max = 20;
	bool pause = false;
	bool respawn = false;	float Afterrot = 90;//��������
	//
	float BossHP = 40;
	bool BossHit = false;
	bool Effect = false;
	//
	int AttackCount = 0;
	bool already = false;
	//
	bool active = false;//�s���J�n
	int action = 0;//�U���̎��
	int pat = 0;//�p�^�[��
	int aiming = 0;//�G�Ǐ]
	int coolT = 0;//�N�[���^�C��
	int AttackC = 0;//����U��������
	bool finish = false;//�t�B�j�b�V��
	int State = 0;

	float y = 0.0f;
	//�ҋ@���[�V�����̂��߂̂��
	enum Motion {
		Up,
		Down
	};
	int b = 0;
};

