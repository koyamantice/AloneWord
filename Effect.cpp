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
	effecttexture->SetScale(effectscale);
}

void Effect::Finalize() {
	
}

void Effect::Update(BossEnemy* bossenemy) {
	Input* input = Input::GetInstance();
	bool effect = bossenemy->GetEffect();
	//エフェクトの発生
	if (effect == true && effectAlive == false) {
		effectscale = { 0.2f,0.2f,0.2f };
		boundpower.x = (float)(rand() % 2 - 1);
		boundpower.y = (float)(rand() % 2 + 2);
		boundpower.z = (float)(rand() % 2 - 1);
		effectcolor.w = (float)(rand() % 10);
		if (boundpower.x == 0.0f) {
			boundpower.x = 1.0f;
		}

		if (boundpower.z == 0.0f) {
			boundpower.z = 1.0f;
		}
		boundpower.x = boundpower.x / 10;
		boundpower.y = boundpower.y / 10;
		boundpower.z = boundpower.z / 10;
		effectcolor.w = effectcolor.w / 100;
		effectpos = bossenemy->GetPosition();
		effectAlive = true;
		if (effectAlive == false) {
			effectAlive = true;
		}
	
	}
	if (effectAlive == true) {
		boundpower.y -= 0.02f;
		effectpos.x += boundpower.x;
		effectpos.y += boundpower.y;
		effectpos.z += boundpower.z;
		effectscale.x -= 0.01;
		effectscale.y -= 0.01;
		effectscale.z -= 0.01;
		effectcolor.w -= 0.01;
		if (effectscale.x <= 0.0f) {
			effectAlive = false;
			bossenemy->SetEffect(false);
		}
	}
	effecttexture->Update();
	effecttexture->SetColor({1.0f,1.0f,1.0f,0.1});
	effecttexture->SetPosition(effectpos);
	effecttexture->SetScale(effectscale);
}

//描画
void Effect::Draw() {
	ImGui::Begin("test");
	if (ImGui::TreeNode("Debug"))
	{
		if (ImGui::TreeNode("Joy"))
		{
			ImGui::Text("IY %d", effectAlive);
			ImGui::SliderFloat("bound.x", &effectpos.x, 50, -50);
			ImGui::Unindent();
			ImGui::TreePop();
		}

		ImGui::TreePop();
	}
	ImGui::End();
	Texture::PreDraw();
	if (effectAlive == true) {
		effecttexture->Draw();
	}
}


void Effect::EffectMove() {
	
}
