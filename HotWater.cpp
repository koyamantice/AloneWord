#include "HotWater.h"
#include "ImageManager.h"

void HotWater::Init() {
	hot = Texture::Create(ImageManager::Resporn, { 0,0,0 }, { 1,1,1 }, { 1,1,1,1 });
	hot->TextureCreate();
	hot->SetPosition({ 0.0f,0.0f,0.0f });
	hot->SetRotation({ 90.0f,0, 0 });
	hot->SetScale({ 0.3f,0.3f,0.3f }); 

}

void HotWater::Upda() {
	hot->Update();
}

void HotWater::Draw() {
	Texture::PreDraw();
	if (IsAlive) {
		hot->Draw();
	}
}

void HotWater::Set(const XMFLOAT3& pos) {
	IsAlive = true;
	hot->SetPosition(pos);
}

void HotWater::Final() {
	delete hot;
}
