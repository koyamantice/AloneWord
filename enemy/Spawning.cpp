#include "Spawning.h"
#include "Collision.h"
#include "Rice.h"
#include <ModelManager.h>
#include <DebugText.h>
#include <ImageManager.h>
#include "TouchableObject.h"
Spawning::Spawning(int Categoly) {
	model = ModelManager::GetIns()->GetModel(ModelManager::EHub);
	object3d = TouchableObject::Create(model);
	texture = Texture::Create(ImageManager::playerhp, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	texture->TextureCreate();
	net[0] = Texture::Create(ImageManager::net, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	net[0]->TextureCreate();
	net[1] = Texture::Create(ImageManager::effect3, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	net[1]->TextureCreate();

	//if (Categoly==0) {
	//	for (int i = 0; i < EneMax; i++) {
	//		enemy[i] = new Rice();
	//	}
	//} else 	if (Categoly == 1) {
	//	for (int i = 0; i < EneMax; i++) {
	//		enemy[i] = new Rice();
	//	}
	//} else 	if (Categoly == 2) {
	//	for (int i = 0; i < EneMax; i++) {
	//		enemy[i] = new Rice();
	//	}
	//}
}

void Spawning::Initialize() {
	object3d = TouchableObject::Create(model);
	object3d->SetModel(model);
	object3d->SetPosition(pos);
	object3d->SetScale({3.9f,3.9f,3.9f});

	texture->SetPosition({ pos.x,pos.y + 4.5f,pos.z });
	texture->SetRotation({ 0,0,0 });
	texture->SetScale({ (float)Hp*0.05f,0.2f,0.2f });

	net[0]->SetPosition({pos.x,pos.y+1.0f,pos.z});
	net[0]->SetRotation({90,0,0});
	net[0]->SetScale({ 0.4f,0.4f,0.0f });

	net[1]->SetPosition({ pos.x,pos.y,pos.z });
	net[1]->SetRotation({ 90,0,0 });
	net[1]->SetScale({ 0.3f,0.3f,0.0f });


}

void Spawning::Update() {
	if (pause) { return; }
	if (Hp > 0) { isAlive = true; } else { isAlive = false; }
	//for (int i = 0; i < EneMax; i++) {
	//	enemy[i]->SetBasePos(pos);
	//	enemy[i]->Respawn(360.0f/EneMax*i);
	//	if (isAlive|| enemy[i]->GetIsAlive()==true|| enemy[i]->GetIsTimer()<=100) {
	//		enemy[i]->Update();
	//		if (enemy[i]->GetIsAlive()) {
	//			for (int colA = 0; colA < EneMax; colA++) {
	//				for (int colB = 1; colB < EneMax; colB++) {
	//					if (Collision::SphereCollision2(enemy[colA]->GetPosition(), 2.0f, enemy[colB]->GetPosition(), 2.0f) && colA != colB) {//“–‚½‚è”»’è‚Æ©‹@“¯m‚Ì“–‚½‚è”»’è‚Ìíœ
	//						DebugText::GetInstance()->Print("Hit", 0, 0, 5.0f);
	//						enemy[colA]->SetHit(true);
	//						enemy[colB]->SetHit(false);
	//						break;
	//					} else {
	//						enemy[colA]->SetHit(false);
	//						break;
	//					}
	//				}
	//			}
	//		}
	//	}
	//}

	if (isAlive) {
		object3d->Update();
		object3d->SetPosition(pos);
		//for (int i = 0; i < EneMax;i++) {
		//	if (Collision::CircleCollision(pos.x,pos.z,1.8f, enemy[i]->GetPosition().x,enemy[i]->GetPosition().z, 1.8f)) {
		//		if (!enemy[i]->GetIsAlive()) {
		//			enemy[i]->SetScale(rand() * (XM_PI / 180.0f));
		//			enemy[i]->SetSpeed(rand());
		//		} else {

		//		}
		//	}
		//}


		if (Collision::CircleCollision(pos.x, pos.z, 2.0f, player->GetPosition().x, player->GetPosition().z, 1.5f)) {
			player->BackPos();
		}
		//for (int i = 0; i < EneMax;i++) {
		//	if (enemy[i]->CollidePos(pos, 2.0f)) {
		//		enemy[i]->SetHit(true);
		//		break;
		//	}
		//}
		//collideAttackArm();
		texture->Update();
		texture->SetPosition({ pos.x,pos.y + 5.0f,pos.z });
		texture->SetScale({ (float)Hp * 0.05f,0.05f,0.0f });

		net[0]->Update();
		net[0]->SetPosition({ pos.x+0.2f,pos.y + 3.0f,pos.z-0.1f });
		net[0]->SetRotation({ 90,0,0 });
		net[1]->Update();
		net[1]->SetPosition({ pos.x,pos.y+5.0f,pos.z });
		net[1]->SetRotation({ 90,0,0 });
	}
}

void Spawning::Finalize() {
	delete object3d;
	delete texture;
	//for (int i = 0; i < EneMax; i++) {
	//	enemy[i]->Finalize();
	//}

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
	if (isAlive) {
		Object3d::PreDraw();
		object3d->Draw();
		Texture::PreDraw();
		texture->Draw();
		net[0]->Draw();
		net[1]->Draw();
	}
	//for (int i = 0; i < EneMax; i++) {
	//	enemy[i]->Draw();
	//}
}

void Spawning::Pause(const int& Timer) {
	wait++;
	//for (int i = 0; i < EneMax; i++) {
	//	enemy[i]->Pause(Timer);
	//}
	if (wait >= Timer) {
		pause = false;
		wait = 0;
	} else {
		pause = true;
	}
}

//UŒ‚ŠÖ”
bool Spawning::collideAttackArm() {
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
			if (power == 0.25f) {
				stop = 10;
			} if (power == 0.5f) {
				stop = 15;
			}if (power == 0.75f) {
				stop = 30;
			}if (power == 1.0f) {
				stop = 60;
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
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}


}
