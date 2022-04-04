#include "Enemy.h"
#include"Collision.h"
#include "BossEnemy.h"
#include<sstream>
#include<iomanip>
#include <Easing.h>
using namespace DirectX;

Enemy::Enemy() {
	model = Model::CreateFromOBJ("Enemy");
	enemyobj = new Object3d();
}

void Enemy::Initialize() {
	//敵
	IsAlive = false;
	IsTimer = 200;
	enemyobj = Object3d::Create();
	enemyobj->SetModel(model);
	rot = { 0,90,0 };
	enemyobj->SetPosition(pos);
	enemyobj->SetScale(enescale);
	texture = Texture::Create(0, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	texture->TextureCreate();
	texture->SetPosition(pos);
	texture->SetRotation({ 90,0,0 });
	texture->SetScale({ 0.2f,0.2f,0.2f });
	
	//texture->SetColor({ 1.0f,0.0,0.0,1.0f });
	Restexture = Texture::Create(3, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	Restexture->TextureCreate();
	Restexture->SetPosition(pos);
	Restexture->SetRotation({ 90,0,0 });
	Restexture->SetScale({ 0.2f,0.2f,0.2f });
	collider.radius = rad;
}

void Enemy::Finalize() {
	delete enemyobj;
	delete texture;
	delete Restexture;
}

void Enemy::Update() {
	assert(player);
	collider.center = XMVectorSet(pos.x, pos.y, pos.z, 1);
	playerpos = player->GetPosition();
	Interval = player->GetInterval();
	FlashCount = player->GetFlashCount();
	if (!IsAlive) {
		IsTimer--;
		if (IsTimer == 100) {
			speed = (float)(rand() % 360);
			scale = (float)(rand() % 10 + 10);
			StartPos = pos;
			frame = 0;
			radius = speed * PI / 180.0f;
			circleX = cosf(radius) * scale;
			circleZ = sinf(radius) * scale;
			pos.x = circleX + basePos.x;
			pos.z = circleZ + basePos.z;
		}

		else if (IsTimer == 0) {
			IsAlive = true;
			appearance = true;
			isMove = false;
			IsTimer = 200;
		}
	}

	if (IsAlive && !EnemyCatch && !Exp) {
		if (LockOn()) {
			moveCount = (rand() % 15) + 20;
			isMove = false;
			Follow();
		} else {
			Move();
		}
	}

	//倒したときの演出
	if (bound == true) {
		//enescale = { 0.4f,0.4f,0.4f };
		boundpower.x = (float)(rand() % 4 - 2);
		boundpower.y = (float)(rand() % 3 + 3);
		boundpower.z = (float)(rand() % 4 - 2);
		if (boundpower.x == 0.0f) {
			boundpower.x = 1.0f;
		}

		if (boundpower.z == 0.0f) {
			boundpower.z = 1.0f;
		}
		boundpower.x = boundpower.x / 10;
		boundpower.y = boundpower.y / 10;
		boundpower.z = boundpower.z / 10;
		bound = false;
		add = true;
	}

	//出現する瞬間
	if (appearance == true) {
		boundpower.y = 0.5;
		enescale = { 0.0f,0.0f,0.0f };
		pos.y = -3.0f;
		add = true;
		appearance = false;
	}

	//更に加算
	if (add == true) {
		boundpower.y -= 0.02f;
		pos.x += boundpower.x;
		pos.y += boundpower.y;
		pos.z += boundpower.z;
		if (boundpower.x != 0.0f && boundpower.z != 0.0f) {
			enescale.x -= 0.01f;
			enescale.y -= 0.01f;
			enescale.z -= 0.01f;
		} else {
			if (enescale.x <= 0.7) {
				enescale.x += 0.02f;
				enescale.y += 0.02f;
				enescale.z += 0.02f;
			}
		}
	}

	//演出フラグ終了
	if (enescale.x <= 0.0f && enescale.y <= 0.0f && enescale.z <= 0.0f) {
		add = false;
		boundpower = { 0.0f,0.0f,0.0f };
		pos.y = 0.0f;
		IsAlive = false;
	}

	//敵出現完了
	if (add == true && boundpower.y <= 0.0f && pos.y <= 0.0f && boundpower.x == 0.0f) {
		boundpower = { 0.0f,0.0f,0.0f };
		add = false;
		pos.y = 0.0f;
	}

	collideArm();
	collidePlayer();
	collideAttackArm();
	if (Exp == true) {
		DeadEnemy();
	}
	enemyobj->SetPosition(pos);
	texture->SetPosition(pos);
	Restexture->SetPosition(pos);
	player->SetInterval(Interval);
	rot.y = Ease(In, Quad, 0.5f, rot.y, EndRot.y);
	enemyobj->SetRotation(rot);
	enemyobj->SetScale(enescale);
	enemyobj->Update();
	//texture->SetColor({ 1.0f,0.0,0.0,0.0 });
	texture->Update();
	Restexture->Update();
}

//描画
void Enemy::Draw() {

	//ImGui::Begin("test");
	//if (ImGui::TreeNode("Debug")) {
	//	if (ImGui::TreeNode("Enemy")) {
	//		float A = (float)Check;
	//		ImGui::SliderFloat("Check", &A, 50, -50);
	//		//ImGui::Text("%d", DrawExp);
	//		ImGui::Unindent();
	//		ImGui::TreePop();
	//	}
	//	ImGui::TreePop();
	//}
	//ImGui::End();

	if (IsAlive) {
		Object3d::PreDraw();
		enemyobj->Draw();
	}
	Texture::PreDraw();
	if (IsAlive && !EnemyCatch && !add) {
		texture->Draw();
	} else if (!IsAlive && IsTimer <= 100 && IsTimer != 0) {
		Restexture->Draw();
	}
}

//敵をキャッチ
bool Enemy::collideArm() {
	XMFLOAT3 Armpos = player->GetArmPosition();
	float armweight = player->GetArmWeight();
	float armspeed = player->GetArmSpeed();
	float armscale = player->GetArmScale();
	int armMove = player->GetArmMoveNumber();
	if (IsAlive && armMove >= 1 && !EnemyCatch && add == false && !Exp) {
		if (Collision::SphereCollision(pos.x, pos.y, pos.z, 0.5f, Armpos.x, Armpos.y, Armpos.z, 0.5f) == true) {
			EnemyCatch = true;
			armweight += 1.0f;
			if (armweight == 1) {
				savespeed = 5.0;
				savesacale = 1.0f;
			} else if (armweight == 2.0f) {
				savespeed = -5.0;
				savesacale = 1.0f;
			} else if (armweight == 3.0f) {
				savespeed = 5.0;
				savesacale = 1.5f;
			} else if (armweight == 4.0f) {
				savespeed = -5.0;
				savesacale = 1.5f;
			} else if (armweight == 5.0f) {
				savespeed = 9.0;
				savesacale = 1.25f;
				pos.y = 0.5f;
			} else if (armweight == 6.0f) {
				savespeed = -9.0;
				savesacale = 1.25f;
				pos.y = 0.5f;
			} else if (armweight == 7.0f) {
				savespeed = 0.0;
				savesacale = 1.25f;
				pos.y = 1.0f;
			}
			player->SetArmWeight(armweight);
		}
	}
	if (EnemyCatch == true) {
		//enescale = { 0.4f,0.4f,0.4f };
		speed = armspeed + savespeed;
		scale = armscale + savesacale;
		return true;
	} else {
		return false;
	}
}

//プレイヤーがダメージを食らう
bool Enemy::collidePlayer() {
	if (IsAlive && !EnemyCatch && FlashCount == 0 && add == false && !Exp) {
		if (Collision::SphereCollision(pos.x, pos.y, pos.z, 0.5f, playerpos.x, playerpos.y, playerpos.z, 0.5f) == true) {
			IsAlive = 0;
			player->SetHp(player->GetHp() - 1);
			player->SetDamageFlag(true);
			Interval = 20;
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

//敵の当たり判定
bool Enemy::collideAttackArm() {
	XMFLOAT3 Armpos = player->GetArmPosition();
	bool attackflag = player->GetAttackFlag();
	float armweight = player->GetArmWeight();
	if (IsAlive && !EnemyCatch && attackflag && !Exp) {
		if (Collision::SphereCollision(pos.x, pos.y, pos.z, 0.5f, Armpos.x, Armpos.y, Armpos.z, 0.5f) == true) {
			Exp = true;
			RandDeadPower();
			player->SetAttackFlag(false);
			if (armweight <= 3) {
				Audio::GetInstance()->PlayWave("Resources/Sound/strongL1.wav", 0.4f);
			} else if (armweight > 3 && armweight <= 6) {
				Audio::GetInstance()->PlayWave("Resources/Sound/strongL2.wav", 0.4f);
			} else if (armweight >= 7) {
				Audio::GetInstance()->PlayWave("Resources/Sound/strongL3.wav", 0.4f);
			}
			if (armweight != 0.0f) {//持ってる方
				//enescale = { 0.4f,0.4f,0.4f };
				armweight = 0.0f;
				player->SetArmWeight(armweight);
			}
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

//敵がプレイヤーの近くにいるか
bool Enemy::LockOn() {
	if (Collision::CircleCollision(playerpos.x, playerpos.z, 5.0,
		pos.x, pos.z, 3.0)) {
		return true;
	} else {
		return false;
	}
}

//敵追従
void Enemy::Follow() {
	XMFLOAT3 position{};
	position.x = (playerpos.x - pos.x);
	position.z = (playerpos.z - pos.z);
	posR = sqrt(pow(position.x, 2) + pow(position.z, 2));
	Check = position.x / posR;
	Check2 = position.z / posR;
	if (Check>0.2f) {
		if (Check2>0.2f) {
			EndRot.y = -45;

		} else if (Check2 < -0.2f) {
			EndRot.y = 45;
		} else {
			EndRot.y = 0;
		}
	} else if(Check < -0.2f){
		if (Check2 > 0.2f) {
			EndRot.y = 225;
		} else if (Check2 < -0.2f) {
			EndRot.y = 135;
		} else {
			EndRot.y = 180;
		}
	}
	pos.x += (float)Check * 0.095f;
	pos.z += (float)Check2 * 0.095f;
}

//敵が動く
void Enemy::Move() {
	if (pos.z > z_max) {
		pos.z = z_max;
	}
	if (pos.z < z_min) {
		pos.z = z_min;
	}
	if (pos.x > x_max) {
		pos.x = x_max;
	}
	if (pos.x < x_min) {
		pos.x = x_min;
	}
	if (EndPos.z > z_max) {
		EndPos.z = z_max;
	}
	if (EndPos.z < z_min) {
		EndPos.z = z_min;
	}
	if (EndPos.x > x_max) {
		EndPos.x = x_max;
	}
	if (EndPos.x < x_min) {
		EndPos.x = x_min;
	}


	if (moveCount < 0 && !isMove) {
		StartPos = pos;
		if (dir % 4 == 0) {
			if (pos.x < x_max) {
				EndPos.x = StartPos.x + 2.5f;
			} else {
				EndPos.x = StartPos.x - 2.5f;
			}
			zmove = false;
		} else if (dir % 4 == 1) {
			if (pos.x > x_min) {
				EndPos.x = StartPos.x - 2.5f;
			} else {
				EndPos.x = StartPos.x + 2.5f;
			}
			zmove = false;
		} else if (dir % 4 == 2) {
			if (pos.z > z_min) {
				EndPos.z = StartPos.z - 2.5f;
			} else {
				EndPos.z = StartPos.z + 2.5f;

			}
			zmove = true;
		} else {
			if (pos.z > z_max) {
				EndPos.z = StartPos.z + 2.5f;
			} else {
				EndPos.z = StartPos.z - 2.5f;
			}
			zmove = true;
		}
		frame = 0;
		isMove = true;
	} else {
		moveCount--;
		dir = (rand() % 40);
	}
	if (isMove) {
		if (frame <= 1.0f) {
			frame += 0.01f;
		} else {
			frame = 1.0f;
			moveCount = (rand() % 30) + 30;
			dir = 0;
			isMove = false;
		}
		if (zmove) {
			if (pos.z < EndPos.z) {
				EndRot.y = 270;
			} else if (pos.z > EndPos.z) {
				EndRot.y = 90;
			} /*else {
				EndRot.y = rot.y;
			}*/
			pos.z = Ease(In, Quad, frame, pos.z, EndPos.z);
		} else {
			if (pos.x < EndPos.x) {
				EndRot.y = 360;
			} else 	if (pos.x > EndPos.x) {
				EndRot.y = 180;
			} /*else {
				EndRot.y = rot.y;
			}*/
			pos.x = Ease(In, Quad, frame, pos.x, EndPos.x);
		}
		enemyobj->SetPosition(pos);

	}
}

//敵の位置を腕と同じにする
void Enemy::SetEnemy() {
	float armweight = player->GetArmWeight();
	XMFLOAT3 plapos = player->GetPosition();
	if (EnemyCatch == true) {
		radius = speed * PI / 180.0f;
		circleX = cosf(radius) * scale;
		circleZ = sinf(radius) * scale;
		pos.x = circleX + plapos.x;
		pos.z = circleZ + plapos.z;
	}
}

//敵が死んだときの演出
void Enemy::DeadEnemy() {
	Deadbound.y -= 0.02f;
	pos.y += Deadbound.y;
	if (pos.y > 0.0f) {
		pos.x += Deadbound.x;
		pos.z += Deadbound.z;
	}
	else{
		pos.y = 0.0f;
	}

	if (pos.y == 0.0f) {
		enescale.x -= 0.01f;
		enescale.y -= 0.01f;
		enescale.z -= 0.01f;
		if (enescale.x <= 0.0f && enescale.y <= 0.0f && enescale.z <= 0.0f) {
			DrawExp = true;
			Exp = false;
			IsAlive = false;
		}
	}
}

void Enemy::RandDeadPower() {
	Deadbound.x = (float)(rand() % 4 - 2);
	Deadbound.y = 5;
	Deadbound.z = (float)(rand() % 4 - 2);
	Deadbound.x = Deadbound.x / 10;
	Deadbound.y = Deadbound.y / 10;
	Deadbound.z = Deadbound.z / 10;
}