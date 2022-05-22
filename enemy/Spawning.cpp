#include "Spawning.h"
#include "Collision.h"
#include "Rice.h"
#include <ModelManager.h>
#include <DebugText.h>
#include <ImageManager.h>
#include "TouchableObject.h"
Spawning::Spawning() {
	model = ModelManager::GetIns()->GetModel(ModelManager::EHub);
	enemyobj = TouchableObject::Create(model);
	BossHp[now] = Texture::Create(ImageManager::spawnhp, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	BossHp[now]->TextureCreate();
	BossHp[now]->SetColor({ 1.0f,1.0f,1.0f,1.0f });
	BossHP = 15;
	for (int i = 0; i < 1; i++) {
		BossHp[i]->SetPosition({ pos.x,pos.y + 4.5f,pos.z });
		BossHp[i]->SetRotation({ 45,0,0 });
		BossHp[i]->SetScale({ (float)BossHP * 0.05f,0.2f,0.2f });
		//BossHp[i]->SetIsBillboard(true);
	}

	net[0] = Texture::Create(ImageManager::net, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	net[0]->TextureCreate();
	net[1] = Texture::Create(ImageManager::effect3, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	net[1]->TextureCreate();
}

void Spawning::Initialize(bool shadow) {
	enemyobj = TouchableObject::Create(model);
	enemyobj->SetModel(model);
	enemyobj->SetPosition(pos);
	enemyobj->SetScale({ 3.9f,3.9f,3.9f });
	net[0]->SetPosition({ pos.x,pos.y + 1.0f,pos.z });
	net[0]->SetRotation({ 90,0,0 });
	net[0]->SetScale({ 0.4f,0.4f,0.0f });

	net[1]->SetPosition({ pos.x,pos.y,pos.z });
	net[1]->SetRotation({ 90,0,0 });
	net[1]->SetScale({ 0.3f,0.3f,0.0f });


}

void Spawning::specialDraw() {
	Texture::PreDraw();
	net[0]->Draw();
	net[1]->Draw();
	for (int i = 0; i < 1; i++) {
		BossHp[i]->Draw();
	}
}
void Spawning::Finalize() {
	delete enemyobj;

	for (int i = 0; i < 1; i++) {
		delete BossHp[i];
	}
	delete net[0];
	delete net[1];
}

void Spawning::Spec() {
	if (BossHP > 0) {} else { BossHP = 10; pos.y = 10.0f; }
	if (pos.y > 0) {
		pos.y -= 0.4f;
	} else {
		pos.y = 0;
	}
	enemyobj->Update();
	enemyobj->SetPosition(pos);
	for (int i = 0; i < 1; i++) {
		BossHp[i]->SetRotation({ 45,0,0 });
		BossHp[i]->SetScale({ (float)BossHP * 0.05f,0.1f,0.05f });
		BossHp[i]->Update();
	}
	BossHp[0]->SetPosition({ pos.x,pos.y + 4.5f,pos.z });
	net[0]->Update();
	net[0]->SetPosition({ pos.x + 0.2f,pos.y + 3.0f,pos.z - 0.1f });
	net[0]->SetRotation({ 90,0,0 });
	net[1]->Update();
	net[1]->SetPosition(smooth);
	smooth.y = smooth.y + 0.05f;
	if (smooth.y > 7.0f) {
		smooth.y = pos.y + 4.5f;
	}
	net[1]->SetRotation({ 90,0,0 });
}


