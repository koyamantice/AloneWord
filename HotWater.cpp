#include "HotWater.h"
#include "ImageManager.h"

void HotWater::Init() {
	hot = Texture::Create(ImageManager::Resporn, { 0,0,0 }, { 12,12,12 }, { 1,1,1,0.6f });
	hot->TextureCreate();
	hot->SetPosition({ 0.0f,0.0f,0.0f });
	hot->SetRotation({ 0.0f,0, 0 });
	//limit->SetScale({ 6,5,5 }); 

}

void HotWater::Upda() {
	hot->Update();
}

void HotWater::Draw() {
	hot->Draw();
}

void HotWater::Final() {
	delete hot;
}
