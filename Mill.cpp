//#include "Mill.h"
//#include"Collision.h"
//#include<sstream>
//#include<iomanip>
//#include <Easing.h>
//#include"ImageManager.h"
//using namespace DirectX;
//
//Mill::Mill() {
//	model = ModelManager::GetIns()->GetModel(ModelManager::EHub);
//	enemyobj = new Object3d();
//}
//
//void Mill::Initialize() {
//	assert(player);
//	IsAlive = 0;
//	enemyobj = Object3d::Create();
//	enemyobj->SetModel(model);
//	pos = { 0.0f,-3.0f,0.0f };
//	enemyobj->SetPosition(pos);
//	rot = { 0,90,0 };
//	enemyobj->SetRotation(rot);
//	enemyobj->SetScale({ 5.5f,5.5f,5.5f });
//	texture = Texture::Create(ImageManager::shadow, { 0,0,0 }, { 0.5f,0.5f,0.5f }, { 1,1,1,1 });
//	texture->TextureCreate();
//	//texture->SetColor({ 1,1,1,1 });
//	texture->SetPosition(pos.x, -1, pos.z);
//	texture->SetRotation({ 90,0,0 });
//	texture->SetScale({ 0.3f,0.3f,0.3f });
//}
//
//void Mill::Finalize() {
//	//delete enemyobj;
//	delete texture;
//}
//
////ƒ{ƒX‚Ìs“®
//void Mill::Spec() {
//	if (haveEnemy >= 10.0f) {
//		haveTimer++;
//
//		if (haveTimer == 1000) {
//			haveTimer = 0;
//			haveEnemy = 0.0f;
//		}
//	}
//}
//
//void Mill::App() {
//
//}
//void Mill::specialDraw() {
//}
//
//bool Mill::collideAttackArm(Player* player) {
//	XMFLOAT3 Armpos = player->GetArmPosition();
//	bool attackflag = player->GetAttackFlag();
//	float weight = player->GetArmWeight();
//	if (attackflag && !BossHit) {
//		if (Collision::CircleCollision(Armpos.x, Armpos.z, 1.0,pos.x, pos.z, 1.0)) {
//			BossHit = true;
//			player->SetAttackFlag(false);
//			//–Ý‚ð‰P‚É“ü‚ê‚Ä‚¢‚é
//			if (BossHit == true) {
//				haveEnemy += weight;
//				weight = 0.0f;
//				player->SetArmWeight(weight);
//				BossHit = false;
//			}
//			return true;
//		}
//		else {
//			return false;
//		}
//	}
//	else {
//		return false;
//	}
//}
//
