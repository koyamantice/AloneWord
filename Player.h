#pragma once
#include"Object3d.h"
#include"Model.h"
#include <DirectXMath.h>
#include <Input.h>
#include"CollisionPrimitive.h"
#include "Sprite.h"
class Player {
public:
	Player();

	void Initialize();
	void Update();
	void Draw();
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	/// <summary>
/// ���W�̎擾
/// </summary>
/// <returns>���W</returns>
	const XMFLOAT3& GetPosition() { return  object3d->GetPosition(); }

	const XMFLOAT3& GetRotation() { return object3d->GetRotation(); }

	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	void SetPosition(XMFLOAT3 position) { object3d->SetPosition(position); }

	void SetRotation(XMFLOAT3 rotation) { object3d->SetRotation(rotation); }

private:
	Object3d* Armobj;
	Object3d* object3d;
	Model* model;
	Model* Armmodel;
	XMFLOAT3 pos = { 0,0,0 };
	XMFLOAT3 Armpos = { 0,0,0 };
	Sprite* Gauge = nullptr;

	float PlayerSpeed = 0.3f;
	//���W��߂�
	bool undoPos = false;

	float rad = 0.4f;
	const float PI = 3.14f;
	//�r�̕ϐ�
	float radius = 0.0f;
	float speed = 0.0f;
	float scale = 10.0f;
	float initscale = 0.0f;
	float initspeed = 0.0f;
	float initrotation = 0.0f;
	float circleX = 0.0f;
	float circleZ = 0.0f;
	float Armradius = 0.0f;
	float ArmSpeed = 90.0f;
	float Armscale = 1.0f;
	float ArmCircleX = 0.0f;
	float ArmCircleZ = 0.0f;
	//���낢��ȃt���O
	int ArmMoveNumber = 0;
	bool AttackFlag = false;
	int AttackMoveNumber = 0;
	//�C�[�W���O�̂��߂̂��
	float frame = 0.0f;
	float frameMax = 27.0f;
	float frame2 = 0.0f;
	float frameMax2 = 80.0f;
	float frame3 = 0.0f;
	float frameMax3 = 80.0f;
	//�c���֘A

	XMFLOAT3 angle = { 0,0,0 };
public:
	Sphere collider;

};


