#include "Enemy.h"
#include"Collision.h"
#include "BossEnemy.h"
#include<sstream>
#include<iomanip>
#include <Easing.h>
using namespace DirectX;

Enemy::Enemy() {
	model = Model::CreateFromOBJ("chr_sword");
	enemyobj = new Object3d();

}

void Enemy::Initialize() {

	//ƒvƒŒƒCƒ„[
	IsAlive = false;
	IsTimer = 100;
	enemyobj = Object3d::Create();
	enemyobj->SetModel(model);
	enemyobj->SetPosition(pos);
	//enemyobj->SetScale({ 0.5f,0.5f,0.5f });
	texture = Texture::Create(0, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	texture->TextureCreate();
	texture->SetPosition(pos);
	texture->SetRotation({ 90,0,0 });
	texture->SetScale({ 0.2f,0.2f,0.2f });
	collider.radius = rad;
}

void Enemy::Finalize() {
}

void Enemy::Update() {
	assert(player);
	collider.center = XMVectorSet(pos.x, pos.y, pos.z, 1);
	playerpos = player->GetPosition();
	if (!IsAlive) {
		IsTimer--;
		speed = (float)(rand() % 360);
		scale = (float)(rand() % 10 + 10);
	}

	if (IsTimer <= 0) {
		IsAlive = true;
		isMove = false;
		StartPos = pos;
		frame = 0;
		radius = speed * PI / 180.0f;
		circleX = cosf(radius) * scale;
		circleZ = sinf(radius) * scale;
		pos.x = circleX + basePos.x;
		pos.z = circleZ + basePos.z;
		IsTimer = 100;
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
	enemyobj->SetPosition(pos);
	texture->SetPosition(pos);
	rot.y = Ease(In, Quad, 0.5f, rot.y, EndRot.y);
	enemyobj->SetRotation(rot);
	enemyobj->Update();
	texture->Update();
}

void Enemy::Draw() {
	if (IsAlive) {
		Object3d::PreDraw();
		enemyobj->Draw();
	}
	if (IsAlive && !EnemyCatch) {
		Texture::PreDraw();
		texture->Draw();

	}
}

bool Enemy::collideArm() {
	XMFLOAT3 Armpos = player->GetArmPosition();
	float armweight = player->GetArmWeight();
	int armMove = player->GetArmMoveNumber();
	if (IsAlive && armMove >= 1 && !EnemyCatch) {
		if (Collision::SphereCollision(pos.x, pos.y, pos.z, 0.5f, Armpos.x, Armpos.y, Armpos.z, 0.5f) == true) {
			EnemyCatch = true;
			armweight += 1.0f;
			player->SetArmWeight(armweight);
		}
	}
	if (EnemyCatch == true) {
		pos = Armpos;
		return true;
	} else {
		return false;
	}
}

bool Enemy::collidePlayer() {
	if (IsAlive && !EnemyCatch) {
		if (Collision::SphereCollision(pos.x, pos.y, pos.z, 0.5f, playerpos.x, playerpos.y, playerpos.z, 0.5f) == true) {
			IsAlive = 0;
			player->SetHp(player->GetHp() - 1);
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

	pos.x += Check * 0.095f;
	pos.z += Check2 * 0.095f;
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
