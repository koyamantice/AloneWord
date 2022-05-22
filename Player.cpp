#include "Player.h"
#include "Input.h"
#include"Collision.h"
#include"Easing.h"
#include "DebugText.h"
#include<sstream>
#include<iomanip>
#include "stdlib.h"
#include"Rice.h"
#include "InterBoss.h"
#include "SphereCollider.h"
#include "ParticleManager.h"
#include "CollisionManager.h"
#include "CollisionAttribute.h"
#include "FbxLoader.h"
#include "ModelManager.h"
#include "ImageManager.h"
#include "Easing.h"
#include <XorShift.h>
using namespace DirectX;
Input* input = Input::GetInstance();

Player::Player() {
	//モデル読み込み
	model = ModelManager::GetIns()->GetModel(ModelManager::Player);
	Armmodel = ModelManager::GetIns()->GetModel(ModelManager::Arm);
	object3d = new Object3d();
	Armobj = new Object3d();
	move_model1 = ModelManager::GetIns()->GetFBXModel(ModelManager::MottiMove);
	move_object1 = new FBXObject3d;
	Charge = Texture::Create(ImageManager::Charge, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	
	for (std::size_t i = 0; i < ChargeEffect.size(); i++) {
		ChargeEffect[i] = Texture::Create(ImageManager::ChargeEffect, {0,0,0}, {0.5f,0.5f,0.5f}, {1,1,1,1});
	}
}

bool Player::Initialize() {
	//各モデルの初期化
	//プレイヤー
	object3d = Object3d::Create();
	object3d->SetModel(model);
	position = { 0,0,0 };
	object3d->SetPosition(position);
	object3d->SetRotation({ 0,270,0 });
	object3d->SetScale(plasca);
	//腕
	Armobj = Object3d::Create();
	Armobj->SetModel(Armmodel);
	Armradius = ArmSpeed * PI / 180.0f;
	ArmCircleX = cosf(Armradius) * Armscale;
	ArmCircleZ = sinf(Armradius) * Armscale;
	Armpos.x = ArmCircleX + pos.x;
	Armpos.z = ArmCircleZ + pos.z;
	Armobj->SetPosition(Armpos);
	Armobj->SetScale({ 1.4f,1.4f,1.4f });
	Armobj->Update();

	//FBX
	move_object1->Initialize();
	move_object1->SetModel(move_model1);
	move_object1->SetScale(plasca);
	move_object1->SetPosition(position);
	move_object1->SetRotation(rot);

	//チャージ時のサークル
	Charge = Texture::Create(ImageManager::Charge, { 0,0,0 }, { 1,1,1 }, { 1,1,1,1 });
	Charge->TextureCreate();
	Charge->SetPosition(position);
	Charge->SetRotation({ 90.0f,0.0f,0.0f });
	Charge->SetScale(sca);
	Charge->Update();

	//チャージ時に出る周りの弾
	for (std::size_t i = 0; i < ChargeEffect.size(); i++) {
		ChargeEffect[i] = Texture::Create(ImageManager::ChargeEffect, { 0,0,0 }, { 1,1,1 }, { 1,1,1,1 });
		ChargeEffect[i]->TextureCreate();
		//chargerot[i] = { 90.0f,0.0f,0.0f };
		ChargeEffect[i]->SetRotation(chargerot[i]);
		chargesca[i] = { 0.3f,0.3f,0.3f };
		ChargeEffect[i]->SetScale(chargesca[i]);
		ChargeEffect[i]->Update();
	}
	//effecttexture = Texture::Create(4, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	//effecttexture->TextureCreate();
	////effecttexture->SetRotation({ 90,0,0 });
	//effecttexture->SetScale({ 0.2f,0.2f,0.2f });
	// コライダーの追加
	float radius = 0.6f;
	SetCollider(new SphereCollider(XMVECTOR({ 0,radius,0,0 }), radius));
	collider->SetAttribute(COLLISION_ATTR_ALLIES);

	//カメラのためのポジション(初期化)
	//targetpos = position;
	return true;
}
//開放
void Player::Finalize() {
	delete object3d;
	delete Armobj;
	delete Charge;
	for (std::size_t i = 0; i < ChargeEffect.size(); i++) {
		delete ChargeEffect[i];
	}
}

//更新
void Player::Update() {
	if (pause) {
		return;
	}
	oldPos = position;
	rot = this->object3d->GetRotation();
	Charge->Update();
	Charge->SetPosition(position);
	Charge->SetScale(sca);
	for (std::size_t i = 0; i < ChargeEffect.size(); i++) {
		ChargeEffect[i]->Update();
		ChargeEffect[i]->SetPosition(chargepos[i]);
		ChargeEffect[i]->SetScale({0.1f,0.1f,0.1f});
	}
	object3d->Update();
	Armobj->Update();
	StickrotX = input->GetPosX();
	StickrotY = input->GetPosY();
	//effecttexture->Update();
	if (wet) {
		wetC++;
		if (wetC > 20) {
			wet = false;
			wetC = 0;
		}
	}

	//プレイヤーの動き系
	if (Interval <= 80) {
		//プレイヤーの移動
		if (!(StickrotX<650 && StickrotX>-650)) {
			position.x += sin(atan2(StickrotX, StickrotY)) * PlayerSpeed;
			if (!AttackFlag) {
				rot.y = ((-atan2(StickrotX, StickrotY) * (180.0f / XM_PI))) + 90;
				ArmRot.y = ((-atan2(StickrotX, StickrotY) * (180.0f / XM_PI))) + 90;
				ArmSpeed = ((atan2(StickrotX, StickrotY) * (180.0f / XM_PI))) - 90;
			}
		}

		if (!(StickrotY<650 && StickrotY>-650)) {
			position.z -= cos(atan2(StickrotX, StickrotY)) * PlayerSpeed;
			if (!AttackFlag) {
				rot.y = ((-atan2(StickrotX, StickrotY) * (180.0f / XM_PI))) + 90;
				ArmRot.y = ((-atan2(StickrotX, StickrotY) * (180.0f / XM_PI))) + 90;
				ArmSpeed = ((atan2(StickrotX, StickrotY) * (180.0f / XM_PI))) - 90;
			}
		}
		
		//的とあたったときに加速する
		if (AddSpeed != 0.0f) {
			Speedframe += 0.02f;
			AddSpeed = Ease(Out, Cubic, Speedframe, AddSpeed, 0.0f);
		}
		else {
			Speedframe = 0.0f;
		}
		PlayerSpeed = 0.3f + AddSpeed;

		//攻撃関係
		if (AttackFlag == false) {
			//if (input->TriggerButton(input->Button_RB)) {
			//	RotCount = 0;
			//}
			//ため時間
			if (input->PushButton(input->Button_A)) {
				move_count = 0;
				ChargeEffectMove();
				chargeTimer++;
				PlayerSpeed = 0.2f;

				if (plasca.x<0.004f) {
					state = down;
				}
				if (plasca.x >= 0.007f) {
					state = up;
				}

				if (state==up) {
					plasca.x -= 0.00015f;
					plasca.y -= 0.00015f;
					plasca.z -= 0.00015f;
				} 
				if(state==down) {
					plasca = {
					0.007f,
					0.007f,
					0.007f,
					};
				}

				if (sca.x < 0.0f) {
					sca = { 0.7f,0.7f,0.7f };
				} else {
					sca.x -= 0.015f;
					sca.y -= 0.015f;
					sca.z -= 0.015f;
				}
				if ((chargeTimer % 100 == 0) && (RotCount <= 2)) {
					RotCount++;
					ChangeScale = true;
				}
				//チャージ時のエフェクト
				if (RotCount<1) {
					Charge->SetColor({1,1,1,1});
				} else if(RotCount < 2) {
					Charge->SetColor({ 1,1,0,1 });
				} else if (RotCount < 3) {
					Charge->SetColor({ 1,0.5f,0,1 });
				} else {
					Charge->SetColor({ 1,0,0,1 });
				}
				/*if (speedlimit <= ArmSpeed) {
					ArmSpeed--;
					ArmRot.y++;
				}*/
			}
			else {
				plasca = {
				0.007f,
				0.007f,
				0.007f,
				};
				for (std::size_t i = 0; i < ChargeEffect.size(); i++) {
					EffectTimer[i] = 0;
					Chargeframe[i] = 0.0f;
				}
				//ため開放
				if (chargeTimer >= 100) {

					ReleaseStart = true;
					AttackFlag = true;
					AttackMoveNumber = 1;
					RotTimer = 200 * (int)RotCount;
					RotPower = 10.0f;
					ChangeScale = true;
				}
				else {
					for (std::size_t i = 0; i < ChargeEffect.size(); i++) {
						ChargeAlive[i] = false;
					}
					chargeTimer = 0;
				}
			}
		}
	}

	//チャージのエフェクト
	if (ReleaseStart == true) {
		ChargeRelease();
	}
	//チャージ時間に応じてプレイヤーのスケール変更
	if (ChangeScale == true) {
		if (scaleframe >= 1.0f) {
			ChangeScale = false;
			scaleframe = 0.0f;
		}
		else {
			scaleframe += 0.1f;
		}

		//plasca = {
		//Ease(In,Cubic,scaleframe,plasca.x,Aftersca.x),
		//Ease(In,Cubic,scaleframe,plasca.y,Aftersca.y),
		//Ease(In,Cubic,scaleframe,plasca.z,Aftersca.z)
		//};
	}
	//振り回している
	if (AttackFlag == true) {
		RotTimer--;

		if (RotTimer >= 0 && RotPower >= 0.0f) {
			rot.y -= RotPower;
			ArmSpeed += RotPower;
		}
		else {
			chargeTimer = 0;
			RotCount = 0;
			RotTimer = 0;
			ArmWeight = 0.0f;
			AttackFlag = false;
		}

		if (RotTimer <= 150) {
			RotPower -= 0.05f;
		}
	}

	//アニメーション用のキー入力
	if ((input->LeftTiltStick(input->Right)) || (input->LeftTiltStick(input->Left))
		|| (input->LeftTiltStick(input->Up)) || (input->LeftTiltStick(input->Down))) {
		move_count++;
	} else {
		move_count = 0;
	}

	//FlashCount == 4までプレイヤーがダメージを食らったあとの判定
	if (Interval != 0 && FlashCount <= 5) {
		Interval--;
	}

	if (Interval != 100 && Interval != 0 && Interval % 20 == 0) {
		FlashCount++;
	}

	if (FlashCount == 4) {
		FlashCount = 0;
		Interval = 0;
	}

	// 落下処理
	if (!onGround) {
		// 下向き加速度
		const float fallAcc = -0.01f;
		const float fallVYMin = -0.5f;
		// 加速
		fallV.m128_f32[1] = max(fallV.m128_f32[1] + fallAcc, fallVYMin);
		// 移動
		position.x += fallV.m128_f32[0];
		position.y += fallV.m128_f32[1];
		position.z += fallV.m128_f32[2];
	}

	// ワールド行列更新
	UpdateWorldMatrix();
	collider->Update();

	SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collider);
	assert(sphereCollider);

	// クエリーコールバッククラス
	class PlayerQueryCallback : public QueryCallback {
	public:
		PlayerQueryCallback(Sphere* sphere) : sphere(sphere) {};

		// 衝突時コールバック関数
		bool OnQueryHit(const QueryHit& info) {

			const XMVECTOR up = { 0,1,0,0 };

			XMVECTOR rejectDir = XMVector3Normalize(info.reject);
			float cos = XMVector3Dot(rejectDir, up).m128_f32[0];

			// 地面判定しきい値
			const float threshold = cosf(XMConvertToRadians(30.0f));

			if (-threshold < cos && cos < threshold) {
				sphere->center += info.reject;
				move += info.reject;
			}

			return true;
		}

		Sphere* sphere = nullptr;
		DirectX::XMVECTOR move = {};
	};

	PlayerQueryCallback callback(sphereCollider);

	// 球と地形の交差を全検索
	CollisionManager::GetInstance()->QuerySphere(*sphereCollider, &callback, COLLISIONSHAPE_MESH);
	// 交差による排斥分動かす
	position.x += callback.move.m128_f32[0];
	position.y += callback.move.m128_f32[1];
	position.z += callback.move.m128_f32[2];
	// ワールド行列更新
	UpdateWorldMatrix();
	collider->Update();

	// 球の上端から球の下端までのレイキャスト
	Ray ray;
	ray.start = sphereCollider->center;
	ray.start.m128_f32[1] += sphereCollider->GetRadius();
	ray.dir = { 0,-1,0,0 };
	RaycastHit raycastHit;

	// 接地状態
	if (onGround) {
		// スムーズに坂を下る為の吸着距離
		const float adsDistance = 0.2f;
		// 接地を維持
		if (CollisionManager::GetInstance()->Raycast(ray, COLLISION_ATTR_LANDSHAPE, &raycastHit, sphereCollider->GetRadius() * 2.0f + adsDistance)) {
			onGround = true;
			position.y -= (raycastHit.distance - sphereCollider->GetRadius() * 2.0f);
		}
		// 地面がないので落下
		else {
			onGround = false;
			fallV = {};
		}
	}
	// 落下状態
	else if (fallV.m128_f32[1] <= 0.0f) {
		if (CollisionManager::GetInstance()->Raycast(ray, COLLISION_ATTR_LANDSHAPE, &raycastHit, sphereCollider->GetRadius() * 2.0f)) {
			// 着地
			onGround = true;
			position.y -= (raycastHit.distance - sphereCollider->GetRadius() * 2.0f);
		}
	}

	//プレイヤーが行ける限界
	if (position.y <= 0.0f) {
		position.y = 0.0f;
		onGround = true;
	}
	if (position.z< -17) {
		position.z = -17;
	}
	if (position.z > 22) {
		position.z = 22;
	}
	Armradius = ArmSpeed * PI / 180.0f;
	ArmCircleX = cosf(Armradius) * Armscale;
	ArmCircleZ = sinf(Armradius) * Armscale;
	Armpos.x = ArmCircleX + position.x;
	Armpos.y = position.y;
	Armpos.z = ArmCircleZ + position.z;
	Armobj->SetPosition(Armpos);
	//各オブジェクトのアップデート
	object3d->Update();
	object3d->SetPosition(position);
	object3d->SetRotation(rot);
	Armobj->SetRotation(ArmRot);
	//パーティクル発生
	BirthParticle();
	//カメラのためのポジション(更新)
	move_object1->SetPosition(position);
	move_object1->SetScale(plasca);
	move_object1->SetRotation(rot);

	//FBXアニメーションの管理(移動)
	if (move_count == 1) {
		move_object1->PlayAnimation();
	}

	else if (move_count == 0) {
		move_object1->StopAnimation();
	}

	move_object1->Update();
}

