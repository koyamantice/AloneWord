#include "Obstacle.h"
#include "Input.h"
#include"Collision.h"
#include"Easing.h"
#include "DebugText.h"
#include<sstream>
#include<iomanip>
#include"Enemy.h"
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
void Obstacle::PosSet(Obstacle* obstacle[]) {
	obstacle[0]->SetPosition({ 0,0,0 });
	obstacle[1]->SetPosition({5,0,0});
}
Obstacle::Obstacle() {
	model = Model::CreateFromOBJ("Particle");
	object3d = new Object3d();
	//Sprite::LoadTexture(3, L"Resources/2d/ObstacleHP.png");
}

void Obstacle::Initialize() {
	//”wŒiƒXƒvƒ‰ƒCƒg¶¬
	object3d = Object3d::Create();
	object3d->SetModel(model);
	object3d->SetScale({ 1.0f,1.0f,1.0f });
}

void Obstacle::Finalize() {
	delete object3d;
}

void Obstacle::Update() {
	Input* input = Input::GetInstance();

	object3d->Update();
}

//•`‰æ
void Obstacle::Draw() {
	/*ImGui::Begin("test");
	if (ImGui::TreeNode("Debug")) {
		if (ImGui::TreeNode("Obstacle")) {
			ImGui::SliderFloat("power", &power, 50, -50);
			ImGui::Text("Sub %d", SpeedSub);

			ImGui::Unindent();
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
	ImGui::End();*/
	Sprite::PreDraw();
	
	Object3d::PreDraw();
	object3d->Draw();
}
