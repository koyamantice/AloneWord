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

	//“G
	IsAlive = false;
	IsTimer = 200;
	enemyobj = Object3d::Create();
	enemyobj->SetModel(model);
	enemyobj->SetPosition(pos);
	enemyobj->SetScale(enescale);
	texture = Texture::Create(0, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	texture->TextureCreate();
	texture->SetPosition(pos);
	texture->SetRotation({ 90,0,0 });
	texture->SetScale({ 0.2f,0.2f,0.2f });
	Restexture = Texture::Create(3, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	Restexture->TextureCreate();
	Restexture->SetPosition(pos);
	Restexture->SetRotation({ 90,0,0 });
	Restexture->SetScale({ 0.2f,0.2f,0.2f });
	collider.radius = rad;
}

void Enemy::Finalize() {
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
			isMove = false;

			IsTimer = 200;
		}
	}

	collideArm();
	collidePlayer();
	collideAttackArm();
	if (IsAlive && !EnemyCatch) {
		if (LockOn()) {
			moveCount = (rand() % 15) + 20;
			isMove = false;
			Follow();
		} else {
			Move();
		}
	}

	if (bound == true) {
		boundpower.x = (float)(rand() % 4 - 2);
		boundpower.y = (float)(rand() % 6);
		boundpower.z = (float)(rand() % 4 - 2);
		boundpower.x = boundpower.x / 10;
		boundpower.y = boundpower.y / 10;
		boundpower.z = boundpower.z / 10;
		bound = false;
		add = true;
	}

	if (add == true) {
		boundpower.y -= 0.02;
		pos.x += boundpower.x;
		pos.y += boundpower.y;
		pos.z += boundpower.z;
		enescale.x -= 0.008f;
		enescale.y -= 0.008f;
		enescale.z -= 0.008f;
	}

	if (enescale.x <= 0.0f && enescale.y <= 0.0f && enescale.z <= 0.0f) {
		add = false;
		enescale = { 0.4f,0.4f,0.4f };
		pos.y = 0.0f;
		//boundpower = { 0.0f,0.0f,0.0f };
		IsAlive = false;
	}

	//if (boundpower.y >= -10.0f) {
	//	boundpower.y -= 0.2;
	//	pos.x += boundpower.x;
	//	pos.y += boundpower.y;
	//	pos.z += boundpower.z;
	//}

	//if (pos.y < -5.0f) {
	//	pos.y = 0.0f;
	//	IsAlive = false;
	//}

	enemyobj->SetPosition(pos);
	texture->SetPosition(pos);
	Restexture->SetPosition(pos);
	player->SetInterval(Interval);
	rot.y = Ease(In, Quad, 0.5f, rot.y, EndRot.y);
	enemyobj->SetRotation(rot);
	enemyobj->SetScale(enescale);
	enemyobj->Update();
	texture->Update();
	Restexture->Update();
}

