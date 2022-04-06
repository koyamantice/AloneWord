#include "Spawning.h"
#include "Collision.h"

Spawning::Spawning() {
	model = Model::CreateFromOBJ("EHub");
	object3d = new Object3d();
	texture = Texture::Create(5, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	texture->TextureCreate();
}

void Spawning::Initialize() {
	object3d = Object3d::Create();
	object3d->SetModel(model);
	object3d->SetPosition(pos);
	object3d->SetScale({1,1,1});

	texture->SetPosition({ pos.x,pos.y + 3.0f,pos.z });
	texture->SetRotation({ 45,0,0 });
	texture->SetScale({ 0.2f,(float)Hp,0.2f });

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
	texture->SetPosition({ pos.x,pos.y + 3.0f,pos.z });
	texture->SetScale({ 0.2f,(float)Hp*0.02f,0.2f });

	if (Hp>0) {
		isAlive = true;
	} else {
		isAlive = false;
	}


}

void Spawning::Finalize() {
	delete object3d;
	delete texture;
}

void Spawning::Draw() {
	Object3d::PreDraw();
	if (isAlive) {
		object3d->Draw();
	}
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
		if (Collision::CircleCollision(pos.x,pos.z, 1.5f, Armpos.x, Armpos.z, 1.5f) == true) {
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
				Hp -= ((int)weight * 2) * (int)power;
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
