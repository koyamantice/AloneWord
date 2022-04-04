#pragma once
#include"Object3d.h"
#include"Model.h"
#include <DirectXMath.h>
#include <Input.h>
#include"CollisionPrimitive.h"
#include "Sprite.h"
#include "Texture.h"

class Enemy;
class Player : public Object3d {
public:
	Player();

	bool Initialize() override;
	//void Finalize();
	void Update() override;
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

	const int& GetInterval() { return Interval; }

	const int& GetFlashCount() { return FlashCount; }

	const int& GetArmMoveNumber() { return ArmMoveNumber; }

	const bool& GetAttackFlag() { return AttackFlag; }

	const bool& GetDamageFlag() { return DamageFlag; }

	const float& GetArmWeight() { return ArmWeight; }

	const float& GetArmScale() { return Armscale; }

	const float& GetArmSpeed() { return ArmSpeed; }

	const float& GetPower() { return power; }

	const int& GetLv() { return Lv; }

	const float& GetExp() { return Exp; }

	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(XMFLOAT3 position) { object3d->SetPosition(position); }

	void SetRotation(XMFLOAT3 rotation) { object3d->SetRotation(rotation); }

	void SetArmPosition(XMFLOAT3 Armpos) { this->Armpos = Armpos; }

	void SetArmRotation(XMFLOAT3 ArmRot) { this->ArmRot = ArmRot; }

	void SetHp(int hp) { this->HP = hp; }

	void SetLv(int Lv) { this->Lv = Lv; }

	void SetExp(float Exp) { this->Exp = Exp; }
	
	void SetInterval(int Interval) { this->Interval = Interval; }

	void SetFlash(int Flash) { this->FlashCount = FlashCount; }

	void SetArmMoveNumber(int ArmMoveNumber) { this->ArmMoveNumber = ArmMoveNumber; }

	void SetAttackFlag(bool AttackFlag) { this->AttackFlag = AttackFlag; }

	void SetDamageFlag(bool DamageFlag) { this->DamageFlag = DamageFlag; }

	void SetArmWeight(float ArmWeight) { this->ArmWeight = ArmWeight; }

	void SetArmScale(float Armscale) { this->Armscale = Armscale; }

	void SetMove(float XMax, float ZMax) { this->XMax = XMax; this->ZMax = ZMax; }

	void ResetWeight(Enemy* enemy);
	
	void Rebound(Enemy* enemy);
	
	void EffectMove();

private:
	Object3d* Armobj;
	Object3d* object3d;
	Model* model;
	Model* Armmodel;
	XMFLOAT3 pos = { 0,0,-10 };
	XMFLOAT3 Armpos = { 0,0,0 };
	XMFLOAT3 ArmRot = { 0,270,0 };
	XMFLOAT3 distance{};
	XMFLOAT3 rebound{};

	float PlayerSpeed = 0.3f;
	//座標を戻す
	bool undoPos = false;
	float AfterRot =270.0f;
	float rad = 0.4f;
	float XMax = 0.0f;
	float ZMax = 0.0f;
	const float PI = 3.14f;
	//腕の変数
	float radius = 0.0f;
	float speed = 0.0f;
	float scale = 10.0f;
	float initscale = 0.0f;
	float scaleVel = 3.0f;
	float initspeed = 0.0f;
	float initrotation = 0.0f;
	float initArmRotation = 0.0f;
	float circleX = 0.0f;
	float circleZ = 0.0f;
	float Armradius = 0.0f;
	float ArmSpeed = 90.0f;
	float Armscale = 1.0f;
	float ArmCircleX = 0.0f;
	float ArmCircleZ = 0.0f;
	float ArmWeight = 0.0f;
	unsigned int SpeedSub = 0;
	float power = 0.0f;
	//いろいろなフラグ
	int ArmMoveNumber = 0;
	bool AttackFlag = false;
	bool DamageFlag = false;
	int AttackMoveNumber = 0;
	int Interval = 0;
	int FlashCount = 0;
	//イージングのためのやつ
	float frame = 0.0f;
	float frameMax = 27.0f;
	float frame2 = 0.0f;
	float frameMax2 = 80.0f;
	float frame3 = 0.0f;
	float frameMax3 = 80.0f;
	//HP
	int HP = 10;
	int Lv = 1;
	float Exp = 0.0f;
	float StickrotX = 0;
	float StickrotY = 0;
	XMFLOAT3 angle = { 0,0,0 };
	bool onGround = true;
	// 落下ベクトル
	DirectX::XMVECTOR fallV;
};