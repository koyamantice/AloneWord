#include "Warp.h"
#include "Input.h"
#include"Collision.h"
#include"Easing.h"
#include "DebugText.h"
#include<sstream>
#include<iomanip>
#include"ImageManager.h"
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
Warp::Warp() {

}

void Warp::Initialize() {
	Warptexture = Texture::Create(ImageManager::magic, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	Warptexture->TextureCreate();
	Warptexture->SetRotation({ 90.0f, 0.0f, 0.0f });
	Warptexture->SetScale({ 0.7f,0.7f,0.7f });
}

void Warp::Finalize() {
	delete Warptexture;
}

void Warp::Update(Player*player) {
	Input* input = Input::GetInstance();
	Warptexture->SetPosition(pos);
	Warptexture->Update();
}

//•`‰æ
void Warp::Draw() {
	/*ImGui::Begin("test");
	if (ImGui::TreeNode("Debug")) {
		if (ImGui::TreeNode("Warp")) {
			ImGui::SliderFloat("pos", &pos.x, 50, -50);
			ImGui::SliderFloat("pos", &pos.y, 50, -50);
			ImGui::SliderFloat("pos", &pos.z, 50, -50);
			ImGui::Unindent();
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
	ImGui::End();*/

	Texture::PreDraw();
	Warptexture->Draw();
}

bool Warp::collidePlayer(Player* player) {
	XMFLOAT3 playerpos = player->GetPosition();
	if (Collision::CircleCollision(playerpos.x, playerpos.z, 1.0,
		pos.x, pos.z, 1.0)) {
		return true;
	} else {
		return false;
	}
}

