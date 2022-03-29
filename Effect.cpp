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
	effecttexture->SetScale({ 0.4f,0.4f,0.4f });
}

void Effect::Finalize() {
	
}

void Effect::Update(BossEnemy* bossenemy) {
	Input* input = Input::GetInstance();
	bool effect = bossenemy->GetEffect();
	//�G�t�F�N�g�̔���
	if (effect == true) {
		effectscale = { 0.4f,0.4f,0.4f };
		boundpower.x = (float)(rand() % 6 - 3);
		boundpower.y = (float)(rand() % 3 + 3);
		boundpower.z = (float)(rand() % 6 - 3);
		if (boundpower.x == 0.0f) {
			boundpower.x = 1.0f;
		}

		if (boundpower.z == 0.0f) {
			boundpower.z = 1.0f;
		}
		boundpower.x = boundpower.x / 10;
		boundpower.y = boundpower.y / 10;
		boundpower.z = boundpower.z / 10;
		effectpos = bossenemy->GetPosition();
		effectAlive = true;
		if (effectAlive == false) {
			effectAlive = true;
		}
		bossenemy->SetEffect(false);
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
		}
	}
	effecttexture->Update();
	effecttexture->SetPosition(effectpos);
	effecttexture->SetScale(effectscale);
}

//�`��
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