//セレクト画面でのアップデート
void Player::SelectUp() {
	if (pause) {
		return;
	}
	rot = this->object3d->GetRotation();
	object3d->Update();
	move_object1->SetPosition(position);
	move_object1->SetScale(plasca);
	move_object1->SetRotation(rot);
	if (move_count == 1) {
		move_object1->PlayAnimation();
	}

	else if (move_count == 0) {
		move_object1->StopAnimation();
	}
	move_object1->Update();
	Armobj->Update();
	StickrotX = input->GetPosX();
	StickrotY = input->GetPosY();
	//effecttexture->Update();
	//object3d->SetRotation({ 90,0,0 });

	rot = { 0,0,0 };
	if ((position.x <= 13 && position.x >= -13)) {
		if (!(StickrotX<650 && StickrotX>-650)) {
			rot.y = ((-atan2(StickrotX, StickrotY) * (180.0f / XM_PI))) + 90;
			position.x += sin(atan2(StickrotX, StickrotY)) * PlayerSpeed;
		}
	}
	if ((position.z <= 7.5f && position.z >= -6.65f)) {
		if (!(StickrotY<650 && StickrotY>-650)) {
			rot.y = ((-atan2(StickrotX, StickrotY) * (180.0f / XM_PI))) + 90;
			position.z -= cos(atan2(StickrotX, StickrotY)) * PlayerSpeed;
		}
	}
	//プレイヤーが行ける限界
	if (position.x > 13) {
		position.x = 13;
	}
	if (position.x < -13) {
		position.x = -13;
	}
	if (position.z > 7.5f) {
		position.z = 7.5f;
	}
	if (position.z < -6.65f) {
		position.z = -6.65f;
	}
	//アニメーション用のキー入力
	if ((input->LeftTiltStick(input->Right)) || (input->LeftTiltStick(input->Left))
		|| (input->LeftTiltStick(input->Up)) || (input->LeftTiltStick(input->Down))) {
		move_count++;
	} else {
		move_count = 0;
	}

	// 落下処理
	if (!onGround) {
		// 下向き加速度
		const float fallAcc = -0.01f;
		const float fallVYMin = -0.5f;
		// 加速
		fallV.m128_f32[2] = max(fallV.m128_f32[2] + fallAcc, fallVYMin);
		// 移動
		position.x += fallV.m128_f32[0];
		position.y += fallV.m128_f32[1];
		position.z += fallV.m128_f32[2];
	}
	if (position.y <= 0.0f) {
		position.y = 0.0f;
		onGround = true;
	}
	//Armradius = ArmSpeed * PI / 180.0f;
	//ArmCircleX = cosf(Armradius) * Armscale;
	//ArmCircleZ = sinf(Armradius) * Armscale;
	Armobj->SetPosition({0,-90,-100});
	//移動
	object3d->Update();
	object3d->SetPosition(position);
	object3d->SetRotation(rot);
	//Armobj->SetRotation(ArmRot);
	//パーティクル発生
	//BirthParticle();
}

