#include "Onomato.h"
#include "ImageManager.h"

void Onomato::Init() {
	onomato = Texture::Create(ImageManager::smoke, { 0,0,0 }, { 1,1,1 }, { 1,1,1,1 });
	onomato->TextureCreate();
}

void Onomato::Update() {
	onomato->Update();
}

void Onomato::Run() {


}

void Onomato::Draw() {
	Texture::PreDraw();
	onomato->Draw();
}
