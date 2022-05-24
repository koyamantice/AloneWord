#include "HumanWave.h"
#include "ImageManager.h"
#include "ModelManager.h"
#include "Collision.h"
#include <Easing.h>

//������
void HumanWave::Init() {
	wave = Texture::Create(ImageManager::enemy, { 0,0,0 }, { 12,12,12 }, { 1,1,1,0.6f });
	wave->TextureCreate();
	wave->SetPosition({ 0.0f,0.0f,0.0f });
	wave->SetRotation({ 90.0f, 0.0f, 0.0f });
	wave->SetScale(scale);
}

//�X�V
void HumanWave::Upda() {
	wave->Update();
	//�Ռ��g�̈ʒu�����܂��Ă���
	if (IsAlive == true) {
		scale.x += 0.05f;
		scale.y += 0.05f;
		scale.z += 0.05f;

		//�Ռ��g���L����
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

//�`��
void HumanWave::Draw() {
	if (IsAlive) {
		wave->Draw();
	}
}

//�v���C���[�Ƃ̓����蔻��
bool HumanWave::Collide() {
		if (Collision::CircleCollision(pos.x, pos.z, damegeArea, player->GetPosition().x, player->GetPosition().z, 1.0f)) {
			return true;
		}
		else {
			return false;
		}
}

//�������΂�
void HumanWave::Set(const XMFLOAT3& pos) {
	this->pos = pos;
	wave->SetPosition(this->pos);
	if (!IsAlive) {
		IsAlive = true;
	}
}

//�J������
void HumanWave::Final() {
	delete wave;
}
