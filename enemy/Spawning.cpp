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
	object3d->SetScale({0.9f,0.9f,0.9f});

	texture->SetPosition({ pos.x,pos.y + 4.5f,pos.z });
	texture->SetRotation({ 0,0,0 });
	texture->SetScale({ (float)Hp*0.05f,0.2f,0.2f });
}

void Spawning::Update() {
	object3d->Update();
	object3d->SetPosition(pos);
	texture->Update();
	texture->SetPosition({ pos.x,pos.y + 5.0f,pos.z });
	texture->SetScale({ (float)Hp * 0.05f,0.05f,0.0f });

	if (Hp>0) {
		isAlive = true;
	} else {
		isAlive = false;
	}
	if (isAlive) {
		if (sizeof(enemy) > 0) {
			if (enemy[0] != nullptr) {
				for (int i = 0; i < EnemyMax; i++) {
					enemy[i]->SetBasePos(pos);
					enemy[i]->Update();
				}
			}
		}
		collideAttackArm();
		if (Collision::CircleCollision(pos.x, pos.z, 2.0f, player->GetPosition().x, player->GetPosition().z, 1.5f)) {
			player->BackPos();
		}
	} else {
		//for (int i = 0; i < EnemyMax; i++) {
			//enemy[i]->SetStop(true);
		//}
	}

}

void Spawning::Finalize() {
	delete object3d;
	delete texture;
}

void Spawning::Draw() {
	/*ImGui::Begin("test");
if (ImGui::TreeNode("Debug")) {
	if (ImGui::TreeNode("Spawn")) {
		ImGui::Text("hp %d", Hp);

		ImGui::Unindent();
		ImGui::TreePop();
	}
	ImGui::TreePop();
}
	ImGui::End();*/
	Object3d::PreDraw();
	if (isAlive) {
		object3d->Draw();
	}
	Texture::PreDraw();
	texture->Draw();

}

void Spawning::SetEnemy(const int& i, InterEnemy* enemy) {
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
		}
	}
	//ƒ{ƒX‚ÌHP‚ğ‚Ö‚ç‚·
	if (Hit == true) {
		Hp -= (weight * 2) * power;
		weight = 0.0f;
		//boundpower.x = (float)(rand() % 4 - 2);
		//boundpower.y = (float)(rand() % 6);
		//boundpower.z = (float)(rand() % 4 - 2);
		player->SetArmWeight(weight);
		Hit = false;
	}

}
