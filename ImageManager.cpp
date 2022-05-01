#include "ImageManager.h"

ImageManager* ImageManager::GetIns() {
	static ImageManager instans;
	return &instans;
}

void ImageManager::Load2D() {
	// テクスチャ読み込み
	Sprite::LoadTexture(playerHp, L"Resources/2d/HPBar.png");
	Sprite::LoadTexture(arrow, L"Resources/2d/Arrow.png");
	Sprite::LoadTexture(life, L"Resources/2d/Life.png");
	Sprite::LoadTexture(concent, L"Resources/2d/concent.png");
	Sprite::LoadTexture(vignette, L"Resources/2d/Vignette.png");
	Sprite::LoadTexture(CLEAR, L"Resources/2d/GAMECLEAR.png");
	Sprite::LoadTexture(OVER, L"Resources/2d/GAMEOVER.png");
	Sprite::LoadTexture(TITLE, L"Resources/2d/title.png");
	Sprite::LoadTexture(SELECT, L"Resources/2d/kariSelect.png");
	Sprite::LoadTexture(playerhp, L"Resources/2d/HPBar.png");
	Sprite::LoadTexture(hpGauge, L"Resources/2d/HPGauge.png");
	Sprite::LoadTexture(energy, L"Resources/2d/HPmark_energy.png");
	Sprite::LoadTexture(pinch, L"Resources/2d/HPmark_pinch.png");
	Sprite::LoadTexture(weak, L"Resources/2d/HPmark_weak.png");

}

void ImageManager::LoadTex2D() {
	Texture::LoadTexture(enemy, L"Resources/2d/enemy.png");
	Texture::LoadTexture(shadow, L"Resources/2d/shadow.png");
	Texture::LoadTexture(Resporn, L"Resources/2d/Resporn.png");
	Texture::LoadTexture(effect2, L"Resources/2d/effect2.png");
	Texture::LoadTexture(effect3, L"Resources/2d/effect3.png");
	Texture::LoadTexture(magic, L"Resources/2d/magic2.png");
	Texture::LoadTexture(net, L"Resources/2d/motiNet.png");
	//Texture::LoadTexture(water, L"Resources/2d/motiNet.png");
	//Texture::LoadTexture(hit, L"Resources/2d/hit.png");

}
