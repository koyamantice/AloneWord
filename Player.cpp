#include "Player.h"
#include "Input.h"
#include"Collision.h"
#include"Easing.h"
#include "DebugText.h"
#include<sstream>
#include<iomanip>
#include "stdlib.h"
#include"Rice.h"
#include "SphereCollider.h"
#include "ParticleManager.h"
#include "CollisionManager.h"
#include "CollisionAttribute.h"
#include "FbxLoader.h"
#include <ModelManager.h>
#include <Easing.h>
using namespace DirectX;
Input* input = Input::GetInstance();

Player::Player() {
	model = ModelManager::GetIns()->GetModel(ModelManager::Player);
	Armmodel = ModelManager::GetIns()->GetModel(ModelManager::Arm);
	object3d = new Object3d();
	Armobj = new Object3d();
	move_model1 = ModelManager::GetIns()->GetFBXModel(ModelManager::MottiMove);
	move_object1 = new FBXObject3d;
}

bool Player::Initialize() {
	object3d = Object3d::Create();
	object3d->SetModel(model);
	position = { 0,0,0 };
	object3d->SetPosition(position);
	object3d->SetRotation({ 0,270,0 });
	object3d->SetScale({ 0.7f,0.7f,0.7f });

	Armobj = Object3d::Create();
	Armobj->SetModel(Armmodel);
	Armradius = ArmSpeed * PI / 180.0f;
	ArmCircleX = cosf(Armradius) * Armscale;
	ArmCircleZ = sinf(Armradius) * Armscale;
	Armpos.x = ArmCircleX + pos.x;
	Armpos.z = ArmCircleZ + pos.z;
	Armobj->SetPosition(Armpos);
	Armobj->SetScale({ 1.4f,1.4f,1.4f });

	move_object1->Initialize();
	move_object1->SetModel(move_model1);
	move_object1->SetScale({ 0.007f, 0.007f, 0.007f });
	move_object1->SetPosition(position);
	move_object1->SetRotation(rot);
	
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

void Player::Finalize() {
	delete object3d;
	delete Armobj;
}

void Player::Update() {
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
	if (AttackMoveNumber == 0 && AttackFlag == false
		&& Interval <= 80) {
		if (!(StickrotX<650 && StickrotX>-650)) {
			rot.y = ((-atan2(StickrotX, StickrotY) * (180.0f / XM_PI))) + 90;
			position.x += sin(atan2(StickrotX, StickrotY)) * PlayerSpeed;
			ArmRot.y = ((-atan2(StickrotX, StickrotY) * (180.0f / XM_PI))) + 90;
			ArmSpeed = ((atan2(StickrotX, StickrotY) * (180.0f / XM_PI))) - 90;
		}

		if (!(StickrotY<650 && StickrotY>-650)) {
			rot.y = ((-atan2(StickrotX, StickrotY) * (180.0f / XM_PI))) + 90;
			position.z -= cos(atan2(StickrotX, StickrotY)) * PlayerSpeed;
			ArmRot.y = ((-atan2(StickrotX, StickrotY) * (180.0f / XM_PI))) + 90;
			ArmSpeed = ((atan2(StickrotX, StickrotY) * (180.0f / XM_PI))) - 90;
		}

		if (input->TriggerButton(input->Button_RB)) {
			speedlimit = ArmSpeed - 90;
		}

		if (input->PushButton(input->Button_RB)) {
			chargeTimer++;
			if (chargeTimer == 100) {
				chargeTimer = 0;
				RotCount++;
			}
			if (speedlimit <= ArmSpeed) {
				ArmSpeed--;
				ArmRot.y++;
			}
		}
		else {
			
			if (RotCount >= 1) {
				AttackFlag = true;
				afterSpeed = ArmSpeed + (450 * RotCount);
				initArmRotation = ArmRot.y - (450 * RotCount);
			}
			else {
				chargeTimer = 0;
			}
		}

		//攻撃右回り
	/*	if (input->PushButton(input->Button_RB) && ArmWeight != 0.0f) {
			AttackFlag = true;
			AttackMoveNumber = 1;
			initscale = Armscale;
			initspeed = ArmSpeed;
			initrotation = rot.y;
			initArmRotation = ArmRot.y;
			frame2 = 0;
			frame3 = 0;
			if (ArmMoveNumber != 0) {
				ArmMoveNumber = 0;
			}
		}*/

		//左回り
		/*if (input->PushButton(input->Button_LB) && ArmWeight != 0.0f) {
			AttackFlag = true;
			AttackMoveNumber = 3;
			initscale = Armscale;
			initspeed = ArmSpeed;
			initrotation = rot.y;
			initArmRotation = ArmRot.y;
			frame2 = 0;
			frame3 = 0;
			if (ArmMoveNumber != 0) {
				ArmMoveNumber = 0;
			}
		}*/

		//腕のばす
		if (input->TriggerButton(input->Button_A) && ArmWeight <= 6.0f && ArmMoveNumber == 0) {
			ArmMoveNumber = 1;
			initscale = Armscale;
			frame = 0;
			if (AttackMoveNumber != 0 || AttackFlag == true) {
				AttackMoveNumber = 0;
				AttackFlag = false;
			}
		}
	}

	if (AttackFlag == true) {
		if (frame >= RotCount) {
			frame = 0.0f;
			AttackFlag = false;
			chargeTimer = 0;
			RotCount = 0;
		}
		else {
			frame += 0.02f;
		}
		
	}

	//ArmSpeed++;
	ArmSpeed = Ease(In, Cubic, frame, ArmSpeed, afterSpeed);
	ArmRot.y = Ease(In, Cubic, frame, ArmRot.y, initArmRotation);
	//アニメーション用のキー入力
	if ((input->LeftTiltStick(input->Right)) || (input->LeftTiltStick(input->Left))
		|| (input->LeftTiltStick(input->Up)) || (input->LeftTiltStick(input->Down))) {
		move_count++;
	} else {
		move_count = 0;
	}

	//腕を伸ばす
	//if (ArmMoveNumber == 1) {
	//	Armscale = initscale + 3.0f * easeOutBack(frame / frameMax);
	//	if (frame != frameMax) {
	//		frame = frame + 1;
	//	} else {
	//		ArmMoveNumber = 2;
	//		frame = 0;
	//		initscale = Armscale;
	//	}
	//} else if (ArmMoveNumber == 2) {
	//	Armscale = initscale - 3.0f * easeOutBack(frame / frameMax);
	//	if (frame != frameMax) {
	//		frame = frame + 1;
	//	} else {
	//		ArmMoveNumber = 0;
	//		initscale = Armscale;
	//		//Armscale += ArmWeight;
	//	}
	//}

	////攻撃
	//if (AttackFlag == true) {
	//	if (AttackMoveNumber == 1 || AttackMoveNumber == 2) {
	//		ArmSpeed = initspeed - 360.0f * easeBack(frame2 / frameMax2);
	//		rot.y = initrotation + 360.0f * easeBack(frame2 / frameMax2);
	//		ArmRot.y = initArmRotation + 360.0f * easeBack(frame2 / frameMax2);
	//	} else {
	//		ArmSpeed = initspeed + 360.0f * easeBack(frame2 / frameMax2);
	//		rot.y = initrotation - 360.0f * easeBack(frame2 / frameMax2);
	//		ArmRot.y = initArmRotation - 360.0f * easeBack(frame2 / frameMax2);
	//	}
	//	if (frame2 <= 10.0f) {
	//		power = 0.25f;
	//	} else if (frame2 > 10.0f && frame2 <= 20.0f) {
	//		power = 0.5f;
	//	} else if (frame2 > 20.0f && frame2 <= 30.0f) {
	//		power = 0.75f;
	//	} else {
	//		power = 1.0f;
	//	}

	//	if (frame2 < frameMax2) {
	//		frame2 = frame2 + 1;
	//	} else {
	//		AttackFlag = false;
	//		frameMax2 = 40.0f;
	//	}
	//}

	////攻撃時に腕を伸ばしている
	//if (AttackMoveNumber == 1 || AttackMoveNumber == 3) {
	//	if (ArmWeight > 0) {
	//		Armscale = initscale + 3.0f * easeInOut(frame3 / frameMax3);
	//		if (frame3 < frameMax3) {
	//			frame3 = frame3 + 1;
	//		} else {
	//			if (AttackMoveNumber == 1) {
	//				AttackMoveNumber = 2;
	//			} else if (AttackMoveNumber == 3) {
	//				AttackMoveNumber = 4;
	//			}
	//			initscale = Armscale;
	//			scaleVel = 3.0f;
	//			frame3 = 0;
	//			frameMax3 = frameMax2;
	//		}
	//	} else {
	//		AttackMoveNumber = 2;
	//		scaleVel = Armscale - initscale;
	//		initscale = Armscale;
	//		frame3 = 0;
	//		frameMax3 = frameMax2 / 20;
	//	}
	//}

	//else if (AttackMoveNumber == 2 || AttackMoveNumber == 4) {
	//	Armscale = initscale - scaleVel * easeInOut(frame3 / frameMax3);
	//	if (frame3 < frameMax3) {
	//		frame3 = frame3 + 1;
	//	} else {
	//		AttackMoveNumber = 0;
	//		frameMax3 = frameMax2;
	//	}
	//}

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

	if (position.y <= 0.0f) {
		position.y = 0.0f;
		onGround = true;
	}
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
	//カメラのためのポジション(更新)
	/*if (Interval == 0) {
		targetpos = position;
	} else if (Interval != 0 && Interval <= 99) {
		if (targetpos.x != position.x || targetpos.z != position.z) {
			angleX = (position.x - targetpos.x);
			angleZ = (position.z - targetpos.z);
			angleR = sqrt(pow((position.x - targetpos.x), 2) + pow((position.z - targetpos.z), 2));
			if (angleR >= 1.00) {
				targetpos.x += (angleX / (float)angleR) * 0.25f;
				targetpos.x += (angleZ / (float)angleR) * 0.25f;
			} else {
				targetpos = position;
			}
		}
	}*/

	move_object1->SetPosition(position);
	move_object1->SetRotation(rot);
	//FBXアニメーションの管理
	if (move_count == 1) {
		move_object1->PlayAnimation();
	}

	else if (move_count == 0) {
		move_object1->StopAnimation();
	}

	if (input->PushKey(DIK_0)) {
		//have_object1->PlayAnimation();
	}

	move_object1->Update();

}

void Player::SelectUp() {
	if (pause) {
		return;
	}
	rot = this->object3d->GetRotation();
	object3d->Update();
	move_object1->SetPosition(position);
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

//描画
void Player::Draw(DirectXCommon* dxCommon) {
	ImGui::Begin("test");
	ImGui::SliderFloat("frame", &frame, 1, 0);
	ImGui::SliderFloat("ArmSpeed", &ArmSpeed, 360, -360);
	ImGui::SliderFloat("afterSpeed", &afterSpeed, 360, -360);
	ImGui::Text("AttacF:%d", AttackFlag);
	ImGui::Text("timer:%d", chargeTimer);
	ImGui::Unindent();
	ImGui::End();
	Object3d::PreDraw();
	if (FlashCount % 2 == 0) {
		move_object1->Draw(dxCommon->GetCmdList());
		//object3d->Draw();
		Armobj->Draw();
	}
	//arm_no_object1->Draw(dxCommon->GetCmdList());
	

	//have_object1->Draw(dxCommon->GetCmdList());
}

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
void Player::Rebound(InterEnemy* enemy) {
	XMFLOAT3 enepos = enemy->GetPosition();

	distance.x = position.x - enepos.x;
	distance.z = position.z - enepos.z;


	if (DamageFlag == true) {
		if (distance.x <= 0) {
			rebound.x = -0.2f;
		} else {
			rebound.x = 0.2f;
		}

		if (distance.z <= 0) {
			rebound.z = -0.2f;
		} else {
			rebound.z = 0.2f;
		}
		DamageFlag = false;
	}

	if (rebound.x >= 0.0) {
		rebound.x -= 0.005f;
		if (rebound.x <= 0.0f) {
			rebound.x = 0.0f;
		}
	} else {
		rebound.x += 0.005f;
		if (rebound.x >= 0.0f) {
			rebound.x = 0.0f;
		}
	}

	if (rebound.z >= 0.0) {
		rebound.z -= 0.045f;
		if (rebound.z <= 0.0f) {
			rebound.z = 0.0f;
		}
	} else {
		rebound.z += 0.045f;
		if (rebound.z >= 0.0f) {
			rebound.z = 0.0f;
		}
	}

	//if (position.x <= 25.0f && position.x >= -25.0f) {
	//	position.x += rebound.x;
	//}
	//if (position.z <= 20.0f && position.z >= -20.0f) {
	//	position.z += rebound.z;
	//}
}

void Player::BirthParticle() {

	if (ArmMoveNumber == 0 && AttackMoveNumber == 0 && AttackFlag == false&& Interval <= 80) {
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
void Player::BackPos() {
	position = oldPos;
}

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
	
	move_object1->Update();
}