//タイトル画面でのアップデート
void Player::TitleUp() {
	if (pause) {
		return;
	}
	rot = this->object3d->GetRotation();
	//アニメーション用のキー入力
	rot.y = 45.0f;
	move_count++;
	//position = { 2.0f,-4.0f ,0};
	onGround = true;
	position = {4.0f,-1.0f,-5.0f};
	//移動
	object3d->Update();
	object3d->SetPosition(position);
	object3d->SetRotation(rot);
	//パーティクル発生
	BirthParticle();
	//カメラのためのポジション(更新)
	move_object1->SetPosition(position);
	move_object1->SetScale(plasca);
	move_object1->SetRotation(rot);
	//FBXアニメーションの管理
	if (move_count == 1) {
		move_object1->PlayAnimation();
	}
	else if (move_count == 0) {
		move_object1->StopAnimation();
	}
	move_object1->Update();
}

//描画
void Player::Draw(DirectXCommon* dxCommon) {

	//ImGui::Begin("test");
	////ImGui::SliderFloat("pos.x", &position.x, 50, -50);
	//ImGui::SliderFloat("rot.y", &rot.y, 50, -50);
	//ImGui::SliderFloat("overframe", &overframe, 50, -50);
	////ImGui::("boundpower.x %d", &AttackFlag, 50, -50);
	//ImGui::Text("overMove:%d", overMove);
	//ImGui::End();
	Texture::PreDraw();
	if (chargeTimer!=0&&!AttackFlag) {
		Charge->Draw();
	}

	for (std::size_t i = 0; i < ChargeEffect.size(); i++) {
		if (ChargeAlive[i] == true) {
			ChargeEffect[i]->Draw();
		}
	}
	Object3d::PreDraw();
	if (FlashCount % 2 == 0) {
		move_object1->Draw(dxCommon->GetCmdList());
	}

	//arm_no_object1->Draw(dxCommon->GetCmdList());
	

	//have_object1->Draw(dxCommon->GetCmdList());
}

