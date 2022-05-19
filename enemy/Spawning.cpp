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
	texture = Texture::Create(ImageManager::playerhp, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	texture->TextureCreate();
	net[0] = Texture::Create(ImageManager::net, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	net[0]->TextureCreate();
	net[1] = Texture::Create(ImageManager::effect3, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	net[1]->TextureCreate();
	BossHP = 10;
}

void Spawning::Initialize(bool shadow) {
	enemyobj = TouchableObject::Create(model);
	enemyobj->SetModel(model);
	enemyobj->SetPosition(pos);
	enemyobj->SetScale({3.9f,3.9f,3.9f});

	texture->SetPosition({ pos.x,pos.y + 4.5f,pos.z });
	texture->SetRotation({45,0,0 });
	texture->SetScale({ (float)BossHP *0.05f,0.2f,0.2f });

	net[0]->SetPosition({pos.x,pos.y+1.0f,pos.z});
	net[0]->SetRotation({90,0,0});
	net[0]->SetScale({ 0.4f,0.4f,0.0f });

	net[1]->SetPosition({ pos.x,pos.y,pos.z });
	net[1]->SetRotation({ 90,0,0 });
	net[1]->SetScale({ 0.3f,0.3f,0.0f });


}

void Spawning::specialDraw() {
	if (IsAlive) {
		Texture::PreDraw();
		net[0]->Draw();
		net[1]->Draw();
		texture->Draw();
	}

}
void Spawning::Finalize() {
	delete enemyobj;
	delete texture;
	delete net[0];
	delete net[1];
}

void Spawning::Spec() {
	if (BossHP > 0) { IsAlive = true; } else { BossHP = 10; }
	if (IsAlive) {
		enemyobj->Update();
		enemyobj->SetPosition(pos);
		texture->Update();
		texture->SetPosition({ pos.x,pos.y + 5.0f,pos.z });
		texture->SetScale({ (float)BossHP * 0.05f,0.05f,0.0f });

		net[0]->Update();
		net[0]->SetPosition({ pos.x + 0.2f,pos.y + 3.0f,pos.z - 0.1f });
		net[0]->SetRotation({ 90,0,0 });
		net[1]->Update();
		net[1]->SetPosition(smooth);
		smooth.y = smooth.y + 0.1f;
		if (smooth.y > 7.0f) {
			smooth.y = pos.y + 4.5f;
		}
		net[1]->SetRotation({ 90,0,0 });
	}
}


