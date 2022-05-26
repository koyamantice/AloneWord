#include "Effect.h"
#include "Input.h"
#include"Collision.h"
#include"Easing.h"
#include "DebugText.h"
#include<sstream>
#include <XorShift.h>
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
Effect::Effect() {
	
}

void Effect::Initialize() {
	effecttexture = Texture::Create(ImageManager::effect2, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	effecttexture->TextureCreate();
	//effecttexture->SetRotation({ 90,0,0 });
	effecttexture->SetScale(effectscale);
}

void Effect::Finalize() {
	
}

void Effect::Update(InterBoss* bossenemy) {
	Input* input = Input::GetInstance();
	bool effect = bossenemy->GetEffect();
	bool effect2 = bossenemy->GetEffect2();
	//エフェクトの発生
	if (effect == true && effectAlive == false) {
		effectscale = { 0.3f,0.3f,0.3f };
		boundpower.x = (float)((int)(XorShift::GetInstance()->xor128()) % 20 - 5);
		boundpower.y = (float)((int)(XorShift::GetInstance()->xor128()) % 10 - 5);
		boundpower.z = (float)((int)(XorShift::GetInstance()->xor128()) % 20 - 5);
		effectcolor.w = 0.8f;
		effectcolor.x = 1.0f;
		effectcolor.y = 1.0f;
		effectcolor.z = 0.8f;
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
	/*	effectcolor.x = effectcolor.x / 10;
		effectcolor.y = effectcolor.y / 10;
		effectcolor.z = effectcolor.z / 10;*/
		//effectcolor.w = effectcolor.w / 100;
		effectpos = bossenemy->GetPosition();
		effectAlive = true;
	}
	if (effect2 == true && effectAlive == false) {
		effectscale = { 0.3f,0.3f,0.3f };
		boundpower.x = (float)((int)(XorShift::GetInstance()->xor128()) % 20 - 5);
		boundpower.y = (float)((int)(XorShift::GetInstance()->xor128()) % 10 - 5);
		boundpower.z = (float)((int)(XorShift::GetInstance()->xor128()) % 20 - 5);
		effectcolor.w = 0.8f;
		effectcolor.x = 1.0f;
		effectcolor.y = 0.0f;
		effectcolor.z = 0.0f;
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
		/*	effectcolor.x = effectcolor.x / 10;
			effectcolor.y = effectcolor.y / 10;
			effectcolor.z = effectcolor.z / 10;*/
			//effectcolor.w = effectcolor.w / 100;
		effectpos = bossenemy->GetPosition();
		effectAlive = true;
	}

	if (effectAlive == true) {
		boundpower.y -= 0.02f;
		effectpos.x += boundpower.x;
		effectpos.y += boundpower.y;
		effectpos.z += boundpower.z;
		effectscale.x -= 0.01f;
		effectscale.y -= 0.01f;
		effectscale.z -= 0.01f;
		effectcolor.w -= 0.005f;
		if (effectscale.x <= 0.0f) {
			effectAlive = false;
			bossenemy->SetEffect(false);
			bossenemy->SetEffect2(false);

		}
	}
	effecttexture->Update();
	effecttexture->SetColor(effectcolor);
	effecttexture->SetPosition(effectpos);
	effecttexture->SetScale(effectscale);
}

//描画
void Effect::Draw() {
	
	Texture::PreDraw();
	if (effectAlive == true) {
		effecttexture->Draw();
	}
}


void Effect::EffectMove() {
	
}
