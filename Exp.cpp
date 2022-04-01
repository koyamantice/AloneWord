#include "Exp.h"
#include "Input.h"
#include"Collision.h"
#include"Easing.h"
#include "DebugText.h"
#include<sstream>
#include<iomanip>

using namespace DirectX;
//float easeInSine(float x) {
//	return x * x * x;
//}
//float easeOutBack(float x) {
//	return x == 1 ? 1 : 1 - powf(2, -10 * x);
//}
//
//float easeInOut(float x) {
//	return x < 0.5 ? 2 * x * x : 1 - powf(-2 * x + 2, 2) / 2;
//}
Exp::Exp() {
	model = Model::CreateFromOBJ("Particle");
	object3d = new Object3d();
}

void Exp::Initialize() {
	object3d = Object3d::Create();
	object3d->SetModel(model);
	object3d->SetPosition(pos);
	object3d->SetScale({ 1.0f,1.0f,1.0f });
}

void Exp::Finalize() {

}

void Exp::Update(Player* player,Enemy* enemy) {
	Input* input = Input::GetInstance();
	
	SetExp(enemy);
	if (LockOn(player) == true) {
		Follow(player);
	}
	Collide(player);
	object3d->Update();
	object3d->SetPosition(pos);
	object3d->SetScale(scale);
}

//描画
void Exp::Draw() {
	//ImGui::Begin("test");
	//if (ImGui::TreeNode("Debug")) {
	//	if (ImGui::TreeNode("Exp")) {
	//		ImGui::Text("%d", ExpAlive);
	//		ImGui::Unindent();
	//		ImGui::TreePop();
	//	}
	//	ImGui::TreePop();
	//}
	//ImGui::End();
	Object3d::PreDraw();
	if (ExpAlive == true) {
		object3d->Draw();
	}
}

void Exp::SetExp(Enemy* enemy) {
	//エフェクトの発生
	bool SetExp = enemy->GetDrawExp();
	//エフェクトの発生
	if (SetExp == true && BirthExp == false) {
		pos = enemy->GetPosition();
		boundpower.x = (float)(rand() % 4 - 2);
		boundpower.y = 3;
		boundpower.z = (float)(rand() % 4 - 2);
		//effectcolor.w = (float)(rand() % 10);
		if (boundpower.x == 0.0f) {
			boundpower.x = 1.0f;
		}

		if (boundpower.z == 0.0f) {
			boundpower.z = 1.0f;
		}
		boundpower.x = boundpower.x / 10;
		boundpower.y = boundpower.y / 10;
		boundpower.z = boundpower.z / 10;
		ExpAlive = true;
		BirthExp = true;
	}
	if (ExpAlive == true) {
		boundpower.y -= 0.02f;
		pos.x += boundpower.x;
		pos.y += boundpower.y;
		pos.z += boundpower.z;
		if (pos.y < 0.0f) {
			pos.y = 0.0f;
			boundpower = { 0.0f,0.0f,0.0f };
			enemy->SetDrawExp(false);
			BirthExp = false;
		}
	}
}

bool Exp::LockOn(Player* player) {
	float distance;
	distance = sqrtf(((pos.x - player->GetPosition().x) * (pos.x - player->GetPosition().x)) +
		((pos.y - player->GetPosition().y) * (pos.y - player->GetPosition().y)) +
		((pos.z - player->GetPosition().z) * (pos.z - player->GetPosition().z)));
	if (distance <= 15) {//距離が一定数なったらプレイヤーを検知
		return true;
	} else {
		return false;
	}

	return true;
}

void Exp::Follow(Player* player) {
	XMFLOAT3 position{};
	position.x = (player->GetPosition().x - pos.x);
	position.z = (player->GetPosition().z - pos.z);
	double posR = sqrt(pow(pos.x, 2) + pow(pos.z, 2));
	double Check = position.x / posR;
	double Check2 = position.z / posR;

	pos.x += (float)Check * 0.095f;
	pos.z += (float)Check2 * 0.095f;
}

bool Exp::Collide(Player* player) {
	float PlaExp = player->GetExp();
	if (ExpAlive) {
		if (Collision::SphereCollision(pos.x, pos.y, pos.z, 0.5f, player->GetPosition().x, player->GetPosition().y, player->GetPosition().z, 0.5f) == true) {
			ExpAlive = false;
			player->SetExp(player->GetExp() + 1.0f);
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}
