#include "Rice.h"
#include"Collision.h"
#include "BossEnemy.h"
#include<sstream>
#include<iomanip>
#include <Easing.h>
#include"ImageManager.h"
using namespace DirectX;

//コンストラクタ
Rice::Rice() {
	model = ModelManager::GetIns()->GetModel(ModelManager::Enemy);
}
//初期化
void Rice::Initialize() {
	//敵
	IsAlive = false;
	IsTimer = 100;
	rot = { 0,90,0 };
	Object3d* object3d_ = new Object3d();
	object3d_ = Object3d::Create();
	object3d_->SetModel(model);
	object3d_->SetPosition(pos);
	object3d_->SetScale(enescale);
	enemyobj.reset(object3d_);
	//テクスチャ
	Texture* texture_ = Texture::Create(ImageManager::enemy, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	texture_->TextureCreate();
	texture_->SetPosition(pos);
	texture_->SetRotation({ 90,0,0 });
	texture_->SetScale({ 0.2f,0.2f,0.2f });
	texture.reset(texture_);
	//拠点
	Texture* net_ = Texture::Create(ImageManager::net, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	net_->TextureCreate();
	net_->SetPosition(pos);
	net_->SetRotation({ 90,0,0 });
	net_->SetScale({ 0.2f,0.2f,0.2f });
	net[0].reset(net_);

	Texture* Smoke = Texture::Create(ImageManager::smoke, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	Smoke->TextureCreate();
	Smoke->SetPosition(pos);
	Smoke->SetRotation({ 90,0,0 });
	Smoke->SetScale({ 0.15f,0.15f,0.15f });
	net[1].reset(Smoke);

	oldpos = pos;
}
//開放
void Rice::Finalize() {
}
//アップデート
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
	player->SetInterval(Interval);
	//rot.y = Ease(In, Quad, 0.5f, rot.y, EndRot.y);
	enemyobj->SetRotation(rot);
	enemyobj->SetScale(enescale);
	enemyobj->Update();
	//texture->SetColor({ 1.0f,0.0,0.0,0.0 });
	texture->Update();
	net[0]->Update();
	net[0]->SetPosition(pos);
	net[1]->Update();
	net[1]->SetPosition(smooth);
	smooth.x = pos.x;
	smooth.y = smooth.y + 0.1f;
	smooth.z = pos.z;
	if (smooth.y > 4.0f || IsAlive) {
		smooth.y = 0;
	}
}

//チュートリアルアップデート
void Rice::Demo(int num) {
	assert(player);
	playerpos = player->GetPosition();
	Interval = player->GetInterval();
	FlashCount = player->GetFlashCount();
	oldpos = pos;
	if (pos.y > 3.0f) {
		pos.y = 3.0f;
	}
	if (!IsAlive) {
		IsTimer--;
		if (IsTimer == 70) {
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
			IsTimer = 100;
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
	XMFLOAT3 playerpos = player->GetPosition();
	//ImGui::Begin("test");
	//ImGui::SliderFloat("pos.y", &pos.y, 360, -360);
	//ImGui::SliderFloat("pos.y", &boundpower.y, 360, -360);
	////ImGui::SliderFloat("rot.y", &rot.y, 360, -360);
	////ImGui::SliderFloat("rot.y", &rot.y, 360, -360);
	////ImGui::SliderFloat("rot.z", &rot.z, 360, -360);
	//////ImGui::Text("pat::%d", pat);
	//////ImGui::Text("AttackC:: %d", AttackC);
	////ImGui::SliderFloat("HP", &BossHP, 40, 0);
	////ImGui::SliderFloat("Defense", &Defense, 2, 0);
	//ImGui::Text("rollMove::%d", IsAlive);
	///*ImGui::Text("action::%d", action);
	//ImGui::Text("active::%d", active);
	//*/
	//
	///*ImGui::Text("shadow::%d", shadow);
	//ImGui::SliderFloat("hit", &hitradius, 1, 0);*/

	//ImGui::End();
	if (IsAlive) {
		Object3d::PreDraw();
		enemyobj->Draw();
	//	Piyopiyo->Draw();
	}
	Texture::PreDraw();
	if (IsAlive && !EnemyCatch && !add) {
		texture->Draw();
	} else if (!IsAlive && IsTimer < 70 && IsTimer != 0) {
		Texture::PreDraw();
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
			pos.y = 0.0f;
			player->SetAddSpeed(1.0f);
			if (armweight <= 6) {
				Audio::GetInstance()->PlayWave("Resources/Sound/catchEnemy.wav", 0.08f);
				armweight += 1.0f;
				EnemyCatch = true;
				if (armweight == 1) {
					savespeed = 35.0;
					savesacale = 1.0f;
				}
				else if (armweight == 2.0f) {
					savespeed = 90.0;
					savesacale = 1.0f;
				}
				else if (armweight == 3.0f) {
					savespeed = 145.0;
					savesacale = 1.0f;
				}
				else if (armweight == 4.0f) {
					savespeed = 200.0;
					savesacale = 1.0f;
				}
				else if (armweight == 5.0f) {
					savespeed = 250.0;
					savesacale = 1.0f;
				}
				else if (armweight == 6.0f) {
					savespeed = 300.0;
					savesacale = 1.0f;
				}
				else if (armweight == 7.0f) {
					savespeed = 350.0;
					savesacale = 1.0f;
				}
			}
			else {
				//IsAlive = false;
				Exp = true;
				RandDeadPower();
				nocatch = true;
			}

			player->SetOldArm(player->GetArmWeight());
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

//敵同士がぶつかったとき(多分)
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
	FlashCount = player->GetFlashCount();
	if (IsAlive && !EnemyCatch && add == false && !Exp && !AttackFlag && !nocatch) {
		if (Collision::SphereCollision(pos.x, pos.y, pos.z, 0.5f, playerpos.x, playerpos.y, playerpos.z, 0.5f) == true) {
			IsAlive = 0;
			if(Interval == 0 && FlashCount == 0){
			player->SetHp(player->GetHp() - 1);
			player->SetCharge(0);
			player->SetRotCount(0);
			Audio::GetInstance()->PlayWave("Resources/Sound/Damage.wav", 0.4f);
			}
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
			//ダメージ量に応じて音が変わる
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
				player->SetOldArm(player->GetArmWeight());
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
				player->SetOldArm(player->GetArmWeight());
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
//クリア用
void Rice::FirstRoll(int Timer) {
	
	if (Timer == 3250) {
		appearance = true;
		IsAlive = true;
		RollMove++;
	}

	if (Timer == 3650 || Timer == 4350 || Timer == 4500) {
		RollMove++;
		rollframe = 0.0f;
	}

	if (Timer == 4500) {
		appearance = true;
		IsAlive = true;
	}
	switch (RollMove) {
	case 1:
		//出現する瞬間
		if (appearance == true) {
			boundpower.y = 0.5;
			enescale = { 0.0f,0.0f,0.0f };
			pos.y = -9.0f;
			pos.x = -15.0f;
			add = true;
			appearance = false;
		}

		//更に加算
		if (add == true) {
			boundpower.y -= 0.02f;
			pos.x += boundpower.x;
			pos.y += boundpower.y;
			pos.z += boundpower.z;
			if (enescale.x <= 1.5) {
				enescale.x += 0.04f;
				enescale.y += 0.04f;
				enescale.z += 0.04f;
			}
		}

		//敵出現完了
		if (add == true && pos.y <= -9.0f) {
			boundpower = { 0.0f,0.0f,0.0f };
			add = false;
			pos.y = -9.0f;
		}
		break;
	case 2:
		afterrot = 450.0f;
		if (rollframe < 1.0f) {
			rollframe += 0.005f;
			break;
		}
		else {
			rollframe = 1.0f;
			break;
		}
	case 3:
		afterrot = 90.0f;
		if (rollframe < 1.0f) {
			rollframe += 0.005f;
			break;
		}
		else {
			rollframe = 1.0f;
			break;
		}
	case 4:
		//出現する瞬間
		if (appearance == true) {
			boundpower.y = 0.5;
			pos.y = -9.0f;
			pos.x = -15.0f;
			add = true;
			appearance = false;
		}

		//更に加算
		if (add == true) {
			boundpower.y -= 0.02f;
			pos.x += boundpower.x;
			pos.y += boundpower.y;
			pos.z += boundpower.z;
			/*	if (enescale.x <= 1.5) {
					enescale.x += 0.04f;
					enescale.y += 0.04f;
					enescale.z += 0.04f;
				}*/
		}

		//敵出現完了
		if (add == true && pos.y <= -9.0f) {
			boundpower = { 0.0f,0.0f,0.0f };
			add = false;
			appearance = true;
			pos.y = -9.0f;
		}
		break;
	}
	rot.y = Ease(In, Quad, rollframe, rot.y, afterrot);
	enemyobj->SetPosition(pos);
	enemyobj->SetRotation(rot);
	enemyobj->SetScale(enescale);
	enemyobj->Update();
}

void Rice::SecondRoll(int Timer) {

	if (Timer == 3350) {
		appearance = true;
		IsAlive = true;
		RollMove++;
	}

	if (Timer == 3750 || Timer == 4250 || Timer == 4520) {
		RollMove++;
		rollframe = 0.0f;
	}

	if (Timer == 4520) {
		appearance = true;
		IsAlive = true;
	}

	switch (RollMove) {
	case 1:
		//出現する瞬間
		if (appearance == true) {
			boundpower.y = 0.5;
			enescale = { 0.0f,0.0f,0.0f };
			pos.y = -9.0f;
			pos.x = -5.0f;
			add = true;
			appearance = false;
		}

		//更に加算
		if (add == true) {
			boundpower.y -= 0.02f;
			pos.x += boundpower.x;
			pos.y += boundpower.y;
			pos.z += boundpower.z;
			if (enescale.x <= 1.5) {
				enescale.x += 0.04f;
				enescale.y += 0.04f;
				enescale.z += 0.04f;
			}
		}

		//敵出現完了
		if (add == true && pos.y <= -9.0f) {
			boundpower = { 0.0f,0.0f,0.0f };
			add = false;
			pos.y = -9.0f;
		}
		break;
	case 2:
		afterrot = 450.0f;
		if (rollframe < 1.0f) {
			rollframe += 0.005f;
			break;
		}
		else {
			rollframe = 1.0f;
			break;
		}
	case 3:
		afterrot = 90.0f;
		if (rollframe < 1.0f) {
			rollframe += 0.005f;
			break;
		}
		else {
			rollframe = 1.0f;
			break;
		}
	case 4:
		//出現する瞬間
		if (appearance == true) {
			boundpower.y = 0.5;
			pos.y = -9.0f;
			pos.x = -5.0f;
			add = true;
			appearance = false;
		}

		//更に加算
		if (add == true) {
			boundpower.y -= 0.02f;
			pos.x += boundpower.x;
			pos.y += boundpower.y;
			pos.z += boundpower.z;
			/*	if (enescale.x <= 1.5) {
					enescale.x += 0.04f;
					enescale.y += 0.04f;
					enescale.z += 0.04f;
				}*/
		}

		//敵出現完了
		if (add == true && pos.y <= -9.0f) {
			boundpower = { 0.0f,0.0f,0.0f };
			add = false;
			appearance = true;
			pos.y = -9.0f;
		}
		break;
	}
	rot.y = Ease(In, Quad, rollframe, rot.y, afterrot);
	enemyobj->SetPosition(pos);
	enemyobj->SetRotation(rot);
	enemyobj->SetScale(enescale);
	enemyobj->Update();
}

void Rice::ThirdRoll(int Timer) {

	if (Timer == 3450) {
		RollMove++;
		IsAlive = true;
		appearance = true;
	}

	if (Timer == 3850 || Timer == 4150 || Timer == 4540) {
		RollMove++;
		rollframe = 0.0f;
	}

	if (Timer == 4540) {
		appearance = true;
		IsAlive = true;
	}



	switch (RollMove) {
	case 1:
		//出現する瞬間
		if (appearance == true) {
			boundpower.y = 0.5;
			enescale = { 0.0f,0.0f,0.0f };
			pos.y = -9.0f;
			pos.x = 5.0f;
			add = true;
			appearance = false;
		}

		//更に加算
		if (add == true) {
			boundpower.y -= 0.02f;
			pos.x += boundpower.x;
			pos.y += boundpower.y;
			pos.z += boundpower.z;
			if (enescale.x <= 1.5) {
				enescale.x += 0.04f;
				enescale.y += 0.04f;
				enescale.z += 0.04f;
			}
		}

		//敵出現完了
		if (add == true && pos.y <= -9.0f) {
			boundpower = { 0.0f,0.0f,0.0f };
			add = false;
			pos.y = -9.0f;
		}
		break;
	case 2:
		afterrot = 450.0f;
		if (rollframe < 1.0f) {
			rollframe += 0.005f;
			break;
		}
		else {
			rollframe = 1.0f;
			break;
		}
	case 3:
		afterrot = 90.0f;
		if (rollframe < 1.0f) {
			rollframe += 0.005f;
			break;
		}
		else {
			rollframe = 1.0f;
			break;
		}
	case 4:
		//出現する瞬間
		if (appearance == true) {
			boundpower.y = 0.5;
			pos.y = -9.0f;
			pos.x = 5.0f;
			add = true;
			appearance = false;
		}

		//更に加算
		if (add == true) {
			boundpower.y -= 0.02f;
			pos.x += boundpower.x;
			pos.y += boundpower.y;
			pos.z += boundpower.z;
			/*	if (enescale.x <= 1.5) {
					enescale.x += 0.04f;
					enescale.y += 0.04f;
					enescale.z += 0.04f;
				}*/
		}

		//敵出現完了
		if (add == true && pos.y <= -9.0f) {
			boundpower = { 0.0f,0.0f,0.0f };
			add = false;
			appearance = true;
			pos.y = -9.0f;
		}
		break;
	}
	rot.y = Ease(In, Quad, rollframe, rot.y, afterrot);
	enemyobj->SetPosition(pos);
	enemyobj->SetRotation(rot);
	enemyobj->SetScale(enescale);
	enemyobj->Update();
}

void Rice::FouthRoll(int Timer) {

	if (Timer == 3550) {
		appearance = true;
		IsAlive = true;
		RollMove++;
	}

	if (Timer == 3950 || Timer == 4050 || Timer == 4560) {
		RollMove++;
		rollframe = 0.0f;
	}

	if (Timer == 4560) {
		appearance = true;
		IsAlive = true;
	}
	switch (RollMove) {
	case 1:
		//出現する瞬間
		if (appearance == true) {
			boundpower.y = 0.5;
			enescale = { 0.0f,0.0f,0.0f };
			pos.y = -9.0f;
			pos.x = 15.0f;
			add = true;
			appearance = false;
		}

		//更に加算
		if (add == true) {
			boundpower.y -= 0.02f;
			pos.x += boundpower.x;
			pos.y += boundpower.y;
			pos.z += boundpower.z;
			if (enescale.x <= 1.5) {
				enescale.x += 0.04f;
				enescale.y += 0.04f;
				enescale.z += 0.04f;
			}
		}

		//敵出現完了
		if (add == true && pos.y <= -9.0f) {
			boundpower = { 0.0f,0.0f,0.0f };
			add = false;
			pos.y = -9.0f;
		}
		break;
	case 2:
		afterrot = 450.0f;
		if (rollframe < 1.0f) {
			rollframe += 0.005f;
			break;
		}
		else {
			rollframe = 1.0f;
			break;
		}
	case 3:
		afterrot = 90.0f;
		if (rollframe < 1.0f) {
			rollframe += 0.005f;
			break;
		}
		else {
			rollframe = 1.0f;
			break;
		}
	case 4:
		//出現する瞬間
		if (appearance == true) {
			boundpower.y = 0.5;
			pos.y = -9.0f;
			pos.x = 15.0f;
			add = true;
			appearance = false;
		}

		//更に加算
		if (add == true) {
			boundpower.y -= 0.02f;
			pos.x += boundpower.x;
			pos.y += boundpower.y;
			pos.z += boundpower.z;
		/*	if (enescale.x <= 1.5) {
				enescale.x += 0.04f;
				enescale.y += 0.04f;
				enescale.z += 0.04f;
			}*/
		}

		//敵出現完了
		if (add == true && pos.y <= -9.0f) {
			boundpower = { 0.0f,0.0f,0.0f };
			add = false;
			appearance = true;
			pos.y = -9.0f;
		}
		break;
	}
	rot.y = Ease(In, Quad, rollframe, rot.y, afterrot);
	enemyobj->SetPosition(pos);
	enemyobj->SetRotation(rot);
	enemyobj->SetScale(enescale);
	enemyobj->Update();
}