//ポーズ
void Player::Pause(const int& Timer) {
	wait++;
	if (wait >= Timer) {
		pause = false;
		wait = 0;
	} else {
		pause = true;
	}
}

//敵が腕から離れる
void Player::ResetWeight(InterEnemy* enemy) {
	XMFLOAT3 boundpower = enemy->GetBoundPower();
	XMFLOAT3 enepos = enemy->GetPosition();
	if (ArmWeight == 0.0f) {
		if (enemy->GetEnemyCatch()) {
			enemy->SetBound(true);
			enemy->SetEnemyCatch(false);
		}
		enemy->Setboundpower(boundpower);
	}
}

//ダメージ食らったときにプレイヤーが飛ばされる
void Player::Rebound() {
	/*XMFLOAT3 enepos = boss->GetPosition();

	distance.x = position.x - enepos.x;
	distance.z = position.z - enepos.z;
*/
	if (DamageFlag == true) {
		rebound.x = sin(atan2f(distance.x, distance.z)) * 0.5f;
		rebound.z = cos(atan2f(distance.x, distance.z)) * 0.5f;

		if (damageframe >= 1.0f) {
			damageframe = 0.0f;
			DamageFlag = false;
		}
		else {
			damageframe += 0.05f;
		}

		rebound = {
		Ease(In,Cubic,damageframe,rebound.x,0),
		Ease(In,Cubic,damageframe,rebound.y,0),
		Ease(In,Cubic,damageframe,rebound.z,0)
		};

		JumpG -= 0.05f;
		if (position.y < 0.0f) {
			position.y = 0.0f;
			JumpG = 0.0f;
		}
		position.y += JumpG;
	}

	if (position.x <= 22.0f && position.x >= -20.0f) {
		position.x += rebound.x;
	}
	if (position.z <= 20.0f && position.z >= -17.0f) {
		position.z += rebound.z;
	}

	object3d->SetPosition(position);
}

