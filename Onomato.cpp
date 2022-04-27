#include "Onomato.h"

void Onomato::Init() {
}

void Onomato::Run(const int& num) {
	onomato = Texture::Create(num, { 0,0,0 }, { 1,1,1 }, { 1,1,1,1 });
	onomato->TextureCreate();

}

void Onomato::Draw() {
}
