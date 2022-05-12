#pragma once
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
class InterEnemy;
class Player : public Object3d {
public:
	Player();

	bool Initialize() override;
	void Finalize();
	void Update() override;
	void SelectUp();
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

	void SetHp(int hp) { this->HP = hp; }

	void SetInterval(int Interval) { this->Interval = Interval; }

	void SetFlash(int Flash) { this->FlashCount = FlashCount; }

	void SetArmMoveNumber(int ArmMoveNumber) { this->ArmMoveNumber = ArmMoveNumber; }

	void SetAttackFlag(bool AttackFlag) { this->AttackFlag = AttackFlag; }

	void SetDamageFlag(bool DamageFlag) { this->DamageFlag = DamageFlag; }

	void SetArmWeight(float ArmWeight) { this->ArmWeight = ArmWeight; }

	void SetArmScale(float Armscale) { this->Armscale = Armscale; }

	void SetMove(float XMax, float ZMax) { this->XMax = XMax; this->ZMax = ZMax; }

	//腕の重みリセット
	void ResetWeight(InterEnemy* enemy);

	//ダメージ食らったとき
	void Rebound(InterEnemy* enemy);
	
	//エフェクト
	void EffectMove();
	
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
	XMFLOAT3 pos = { 0,0,-10 };
	XMFLOAT3 oldPos{};
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
	float frameMax = 15.0f;
	bool wet = false;
	int wetC = 0;
	//ステータス的なやつ
	int HP = 10;
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
	int move_count = 0;
	//チャージ攻撃のための変数
	float speedlimit = 0.0f;
	int chargeTimer = 0;
	float afterSpeed = 0;
	float afterScale = 0;
	int RotCount = 0;
};