//パーティクルが出てくる
void Player::BirthParticle() {

	if (AttackMoveNumber == 0 && AttackFlag == false&& Interval <= 80) {
		if (input->LeftTiltStick(input->Right) || input->LeftTiltStick(input->Left) || input->LeftTiltStick(input->Up) || input->LeftTiltStick(input->Down)) {
			if (oldPos.x!= position.x) {
				count++;
			}
		}
	}
	if (count >= 12) {
		for (int i = 0; i < 6; ++i) {
			const float rnd_vel = 0.1f;
			XMFLOAT3 vel{};
			vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			ParticleManager::GetInstance()->Add(30, { oldPos.x + vel.x,oldPos.y,oldPos.z + vel.z }, vel, XMFLOAT3(), 0.7f, 0.1f);
		}
		count = 0;
	}
	{
		if (AttackFlag == true) {
			const float rnd_vel = 0.1f;
			XMFLOAT3 vel{};
			vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
			vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

			ParticleManager::GetInstance()->Add(10, { Armpos.x,Armpos.y,Armpos.z }, vel, XMFLOAT3(), 1.0f, 0.0f);
		}
	}

}

//元の位置に戻る
void Player::BackPos() {
	position = oldPos;
}

//導入
void Player::Begin() {
	if (pause) {
		return;
	}
	oldPos = position;
	rot = this->object3d->GetRotation();
	object3d->Update();
	Armobj->Update();
	StickrotX = input->GetPosX();
	StickrotY = input->GetPosY();
	//effecttexture->Update();
	// ワールド行列更新
	UpdateWorldMatrix();
	
	Armradius = ArmSpeed * PI / 180.0f;
	ArmCircleX = cosf(Armradius) * Armscale;
	ArmCircleZ = sinf(Armradius) * Armscale;
	Armpos.x = ArmCircleX + position.x;
	Armpos.y = position.y;
	Armpos.z = ArmCircleZ + position.z;
	Armobj->SetPosition(Armpos);
	//移動
	object3d->Update();
	object3d->SetPosition(position);
	object3d->SetRotation(rot);
	Armobj->SetRotation(ArmRot);
	//パーティクル発生
	BirthParticle();
	
	move_object1->SetPosition(position);
	move_object1->SetRotation(rot);
	
	move_object1->Update();
}

