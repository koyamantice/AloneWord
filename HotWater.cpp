#include "HotWater.h"
#include "ImageManager.h"
#include "ModelManager.h"
#include "Collision.h"
#include <Easing.h>

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
		if (onGround) {
			if (shrink) {
				if (frame < 1.0f) {
					frame += 0.0018f;
			 } else {
					frame = 0;
				}
				sca = {
				Ease(In,Quint,frame,(float)sca.x,(float)0),
				Ease(In,Quint,frame,(float)sca.y,(float)0),
				Ease(In,Quint,frame,(float)sca.z,(float)0),
				};
			} else {
				if (sca.x < 0.3f) {
					sca.x += 0.02f;
					sca.y += 0.02f;
					sca.z += 0.02f;
				} else {
					if (!shrink) {
						shrink = true;
					}
				}
			}
			if (sca.x > 0.15f ) {
				Collide();
			}
		} else {
			pos.x += vel.x;
			pos.y += vel.y;
			pos.z += vel.z;
			vel.y -= 0.01f;
			water->SetPosition(pos);
			if (pos.y < -0.2f) {
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
}

//描画
void HotWater::Draw() {
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
			player->SetHp(player->GetHp() - 0.5f);
			player->SetWet(true);
		}
	}
}

//お湯を飛ばす
void HotWater::Set(const XMFLOAT3& pos) {
	this->pos = pos;
	water->SetPosition(this->pos);
	const float rnd_vel = 0.2f;
	vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
	vel.y = (float)rand() / RAND_MAX * (rnd_vel * 2.0f); //- rnd_vel / 2.0f;
	vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
	if (!IsAlive) {
		IsAlive = true;
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
	}
}

//開放処理
void HotWater::Final() {
	delete hot;
}
