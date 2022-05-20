#include "Rice.h"
#include"Collision.h"
#include "BossEnemy.h"
#include<sstream>
#include<iomanip>
#include <Easing.h>
#include"ImageManager.h"
using namespace DirectX;

Rice::Rice() {
	model = ModelManager::GetIns()->GetModel(ModelManager::Enemy);
	enemyobj = new Object3d();
	Piyopiyo = new Object3d();
}

void Rice::Initialize() {
	//敵
	IsAlive = false;
	IsTimer = 200;
	enemyobj = Object3d::Create();
	enemyobj->SetModel(model);
	rot = { 0,90,0 };
	enemyobj->SetPosition(pos);
	enemyobj->SetScale(enescale);
	texture = Texture::Create(ImageManager::enemy, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	texture->TextureCreate();
	texture->SetPosition(pos);
	texture->SetRotation({ 90,0,0 });
	texture->SetScale({ 0.2f,0.2f,0.2f });
	oldpos = pos;
	Piyopiyo = Object3d::Create();
	Piyopiyo->SetModel(ModelManager::GetIns()->GetModel(ModelManager::Piyopiyo));
	Piyopiyo->SetPosition({ pos.x,pos.y + 2.0f,pos.z });
	Piyopiyo->SetScale({1.0f, 2.0f, 2.0f});
	Piyopiyo->SetRotation({ 60,0,0 });
	//texture->SetColor({ 1.0f,0.0,0.0,1.0f });
	Restexture = Texture::Create(ImageManager::Resporn, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	Restexture->TextureCreate();
	Restexture->SetPosition(pos);
	Restexture->SetRotation({ 90,0,0 });
	Restexture->SetScale({ 0.2f,0.2f,0.2f });
	net[0] = Texture::Create(ImageManager::net, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	net[0]->TextureCreate();
	net[1] = Texture::Create(ImageManager::effect3, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	net[1]->TextureCreate();
	net[0]->SetPosition(pos);
	net[0]->SetRotation({ 90,0,0 });
	net[0]->SetScale({ 0.2f,0.2f,0.2f });

	net[1]->SetPosition(pos);
	net[1]->SetRotation({ 90,0,0 });
	net[1]->SetScale({ 0.15f,0.15f,0.15f });

}

void Rice::Finalize() {
	delete enemyobj;
	delete texture;
	delete net[0];
	delete net[1];
	delete Restexture;
}

void Rice::Update() {
	assert(player);
	playerpos = player->GetPosition();
	Interval = player->GetInterval();
	FlashCount = player->GetFlashCount();
	oldpos = pos;
	if (pos.y > 3.0f) {
		pos.y = 3.0f;
	}
	if (hit && IsAlive && !EnemyCatch && !Exp) {
		if (frame < 0.4f) {
			speed_y2 = 1.5f / 20.0f;
		}
		Rebound();
	}
	if (IsAlive && !EnemyCatch && !Exp) {
		Back();
		if (LockOn()) {
			moveCount = (rand() % 15) + 20;
			isMove = false;
			followed = true;
			//if (pos.y>!1) {
			//}
		}
		if (!followed && !LockOn()) {
			rot.y = (float)(dir-90);// *(XM_PI / 180.0f);
			speed_y = 3.0f / 20.0f;
			if (pos.y > 0) {
				pos.y -= speed_y;
				start = false;
			} else {
				pos.y = 0;
				start = true;
			}
			if (followed) {
				if (rot.y < -90) {
					dir = (int)rot.y + 360 + 90;
					rot.y = (dir)-90.0f;// *(XM_PI / 180.0f);
				} else {
					dir = (int)rot.y + 90;
					rot.y = (dir)-90.0f;// *(XM_PI / 180.0f);
				}
				followed = false;
			}
			Move();
		}
		if (followed) {
			XMFLOAT3 position{};
			position.x = (playerpos.x - pos.x);
			position.z = (playerpos.z - pos.z);
			pos.y += speed_y;
			speed_y -= gravity;
			rot.y = (atan2(position.x, position.z) * (180.0f / XM_PI)) - 90;// *(XM_PI / 180.0f);
			if (pos.y < 0) {
				pos.y = 0;
				speed_y = 0;
				Follow();
			}
			// 地面に当たったら跳ね返るように
			//enemyobj->SetPosition(pos);
		}
	}
	Reborn();
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
			enescale.x -= 0.02f;
			enescale.y -= 0.02f;
			enescale.z -= 0.02f;
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
	if (hit&&IsAlive && !EnemyCatch && !Exp) {
		Rebound();
	}
	collideArm();
	
	collidePlayer();
	//collideAttackArm();
	SetEnemy();
	if (Exp == true) {
		DeadEnemy();
	}
	if (pos.z > z_max) { pos.z = z_max; }
	if (pos.z < z_min) { pos.z = z_min; }
	if (pos.x > x_max) { pos.x = x_max; }
	if (pos.x < x_min) { pos.x = x_min; }
	enemyobj->SetPosition(pos);
	texture->SetPosition({ pos.x,0,pos.z });
	Restexture->SetPosition(pos);
	player->SetInterval(Interval);
	//rot.y = Ease(In, Quad, 0.5f, rot.y, EndRot.y);
	enemyobj->SetRotation(rot);
	enemyobj->SetScale(enescale);
	enemyobj->Update();
	//texture->SetColor({ 1.0f,0.0,0.0,0.0 });
	texture->Update();
	Restexture->Update();
}

void Rice::Demo(int num) {
	assert(player);
	Piyopiyo->SetPosition({ pos.x,pos.y + 2.0f,pos.z });
	Piyopiyo->Update();
	playerpos = player->GetPosition();
	Interval = player->GetInterval();
	FlashCount = player->GetFlashCount();
	oldpos = pos;
	if (pos.y > 3.0f) {
		pos.y = 3.0f;
	}
	if (!IsAlive) {
		IsTimer--;
		if (IsTimer == 100) {
			speed = (float)num* 60;
			scale = 14;
			StartPos = pos;
			frame = 0;
			radius = speed * PI / 180.0f;
			circleX = cosf(radius) * scale;
			circleZ = sinf(radius) * scale;
			pos.x = circleX + basePos.x;
			pos.z = circleZ + basePos.z;
			dir = 180;
			rot.y = (float)dir-90;// *(XM_PI / 180.0f);
			enemyobj->SetRotation(rot);
			enemyobj->SetPosition(pos);
		} else if (IsTimer == 0) {
			respawn = false;
			pos.y += speed_y;
			speed_y -= gravity;
			start = false;
			IsAlive = true;
			appearance = true;
			isMove = false;
			followed = false;
			IsTimer = 200;
		}
	}	//倒したときの演出
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
			enescale.x -= 0.02f;
			enescale.y -= 0.02f;
			enescale.z -= 0.02f;
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
	//collideAttackArm();
	SetEnemy();
	if (Exp == true) {
		DeadEnemy();
	}
	if (pos.z > z_max) { pos.z = z_max; }
	if (pos.z < z_min) { pos.z = z_min; }
	if (pos.x > x_max) { pos.x = x_max; }
	if (pos.x < x_min) { pos.x = x_min; }
	enemyobj->SetPosition(pos);
	texture->SetPosition({ pos.x,0,pos.z });
	Restexture->SetPosition(pos);
	player->SetInterval(Interval);
	enemyobj->SetRotation(rot);
	enemyobj->SetScale(enescale);
	enemyobj->Update();
	texture->Update();
	net[0]->Update();
	net[0]->SetPosition(pos);
	net[1]->Update();
	net[1]->SetPosition(smooth);
	smooth.x = pos.x;
	smooth.y = smooth.y + 0.1f;
	smooth.z = pos.z;
	if (smooth.y > 4.0f||IsAlive) {
		smooth.y =0;
	}
}

//描画
void Rice::Draw() {
	if (IsAlive) {
		Object3d::PreDraw();
		enemyobj->Draw();
	//	Piyopiyo->Draw();
	}
	Texture::PreDraw();
	if (IsAlive && !EnemyCatch && !add) {
		texture->Draw();
	} else if (!IsAlive && IsTimer <= 100 && IsTimer != 0) {
		Texture::PreDraw();
		Restexture->Draw();
		net[0]->Draw();
		net[1]->Draw();
	}
}

//敵をキャッチ
bool Rice::collideArm() {
	XMFLOAT3 Armpos = player->GetPosition();
	float armweight = player->GetArmWeight();
	float armspeed = player->GetArmSpeed();
	float armscale = player->GetArmScale();
	bool AttackFlag = player->GetAttackFlag();
	if (IsAlive && AttackFlag && !EnemyCatch && add == false && !Exp) {
		if (Collision::SphereCollision(pos.x, pos.y, pos.z, 0.8f, Armpos.x, Armpos.y, Armpos.z, 0.8f) == true) {
			EnemyCatch = true;
			armweight += 1.0f;
			pos.y = 0.0f;
			player->SetAddSpeed(1.0f);
			if (armweight == 1) {
				savespeed = 35.0;
				savesacale = 1.0f;
			} else if (armweight == 2.0f) {
				savespeed = 90.0;
				savesacale = 1.0f;
			} else if (armweight == 3.0f) {
				savespeed = 145.0;
				savesacale = 1.0f;
			} else if (armweight == 4.0f) {
				savespeed = 200.0;
				savesacale = 1.0f;
			} else if (armweight == 5.0f) {
				savespeed = 250.0;
				savesacale = 1.0f;
				pos.y = 0.5f;
			} else if (armweight == 6.0f) {
				savespeed = 300.0;
				savesacale = 1.0f;
			} else if (armweight == 7.0f) {
				savespeed = 350.0;
				savesacale = 1.0f;
			}
			player->SetArmWeight(armweight);
			
		}
	}
	if (EnemyCatch == true) {
		rot.y -= (rand()%3)+1;
		//enescale = { 0.4f,0.4f,0.4f };
		speed = armspeed + savespeed;
		scale = armscale + savesacale;
		return true;
	} else {
		return false;
	}
}

void Rice::Rebound() {
	XMFLOAT3 enepos = exP;
	XMFLOAT3 distance{};
	if (isMove) {
		moveCount = (rand() % 120) + 30;
		rot.y = (float)dir-90;// *(XM_PI / 180.0f);
		frame = 0.5f;
		isMove = false;
	}
	if (followed) {
		if (rot.y < -90) {
			dir = (int)rot.y + 360 + 90;
			rot.y = (float)dir-90;// *(XM_PI / 180.0f);
		} else {
			dir = (int)rot.y + 90;
			rot.y = (float)dir-90;// *(XM_PI / 180.0f);
		}
		followed = false;
	}
	if (frame >= 1.0f&& !stun) {
		moveCount = (rand() % 60) + 60;
		frame = 0.0f;
		followed = false;
		isMove = false;
		stun = true;
	} else {
		frame += 0.05f;
		distance.x = pos.x - enepos.x;
		distance.z = pos.z - enepos.z;

		vel.x = sin(atan2f(distance.x, distance.z)) * 0.05f;
		vel.y = cos(atan2f(distance.x, distance.z)) * 0.05f;
		pos.x -= vel.x;
		pos.y += speed_y2;
		speed_y2 -= gravity2;
		pos.z += vel.y;
	}
	if (stun) {
		if (frame >= 1.0f) {
			frame = 0.0f;
			hit = false;
			stun = false;
		} else {
			frame += 0.01f;
		}
	}
	enemyobj->SetPosition(pos);

}

//プレイヤーがダメージを食らう
bool Rice::collidePlayer() {
	bool AttackFlag = player->GetAttackFlag();
	if (IsAlive && !EnemyCatch && FlashCount == 0 && add == false && !Exp && Interval == 0 && !AttackFlag) {
		if (Collision::SphereCollision(pos.x, pos.y, pos.z, 0.5f, playerpos.x, playerpos.y, playerpos.z, 0.5f) == true) {
			IsAlive = 0;
			player->SetHp(player->GetHp() - 1);
			Audio::GetInstance()->PlayWave("Resources/Sound/Damage.wav", 0.4f);
			if (player->GetAttackFlag() == false) {
				
			}
			Interval = 100;
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

//敵の当たり判定
bool Rice::collideAttackArm() {
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

//回転が止まった時離れる
bool Rice::BoundEnemy() {
	XMFLOAT3 plapos = player->GetPosition();
	bool attackflag = player->GetAttackFlag();
	float armweight = player->GetArmWeight();
	if (IsAlive && EnemyCatch && !attackflag) {
		if (Collision::SphereCollision(pos.x, pos.y, pos.z, 0.8f, plapos.x, plapos.y, plapos.z, 0.8f) == true) {
			IsAlive = false;
			if (armweight != 0.0f) {//持ってる方
				//enescale = { 0.4f,0.4f,0.4f };
				armweight = 0.0f;
				player->SetArmWeight(armweight);
			}
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

//敵がプレイヤーの近くにいるか
bool Rice::LockOn() {
	if (Collision::CircleCollision(playerpos.x, playerpos.z, 5.0,
		pos.x, pos.z, 5.0)) {
		return true;
	} else {
		return false;
	}
}

//敵が動く
void Rice::Move() {
	if (moveCount <= 0 && !isMove) {
		isMove = true;
	}
	if (moveCount > 0) {
		moveCount--;
		if (moveCount % 2 == 1) {
			dir += dirVel;
		}
		dir %= 360;
	}
	if (isMove) {
		if (frame >= 1.0f) {
			moveCount = (rand() % 60) + 60;
			frame = 0.0f;
			isMove = false;
			dirVel *= -1;
		} else {
			frame += 0.05f;
		}
		vel.x = sin(-dir * (XM_PI / 180.0f)) * 0.13f;
		vel.y = cos(-dir * (XM_PI / 180.0f)) * 0.13f;

		pos.x -= vel.x;
		pos.z += vel.y;
		enemyobj->SetPosition(pos);
	}
}