//撃破
void Player::End() {
	if (pause) {
		return;
	}
	oldPos = position;
	rot = this->object3d->GetRotation();
	object3d->Update();
	Armobj->Update();
	StickrotX = input->GetPosX();
	StickrotY = input->GetPosY();
	//effecttexture->Update();
	if (wet) {
		wetC++;
		if (wetC > 20) {
			wet = false;
			wetC = 0;
		}
	}

	// ワールド行列更新
	UpdateWorldMatrix();

	Armradius = ArmSpeed * PI / 180.0f;
	ArmCircleX = cosf(Armradius) * Armscale;
	ArmCircleZ = sinf(Armradius) * Armscale;
	Armpos.x = ArmCircleX + position.x;
	Armpos.y = position.y;
	Armpos.z = ArmCircleZ + position.z;
	Armobj->SetPosition(Armpos);
	//移動
	object3d->Update();
	object3d->SetPosition(position);
	object3d->SetRotation(rot);
	Armobj->SetRotation(ArmRot);
	//パーティクル発生
	BirthParticle();

	move_object1->SetPosition(position);
	move_object1->SetRotation(rot);
	move_object1->StopAnimation();
	move_object1->Update();
}

//チャージ時のエフェクトの動き(吸収)
void Player::ChargeEffectMove() {
	for (std::size_t i = 0; i < ChargeEffect.size(); i++) {
		array<XMFLOAT3,40> chargeposition{};
		
		if (ChargeAlive[i] == false) {
			if (EffectTimer[i] == 0) {
				EffectTimer[i] = rand() % 50;
				chargeposition[i].x = (position.x - chargepos[i].x);
				chargeposition[i].y = (position.y - chargepos[i].y);
				chargeposition[i].z = (position.z - chargepos[i].z);
				chargerot[i].z = (atan2f(chargeposition[i].x, chargeposition[i].y) * (180.0f / XM_PI)) - 90;// *(XM_PI / 180.0f);
				chargerot[i].y = (atan2f(chargeposition[i].x, chargeposition[i].z) * (180.0f / XM_PI)) - 90;// *(XM_PI / 180.0f);
			}
			else {
				EffectTimer[i]--;
			}
			if (EffectTimer[i] == 1) {
				ChargeSpeed[i] = (float)(rand() % 360);
				Chargescale[i] = (float)(rand() % 3 + 3);
				chargepos[i].y = (float)(rand() % 2 + 2);
				ChargeAlive[i] = true;
				EffectTimer[i] = 0;
			}
		}
		else {
			if (Chargescale[i] <= 1.0f) {
				Chargeframe[i] = 0.0f;
				ChargeAlive[i] = false;
			}
			else {
				Chargeframe[i] += 0.01f;
			}

			Chargescale[i] = Ease(In, Cubic, Chargeframe[i], Chargescale[i], 0.0f);
			chargepos[i].y = Ease(In, Cubic, Chargeframe[i], chargepos[i].y, 0.0f);
		}
		Chargeradius[i] = ChargeSpeed[i] * PI / 180.0f;
		ChargeCircleX[i] = cosf(Chargeradius[i]) * Chargescale[i];
		ChargeCircleZ[i] = sinf(Chargeradius[i]) * Chargescale[i];
		chargepos[i].x = ChargeCircleX[i] + position.x;
		chargepos[i].z = ChargeCircleZ[i] + position.z;
		//ChargeEffect[i]->SetRotation(chargerot[i]);
		ChargeEffect[i]->SetPosition(chargepos[i]);
	}
}

