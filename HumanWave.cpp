#include "HumanWave.h"
#include "ImageManager.h"
#include "ModelManager.h"
#include "Collision.h"
#include <Easing.h>

//初期化
void HumanWave::Init() {
	wave = Texture::Create(ImageManager::enemy, { 0,0,0 }, { 12,12,12 }, { 1,1,1,0.6f });
	wave->TextureCreate();
	wave->SetPosition({ 0.0f,0.0f,0.0f });
	wave->SetRotation({ 90.0f, 0.0f, 0.0f });
	wave->SetScale(scale);
}

//更新
void HumanWave::Upda() {
	wave->Update();
	//衝撃波の位置が決まってから
	if (IsAlive == true) {
		scale.x += 0.05f;
		scale.y += 0.05f;
		scale.z += 0.05f;

		//衝撃波が広がる
		damegeArea += 0.06f;

		if (damegeArea >= 0.06f) {
			safeArea += 0.06f;
		}
		if (scale.x >= 2.0f) {
			IsAlive = false;
			scale = { 0.0f,0.0f,0.0f };
			damegeArea = 0.0f;
			safeArea = 0.0f;
		}

		if (Collide() && (player->GetInterval() == 0)) {
			player->SetHp(player->GetHp() - 0.1f);
			player->SetInterval(100);
		}
	}

	wave->SetPosition(pos);
	wave->SetScale(scale);
}

//描画
void HumanWave::Draw() {
	if (IsAlive) {
		wave->Draw();
	}
}

//プレイヤーとの当たり判定
bool HumanWave::Collide() {
		if (Collision::CircleCollision(pos.x, pos.z, damegeArea, player->GetPosition().x, player->GetPosition().z, 1.0f)) {
			return true;
		}
		else {
			return false;
		}
}

//お湯を飛ばす
void HumanWave::Set(const XMFLOAT3& pos) {
	this->pos = pos;
	wave->SetPosition(this->pos);
	if (!IsAlive) {
		IsAlive = true;
	}
}

//開放処理
void HumanWave::Final() {
	delete wave;
}
