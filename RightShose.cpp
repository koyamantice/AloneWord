#include "RightShose.h"
#include"Collision.h"
#include<sstream>
#include<iomanip>
#include <Easing.h>
using namespace DirectX;

RightShose::RightShose() {
	model = ModelManager::GetIns()->GetModel(ModelManager::RightShose);
	enemyobj = new Object3d();
}

void RightShose::Initialize() {
	assert(player);
	IsAlive = 0;
	enemyobj = Object3d::Create();
	enemyobj->SetModel(model);
	pos = { 10.0f,0.0f,0.0f };
	enemyobj->SetPosition(pos);
	
	rot = { 0,90,0 };
	enemyobj->SetRotation(rot);
	enemyobj->SetScale({ 1.5f,1.5f,1.5f });
	texture = Texture::Create(1, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
	texture->TextureCreate();
	//texture->SetColor({ 1,1,1,1 });
	texture->SetPosition(pos.x, -1, pos.z);
	texture->SetRotation({ 90,0,0 });
	texture->SetScale({ 0.3f,0.3f,0.3f });
}

void RightShose::Finalize() {
	//delete enemyobj;
	delete texture;
}

//ƒ{ƒX‚Ìs“®
void RightShose::Spec() {
	XMFLOAT3 AfterPos{};
	if (AttackCount > 180 && pos.y <= 0.1f) {
		if (!active) {
			action = (rand() % 2);
			frame = 0;
			pat = 1;
			active = true;
		}
	}
	else {
		if (!active) {
			AttackCount++;
			if (State == Up) {
				AfterPos.y = 1.0f;
			}
			else {
				AfterPos.y = 0.0f;
			}
			if (frame <= 0.65) {
				frame += 0.005f;
			}
			else {
				frame = 0.0f;
				if (State == Up) {
					State = Down;
				}
				else {
					State = Up;
				}
			}
			pos.y = Ease(In, Cubic, frame, pos.y, AfterPos.y);
			enemyobj->SetPosition(pos);
		}
	}

	if (active) {
		AttackCount2++;
		if ((action % 2) == 0) {
			if (!Attack) {
				if (AttackCount2 == 90) {
					targetpos.x = player->GetPosition().x;
					targetpos.z = player->GetPosition().z;
				}
				else if (AttackCount2 >= 100) {
					Attack = true;
				}
				
			}
			else {
				XMFLOAT3 position{};
				position.x = (targetpos.x - pos.x);
				position.z = (targetpos.z - pos.z);
				rot.y = (atan2(position.x, position.z) * (180.0f / XM_PI)) - 90;// (XM_PI / 180.0f);
				pos.x -= sin(-atan2(position.x, position.z)) * 0.2f;
				pos.z += cos(-atan2(position.x, position.z)) * 0.2f;
			
			}
			enemyobj->SetPosition(pos);
		}
		if ((action % 2) == 1) {
			if (!Attack) {
				if (AttackCount2 == 90) {
					targetpos.x = player->GetPosition().x;
					targetpos.z = player->GetPosition().z;
				}
				else if (AttackCount2 >= 100) {
					Attack = true;
				}

			}
			else {
				XMFLOAT3 position{};
				position.x = (targetpos.x - pos.x);
				position.z = (targetpos.z - pos.z);
				rot.y = (atan2(position.x, position.z) * (180.0f / XM_PI)) - 90;// (XM_PI / 180.0f);
				pos.x -= sin(-atan2(position.x, position.z)) * 0.2f;
				pos.z += cos(-atan2(position.x, position.z)) * 0.2f;
			}
			enemyobj->SetPosition(pos);
		}

	}
}
