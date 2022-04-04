#include "Spawning.h"
#include "Collision.h"

Spawning::Spawning() {
	model = Model::CreateFromOBJ("chr_knight");
	object3d = new Object3d();
	texture = Texture::Create(5, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	texture->TextureCreate();
	texture->SetPosition({ pos.x,pos.y+3.0f,pos.z });
	texture->SetRotation({ 45,0,0 });
	texture->SetScale({ 0.2f,0.2f,0.2f });
}

void Spawning::Initialize() {
	object3d = Object3d::Create();
	object3d->SetModel(model);
	object3d->SetPosition(pos);
	texture->SetPosition({ pos.x,pos.y + 3.0f,pos.z });
	object3d->SetScale({3,3,3});

}

void Spawning::Update() {
	object3d->Update();
	object3d->SetPosition(pos);
	if (sizeof(enemy)>0) {
		if (enemy[0]==nullptr) {
		} else {
			for (int i = 0; i < 10; i++) {
				enemy[i]->SetBasePos(pos);
				enemy[i]->Update();
			}
		}
	}
	collideAttackArm();
	texture->Update();
}

void Spawning::Finalize() {
	delete object3d;
}

void Spawning::Draw() {
	Object3d::PreDraw();
	object3d->Draw();
	Texture::PreDraw();
	texture->Draw();

}

void Spawning::SetEnemy(const int& i, Enemy* enemy) {
	this->enemy[i] = enemy;
}
//UŒ‚ŠÖ”
void Spawning::collideAttackArm() {
	XMFLOAT3 Armpos = player->GetArmPosition();
	bool attackflag = player->GetAttackFlag();
	float power = player->GetPower();
	float weight = player->GetArmWeight();
	if (attackflag) {
		if (Collision::SphereCollision(pos.x, pos.y, pos.z, 0.5f, Armpos.x, Armpos.y, Armpos.z, 0.5f) == true) {
			Hit = true;
			player->SetAttackFlag(false);
			//‚Â‚¢‚Ä‚é“G‚Ì”‚Å‰¹‚ª•Ï‚í‚é
			if (weight <= 3) {
				Audio::GetInstance()->PlayWave("Resources/Sound/strongL1.wav", 0.4f);
			} else if (weight > 3 && weight <= 6) {
				Audio::GetInstance()->PlayWave("Resources/Sound/strongL2.wav", 0.4f);
			} else if (weight >= 7) {
				Audio::GetInstance()->PlayWave("Resources/Sound/strongL3.wav", 0.4f);
			}

			//ƒ{ƒX‚ÌHP‚ğ‚Ö‚ç‚·
			if (Hit == true) {
				Hp -= ((int)weight * 2) * power;
				weight = 0.0f;
				//boundpower.x = (float)(rand() % 4 - 2);
				//boundpower.y = (float)(rand() % 6);
				//boundpower.z = (float)(rand() % 4 - 2);
				player->SetArmWeight(weight);
				Hit = false;
			}
		}
	}
}
