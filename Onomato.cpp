#include "Onomato.h"

void Onomato::Init() {
	Texture::LoadTexture(punyu, L"Resources/2d/puni.png");
}

void Onomato::Run(const int& num) {
	onomato = Texture::Create(num, { 0,0,0 }, { 1,1,1 }, { 1,1,1,1 });
	onomato->TextureCreate();

}

void Onomato::Draw() {
}
