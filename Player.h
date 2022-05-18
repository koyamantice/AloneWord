﻿#pragma once
#include"Object3d.h"
#include"Model.h"
#include <DirectXMath.h>
#include <Input.h>
#include"CollisionPrimitive.h"
#include "Sprite.h"
#include "Texture.h"
#include "DirectXCommon.h"
#include "FBXModel.h"
#include "FBXObject3d.h"
#include <array>       // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
class InterBoss;
class InterEnemy;
class Player : public Object3d {
public:
	Player();

	bool Initialize() override;
	void Finalize();
	void Update() override;
	void SelectUp();
	void TitleUp();
	void Draw(DirectXCommon* dxCommon);
	void Pause(const int& Timer);
	void Begin();
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

	const XMFLOAT3& GetDistance() { return distance; }

	const float& GetHp() { return HP; }

	const int& GetInterval() { return Interval; }

	const int& GetFlashCount() { return FlashCount; }

	const bool& GetAttackFlag() { return AttackFlag; }

	const bool& GetDamageFlag() { return DamageFlag; }

	const float& GetArmWeight() { return ArmWeight; }

	const float& GetArmScale() { return Armscale; }

	const float& GetArmSpeed() { return ArmSpeed; }

	const float& GetPower() { return power; }

	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(XMFLOAT3 position) { this->position=position; 
	object3d->SetPosition(position);
	}

	void SetRotation(XMFLOAT3 rotation) { object3d->SetRotation(rotation); }

	void SetArmPosition(XMFLOAT3 Armpos) { this->Armpos = Armpos; }

	void SetArmRotation(XMFLOAT3 ArmRot) { this->ArmRot = ArmRot; }

	void SetHp(float hp) { this->HP = hp; }

	void SetInterval(int Interval) { this->Interval = Interval; }

	void SetFlash(int Flash) { this->FlashCount = FlashCount; }

	void SetCharge(int chargeTimer) { this->chargeTimer = chargeTimer; }

	void SetAttackFlag(bool AttackFlag) { this->AttackFlag = AttackFlag; }

	void SetDamageFlag(bool DamageFlag) { this->DamageFlag = DamageFlag; }

	void SetArmWeight(float ArmWeight) { this->ArmWeight = ArmWeight; }

	void SetAddSpeed(float AddSpeed) { this->AddSpeed = AddSpeed; }

	void SetJumpG(float JumpG) { this->JumpG = JumpG; }

	void SetMove(float XMax, float ZMax) { this->XMax = XMax; this->ZMax = ZMax; }

	void SetRotTimer(int RotTimer) { this->RotTimer = RotTimer; }

	void SetChargeTimer(int chargeTimer) { this->chargeTimer = chargeTimer; }

	void SetRotCount(int RotCount) { this->RotCount = RotCount; }

	void SetDistance(XMFLOAT3 distance) { this->distance = distance; }

	//腕の重みリセット
	void ResetWeight(InterEnemy* enemy);

	//ダメージ食らったとき
	void Rebound(InterBoss* enemy);
	
	//エフェクト
	void EffectMove();

	//チャージ
	void ChargeEffectMove();
	
	//足元にパーティクル
	void BirthParticle();
	void BackPos();

	const bool& GetWet() { return wet; }
	void SetWet(bool wet) { this->wet = wet; }
private:
	Object3d* Armobj;
	Object3d* object3d;
	Model* model;
	Model* Armmodel;
	Texture* Charge=nullptr;
	
	XMFLOAT3 plasca = { 0.007f,0.007f,0.007f };
	XMFLOAT3 Aftersca = { 0,0,0 };
	XMFLOAT3 sca = { 0.7f,0.7f,0.7f };
	XMFLOAT3 pos = { 0,0,-10 };
	XMFLOAT3 oldPos{};
	XMFLOAT3 Armpos = { 0,0,0 };
	XMFLOAT3 ArmRot = { 0,270,0 };
	XMFLOAT3 distance{};
	XMFLOAT3 rebound{};
	bool state;
	enum state {
		up,
		down
	};
	float PlayerSpeed = 0.3f;
	//座標を戻す
	float AfterRot =270.0f;
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
	float Armscale = 0.5f;
	float ArmCircleX = 0.0f;
	float ArmCircleZ = 0.0f;
	float ArmWeight = 0.0f;
	float power = 0.0f;
	//いろいろなフラグ
	bool AttackFlag = false;
	bool DamageFlag = false;
	int AttackMoveNumber = 0;
	int Interval = 0;
	int FlashCount = 0;
	//イージングのためのやつ
	float frame = 0.0f;
	float frame2 = 0.0f;
	float Speedframe = 0.0f;
	float damageframe = 0.0f;
	float scaleframe = 0.0f;
	bool wet = false;
	int wetC = 0;
	//ステータス的なやつ
	float HP = 10;
	float StickrotX = 0;
	float StickrotY = 0;
	XMFLOAT3 angle = { 0,0,0 };
	bool onGround = true;
	// 落下ベクトル
	DirectX::XMVECTOR fallV;
	//カメラのためのやつ
	double angleR;
	float angleX;
	float angleZ;
	int wait = 0;
	XMFLOAT3 rot;
	bool pause = false;
	int count = 0;
	//動いてるときのFBX
	FBXModel* move_model1 = nullptr;
	FBXObject3d* move_object1 = nullptr;
	//パワーを貯めているときのFBX
	FBXModel* power_model1 = nullptr;
	FBXObject3d* power_object1 = nullptr;
	int move_count = 0;
	//チャージ攻撃のための変数
	float RotPower = 10.0f;
	int chargeTimer = 0;
	int RotTimer = 0;
	int RotCount = 0;
	float AddSpeed = 0.0f;
	float JumpG = 0.0f;
	bool ChangeScale = false;
	//チャージ時エフェクトのパーティクル(配列可濃厚なのでこっちに書く)
	array<Texture*,20> ChargeEffect;
	array<XMFLOAT3, 20> chargepos;
	array<XMFLOAT3, 20> chargerot;
	array<bool ,20>ChargeAlive;
	array<float,20> Chargeradius;
	array<float,20> ChargeSpeed;
	array<float,20> Chargescale;
	array<float,20> ChargeCircleX;
	array<float,20> ChargeCircleZ;
	array<float,20> Chargeframe;
	array<int, 20> EffectTimer;
};