void Enemy::Draw() {
	ImGui::Begin("test");
	if (ImGui::TreeNode("Debug")) {
		if (ImGui::TreeNode("Enemy")) {
			ImGui::SliderFloat("bound.x", &boundpower.x, 50, -50);
			ImGui::SliderFloat("bound.y", &boundpower.y, 50, -50);
			ImGui::SliderFloat("bound.z", &boundpower.z, 50, -50);
			ImGui::SliderFloat("pos.x", &pos.x, 50, -50);
			ImGui::SliderFloat("pos.y", &pos.y, 50, -50);
			ImGui::SliderFloat("pos.z", &pos.z, 50, -50);
			ImGui::Text("%d", IsAlive);
			ImGui::Text("%d", bound);
			ImGui::Unindent();
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
	ImGui::End();
	if (IsAlive) {
		Object3d::PreDraw();
		enemyobj->Draw();
	}
	Texture::PreDraw();
	if (IsAlive && !EnemyCatch && !add ) {	
		texture->Draw();
	}
	else if (!IsAlive && IsTimer <= 100 && IsTimer != 0) {
		Restexture->Draw();
	}

}

bool Enemy::collideArm() {
	XMFLOAT3 Armpos = player->GetArmPosition();
	float armweight = player->GetArmWeight();
	float armspeed = player->GetArmSpeed();
	float armscale = player->GetArmScale();
	int armMove = player->GetArmMoveNumber();
	if (IsAlive && armMove >= 1 && !EnemyCatch) {
		if (Collision::SphereCollision(pos.x, pos.y, pos.z, 0.5f, Armpos.x, Armpos.y, Armpos.z, 0.5f) == true) {
			EnemyCatch = true;
			armweight += 1.0f;
			if (armweight == 1) {
				savespeed = 5.0;
				savesacale = 1.0f;
			}
			else if(armweight == 2.0f){
				savespeed =-5.0;
				savesacale = 1.0f;
			}
			else if (armweight == 3.0f) {
				savespeed = 5.0;
				savesacale = 1.5f;
			}
			else if (armweight == 4.0f) {
				savespeed = -5.0;
				savesacale = 1.5f;
			}
			else if (armweight == 5.0f) {
				savespeed = 0;
				savesacale = 1.25f;
				pos.y = 0.5f;
			} 
			else if (armweight == 6.0f) {
				savespeed = -7.5;
				savesacale = 1.0f;
			}
			else if (armweight == 7.0f) {
				savespeed = 7.5;
				savesacale = 1.0f;
			}
			player->SetArmWeight(armweight);
		}
	}
	if (EnemyCatch == true) {
			speed = armspeed + savespeed;
			scale = armscale + savesacale;
		return true;
	} else {
		return false;
	}
}

bool Enemy::collidePlayer() {
	if (IsAlive && !EnemyCatch && FlashCount == 0 && add == false) {
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

bool Enemy::collideAttackArm() {
	XMFLOAT3 Armpos = player->GetArmPosition();
	bool attackflag = player->GetAttackFlag();
	float armweight = player->GetArmWeight();
	if (IsAlive && !EnemyCatch && attackflag) {
		if (Collision::SphereCollision(pos.x, pos.y, pos.z, 0.5f, Armpos.x, Armpos.y, Armpos.z, 0.5f) == true) {
			IsAlive = 0;//Ž‚½‚ê‚Ä‚Ä‚È‚¢•û
			player->SetAttackFlag(false);
			if (armweight <= 3) {
				Audio::GetInstance()->PlayWave("Resources/Sound/strongL1.wav", 0.4f);
			}
			else if (armweight > 3 && armweight <= 6) {
				Audio::GetInstance()->PlayWave("Resources/Sound/strongL2.wav", 0.4f);
			}
			else if (armweight >= 7) {
				Audio::GetInstance()->PlayWave("Resources/Sound/strongL3.wav", 0.4f);
			}
			if (armweight != 0.0f) {//Ž‚Á‚Ä‚é•û
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

bool Enemy::LockOn() {
	if (Collision::CircleCollision(playerpos.x, playerpos.z, 5.0,
		pos.x, pos.z, 3.0)) {
		return true;
	} else {
		return false;
	}
}

void Enemy::Follow() {
	XMFLOAT3 position{};
	position.x = (playerpos.x - pos.x);
	position.z = (playerpos.z - pos.z);
	double posR = sqrt(pow(pos.x, 2) + pow(pos.z, 2));
	double Check = position.x / posR;
	double Check2 = position.z / posR;

	pos.x += (float)Check * 0.095f;
	pos.z += (float)Check2 * 0.095f;
}

void Enemy::Move() {
	if (pos.z>z_max) {
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
				EndRot.y = 0;
			} else if (pos.z > EndPos.z) {
				EndRot.y = 180;
			} else {
				EndRot.y = rot.y;
			}
			pos.z = Ease(In, Quad, frame, pos.z, EndPos.z);
		} else {
			pos.x = Ease(In, Quad, frame, pos.x, EndPos.x);
			if (pos.x < EndPos.x) {
				EndRot.y = 90;
			} else 	if (pos.x > EndPos.x) {
				EndRot.y = 270;
			} else {
				EndRot.y = rot.y;
			}
		}
		enemyobj->SetPosition(pos);

	}
}

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
