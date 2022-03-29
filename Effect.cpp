#include "Effect.h"
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
Effect::Effect() {
	
}

void Effect::Initialize() {
	effecttexture = Texture::Create(4, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	effecttexture->TextureCreate();
	//effecttexture->SetRotation({ 90,0,0 });
	effecttexture->SetScale({ 1.0f,1.0f,1.0f });
}

void Effect::Finalize() {
	
}

void Effect::Update() {
	Input* input = Input::GetInstance();

	if (effectAlive == 1) {
		EffectMove();
	}
	effecttexture->Update();
}

//•`‰æ
void Effect::Draw() {
	ImGui::Begin("test");
	if (ImGui::TreeNode("Debug"))
	{
		if (ImGui::TreeNode("Joy"))
		{
			ImGui::Text("IY %d", effectAlive);
			ImGui::Unindent();
			ImGui::TreePop();
		}

		ImGui::TreePop();
	}
	//ImGui::End();
	//Texture::PreDraw();
	//if (effectAlive == true) {
	//	effecttexture->Draw();
	//}
}


void Effect::EffectMove() {
	effectcolor.w -= 0.01;
	if (effectcolor.w <= 0.0f) {
		effectAlive = 0;
	}
}
