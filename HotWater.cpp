#include "HotWater.h"
#include "ImageManager.h"
#include "ModelManager.h"
#include "Collision.h"
#include <Easing.h>
#include <Audio.h>

//初期化
void HotWater::Init() {
	water = new Object3d();
	water = Object3d::Create();
	water->SetModel(ModelManager::GetIns()->GetModel(ModelManager::Water));
	water->SetPosition({ 0.0f,-50.0f,0.0f });
	water->SetScale({ 3.0f,3.0f,3.0f });

	hot = Texture::Create(ImageManager::water, { 0,0,0 }, { 1,1,1 }, { 1,1,1,1 });
	hot->TextureCreate();
	hot->SetPosition({ 0.0f,-50.0f,0.0f });
	hot->SetRotation({ 90.0f,0, 0 });
	hot->SetScale({ 0.1f,0.1f,0.1f });
}

//更新
void HotWater::Upda() {
	water->Update();
	hot->Update();
	if (IsAlive) {
		if (watersca.x <= 4.0f) {
			watersca.x += 0.1f;
			watersca.y += 0.1f;
			watersca.z += 0.1f;
		}
		if (action == 1) {
			if (onGround) {
				if (shrink) {
					if (frame < 1.0f) {
						frame += 0.0018f;
					}
					else {
						frame = 0;
					}
					sca = {
					Ease(In,Quint,frame,(float)sca.x,(float)0),
					Ease(In,Quint,frame,(float)sca.y,(float)0),
					Ease(In,Quint,frame,(float)sca.z,(float)0),
					};
				}
				else {
					if (sca.x < 0.3f) {
						sca.x += 0.02f;
						sca.y += 0.02f;
						sca.z += 0.02f;
					}
					else {
						if (!shrink) {
							shrink = true;
						}
					}
				}
				if (sca.x > 0.15f) {
					Collide();
				}
			}
			else {
				pos.x += vel.x;
				pos.y += vel.y;
				pos.z += vel.z;
				vel.y -= 0.01f;
				water->SetPosition(pos);
				if (pos.y < -0.2f) {
					//Audio::GetInstance()->PlayWave("Resources/Sound/GreenTea.wav", 0.2f);
					onGround = true;
					hot->SetPosition(pos);
				}
			}
			if (sca.x <= 0.0f) {
				IsAlive = false;
				shrink = false;
				onGround = false;
				frame = 0;
				sca = { 0.1f,0.1f,0.1f };
				water->SetPosition({ 0.0f,-50.0f,0.0f });
				hot->SetPosition({ 0.0f,-50.0f,0.0f });
			}
			hot->SetScale(sca);
		}
		else if (action == 2) {
			if (!onGround) {
				followTimer++;
				XMFLOAT3 plapos = player->GetPosition();
				XMFLOAT3 position{};
				position.x = ((plapos.x - 1.5f) - pos.x);
				position.z = (plapos.z - pos.z);
				//NextP.x -= sin(-atan2f(position.x, position.z)) * 0.2251f;
				//NextP.z += cos(-atan2f(position.x, position.z)) * 0.2251f;
				vel.x = sin(-atan2f(position.x, position.z)) * 0.17f;
				vel.y = cos(-atan2f(position.x, position.z)) * 0.17f;
				pos.x -= vel.x;
				pos.z += vel.y;
				water->SetPosition(pos);
				if (followTimer == 150) {
					onGround = true;
					hot->SetPosition(pos);
				}
			}
			else {
				if (shrink) {
					if (frame < 1.0f) {
						frame += 0.0018f;
					}
					else {
						frame = 0;
					}
					sca = {
					Ease(In,Quint,frame,(float)sca.x,(float)0),
					Ease(In,Quint,frame,(float)sca.y,(float)0),
					Ease(In,Quint,frame,(float)sca.z,(float)0),
					};
				}
				else {
					if (sca.x < 0.3f) {
						sca.x += 0.02f;
						sca.y += 0.02f;
						sca.z += 0.02f;
					}
					else {
						if (!shrink) {
							shrink = true;
						}
					}
				}
				if (sca.x > 0.15f) {
					Collide();
				}
				/*else {
					IsAlive = false;
					shrink = false;
					onGround = false;
					frame = 0;
					sca = { 0.1f,0.1f,0.1f };
					hot->SetPosition({ 0.0f,-50.0f,0.0f });
				}*/
			}
			if (sca.x <= 0.0f) {
				IsAlive = false;
				shrink = false;
				onGround = false;
				frame = 0;
				sca = { 0.1f,0.1f,0.1f };
				water->SetPosition({ 1000.0f,-50.0f,0.0f });
				hot->SetPosition({ 1000.0f,-50.0f,0.0f });
			}
			hot->SetScale(sca);

			FollowCollide();
		}
		water->SetScale(watersca);
	}
}

