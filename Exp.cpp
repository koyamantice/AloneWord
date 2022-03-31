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
	object3d->Update();
	object3d->SetPosition(pos);
	object3d->SetScale(scale);
}

//描画
void Exp::Draw() {
	ImGui::Begin("test");
	if (ImGui::TreeNode("Debug")) {
		if (ImGui::TreeNode("Exp")) {
			ImGui::Text("%d", ExpAlive);
			ImGui::Unindent();
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
	ImGui::End();
	Object3d::PreDraw();
	if (ExpAlive == true) {
		object3d->Draw();
	}
}

void Exp::SetExp(Enemy* enemy) {
	//エフェクトの発生
	bool SetExp = enemy->GetDrawExp();
	//エフェクトの発生
	if (SetExp == true && ExpAlive2 == false) {
		boundpower.x = (float)(rand() % 4 - 2);
		boundpower.y = (float)(rand() % 5);
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
		pos = enemy->GetPosition();
		ExpAlive = true;
		ExpAlive2 = true;
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
			ExpAlive2 = false;
		}
	}
}
