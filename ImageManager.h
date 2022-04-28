#pragma once
#include <map>
#include <string>
#include "Sprite.h"
#include "Texture.h"
class ImageManager  final {
private:
	ImageManager() = default;
	~ImageManager() = default;
	ImageManager(const ImageManager & r) = default;
	ImageManager& operator= (const ImageManager & r) = default;

public:

	enum texName {
		debugText,
		playerHp,//Sprite::LoadTexture(3, L"Resources/2d/PlayerHP.png");
		arrow,//Sprite::LoadTexture(4, L"Resources/2d/Arrow.png");
		life,//Sprite::LoadTexture(5, L"Resources/2d/Life.png");
		vignette,//Sprite::LoadTexture(6, L"Resources/2d/Vignette.png");
		concent,
		punyu,
		CLEAR,
		OVER,
		TITLE,
		SELECT
	};
	enum tex2dName {
	enemy,//Texture::LoadTexture(0, L"Resources/2d/enemy.png");
	shadow,//Texture::LoadTexture(1, L"Resources/2d/shadow.png");
	Resporn,//Texture::LoadTexture(2, L"Resources/2d/Resporn.png");
	effect2,//Texture::LoadTexture(3, L"Resources/2d/effect2.png");
	effect3,
	playerhp,//Texture::LoadTexture(4, L"Resources/2d/PlayerHP.png");
	magic,//Texture::LoadTexture(5, L"Resources/2d/magic2.png");
	net,//Texture::LoadTexture(6, L"Resources/2d/Resporn.png");
	
	
	};
public:
	static ImageManager* GetIns();		//Žæ“¾—p

	void Load2D();
	void LoadTex2D();

};