//描画
void HotWater::Draw() {
	//ImGui::Begin("test");
	//ImGui::SliderFloat("Defense", &watersca.x, 4, 0);
	//ImGui::End();
	if (IsAlive) {
		Object3d::PreDraw();
		if (!onGround) {
			water->Draw();
		}
		Texture::PreDraw(); 
		hot->Draw();
	}
}

//プレイヤーとの当たり判定
void HotWater::Collide() {
	if (!player->GetWet()) {
		if (Collision::CircleCollision(pos.x, pos.z, radius, player->GetPosition().x, player->GetPosition().z, 1.0f)) {
			Audio::GetInstance()->PlayWave("Resources/Sound/wet.wav", 0.2f);
			player->SetHp(player->GetHp() - 0.5f);
			player->SetWet(true);
			player->SetPoizun(true);
			player->SetCharge(0);
			player->SetRotCount(0);
		}
		else {
			player->SetPoizun(false);
		}
	}
}

//プレイヤーとの当たり判定
void HotWater::FollowCollide() {
	XMFLOAT3 distance = player->GetDistance();
	XMFLOAT3 playerpos = player->GetPosition();
	float weight = player->GetArmWeight();
	if (!player->GetBubble()) {
		if (Collision::CircleCollision(pos.x, pos.z, radius, player->GetPosition().x, player->GetPosition().z, 1.0f)
			&& player->GetInterval() == 0 && !onGround && IsAlive) {
			Audio::GetInstance()->PlayWave("Resources/Sound/wet.wav", 0.2f);
			IsAlive = false;
			water->SetPosition({ 0.0f,-50.0f,0.0f });
			player->SetHp(player->GetHp() - 1);
			player->SetCharge(0);
			player->SetRotCount(0);
			player->SetInterval(100);
			distance.x = playerpos.x - pos.x;
			distance.z = playerpos.z - pos.z;
			player->SetDistance(distance);
			player->SetJumpG(0.5f);
			player->SetDamageFlag(true);
			player->SetAttackFlag(false);
			player->SetBubble(true);
			if (weight != 0.0f) {
				weight = 0.0f;
				player->SetArmWeight(weight);
			}
		}
	}
}

//お湯を飛ばす
void HotWater::Set(const XMFLOAT3& pos) {
	this->pos = pos;
	watersca = { 0.0f,0.0f,0.0f };
	water->SetScale(watersca);
	water->SetPosition(this->pos);
	const float rnd_vel = 0.2f;
	vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
	vel.y = (float)rand() / RAND_MAX * (rnd_vel * 2.0f); //- rnd_vel / 2.0f;
	vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
	if (!IsAlive) {
		IsAlive = true;
		action = 1;
	}
}

void HotWater::Follow(const XMFLOAT3& pos) {
	this->pos = pos;
	watersca = { 0.0f,0.0f,0.0f };
	water->SetScale(watersca);
	water->SetPosition(this->pos);
	if (!IsAlive) {
		IsAlive = true;
		followTimer = 0;
		action = 2;
	}
}

//導入の水
void HotWater::AppeaSet(const XMFLOAT3& pos) {
	this->pos = pos;
	water->SetPosition(this->pos);
	const float rnd_vel = 0.2f;
	vel.x = -0.2f;
	vel.y = 0.2f; //- rnd_vel / 2.0f;
	vel.z = 0;
	if (!IsAlive) {
		IsAlive = true;
		action = 1;
	}
}

//開放処理
void HotWater::Final() {
	delete hot;
}