//チャージ時のエフェクトの動き(開放)
void Player::ChargeRelease() {
	for (std::size_t i = 0; i < ChargeEffect.size(); i++) {
			if (EffectRelease[i] == false) {
				boundpower[i].x = (float)((int)(XorShift::GetInstance()->xor128()) % 20 - 10);
				boundpower[i].y = (float)((int)(XorShift::GetInstance()->xor128()) % 10 - 5);
				boundpower[i].z = (float)((int)(XorShift::GetInstance()->xor128()) % 20 - 10);
				boundpower[i].x = boundpower[i].x / 10;
				boundpower[i].y = boundpower[i].y / 10;
				boundpower[i].z = boundpower[i].z / 10;
				chargesca[i].x = 0.5f;
				chargesca[i].y = 0.5f;
				chargesca[i].z = 0.5f;
				chargepos[i] = position;
				EffectRelease[i] = true;
			}
			else {
				chargesca[i].x -= 0.01f;
				chargesca[i].y -= 0.01f;
				chargesca[i].z -= 0.01f;
				boundpower[i].y -= 0.02f;
				chargepos[i].x += boundpower[i].x;
				chargepos[i].y += boundpower[i].y;
				chargepos[i].z += boundpower[i].z;

				if (chargesca[i].x <= 0.0f) {
					EffectRelease[i] = false;
					ChargeAlive[i] = false;
					ReleaseStart = false;
				}
			}
		ChargeEffect[i]->SetScale(chargesca[i]);
		ChargeEffect[i]->SetPosition(chargepos[i]);
	}
}

void Player::gameoverMovie(int Timer) {
	float RotPower = 0.0f;
	if (Timer == 250) {
		overMove++;
	}

	switch (overMove) {
	case 1:
		
		if (overframe < 1.0f) {
			overframe += 0.005f;
			break;
		}
		else {
			overframe = 1.0f;
			RotPower = 0.0f;
			overMove++;
			break;
		}

	case 2:
		if (rot.x <= 90) {
			rot.x += 2.0f;
		}

		//case 2:
		//	AfterPos = {
		//				pos.x,
		//				1,
		//				pos.z,
		//	};

		//	if (frame < 1.0f) {
		//		frame += 0.08f;
		//		break;
		//	}
		//	else {
		//		frame = 1.0f;
		//		break;
		//	}
	}

	RotPower = Ease(In, Cubic, overframe, RotPower, 20.0f);
	if (overMove == 1) {
		rot.y += RotPower;
	}

	plasca = {
	Ease(In,Cubic,overframe,plasca.x,0.002f),
	Ease(In,Cubic,overframe,plasca.y,0.002f),
	Ease(In,Cubic,overframe,plasca.z,0.002f),
	};

	move_object1->SetScale(plasca);
	//move_object1->SetPosition(pos);
	move_object1->SetRotation(rot);
}

void Player::gameover(int Timer) {
	gameoverMovie(Timer);
	move_object1->StopAnimation();
	move_object1->Update();
}
