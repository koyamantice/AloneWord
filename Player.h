#pragma once
#include"Object3d.h"
#include"Model.h"
#include <DirectXMath.h>
#include <Input.h>
#include"CollisionPrimitive.h"
#include "Sprite.h"

class Enemy;
class Player {
public:
	Player();

	void Initialize();
	void Update();
	void Draw();
private:
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	/// <summary>
/// 座標の取得
/// </summary>
/// <returns>座標</returns>
	const XMFLOAT3& GetPosition() { return  object3d->GetPosition(); }

	const XMFLOAT3& GetRotation() { return object3d->GetRotation(); }

	const XMFLOAT3& GetArmPosition() { return Armpos; }

	const XMFLOAT3& GetArmRotation() { return ArmRot; }

	const int& GetHp() { return HP; }

	const int& GetArmMoveNumber() { return ArmMoveNumber; }

	const bool& GetAttackFlag() { return AttackFlag; }

	const float& GetArmWeight() { return ArmWeight; }

	const float& GetArmScale() { return Armscale; }

	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(XMFLOAT3 position) { object3d->SetPosition(position); }

	void SetRotation(XMFLOAT3 rotation) { object3d->SetRotation(rotation); }

	void SetArmPosition(XMFLOAT3 Armpos) { this->Armpos = Armpos; }

	void SetArmRotation(XMFLOAT3 ArmRot) { this->ArmRot = ArmRot; }

	void SetHp(int hp) { this->HP = hp; }

	void SetArmMoveNumber(int ArmMoveNumber) { this->ArmMoveNumber = ArmMoveNumber; }

	void SetAttackFlag(bool AttackFlag) { this->AttackFlag = AttackFlag; }

	void SetArmWeight(float ArmWeight) { this->ArmWeight = ArmWeight; }

	void SetArmScale(float Armscale) { this->Armscale = Armscale; }

	void ResetWeight(Enemy* enemy);

	void Rebound(Enemy* enemy);
private:
	Object3d* Armobj;
	Object3d* object3d;
	Model* model;
	Model* Armmodel;
	XMFLOAT2 PlayerHP{};
	XMFLOAT3 pos = { 0,0,-10 };
	XMFLOAT3 Armpos = { 0,0,0 };
	XMFLOAT3 ArmRot = { 0,0,0 };
	Sprite* SpritePlayerHP = nullptr;

	float PlayerSpeed = 0.3f;
	//座標を戻す
	bool undoPos = false;
	float AfterRot = 0.0f;
	float rad = 0.4f;
	const float PI = 3.14f;
	//腕の変数
	float radius = 0.0f;
	float speed = 0.0f;
	float scale = 10.0f;
	float initscale = 0.0f;
	float scaleVel = 3.0f;
	float initspeed = 0.0f;
	float initrotation = 0.0f;
	float circleX = 0.0f;
	float circleZ = 0.0f;
	float Armradius = 0.0f;
	float ArmSpeed = 90.0f;
	float Armscale = 1.0f;
	float ArmCircleX = 0.0f;
	float ArmCircleZ = 0.0f;
	float ArmWeight = 0.0f;
	float TargetSpeed = 0.0f;
	//いろいろなフラグ
	int ArmMoveNumber = 0;
	bool AttackFlag = false;
	int AttackMoveNumber = 0;
	//イージングのためのやつ
	float frame = 0.0f;
	float frameMax = 27.0f;
	float frame2 = 0.0f;
	float frameMax2 = 80.0f;
	float frame3 = 0.0f;
	float frameMax3 = 80.0f;
	//HP
	int HP = 10;
	float StickrotX = 0;
	float StickrotY = 0;
	XMFLOAT3 angle = { 0,0,0 };
public:
	Sphere collider;

};


