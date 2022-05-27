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
		arrow2,
		life,//Sprite::LoadTexture(5, L"Resources/2d/Life.png");
		CLEAR,
		OVER,
		TITLE,
		SELECT1,
		hpGauge,
		energy,
		pinch,
		weak,
		select1,
		select2,
		select3,
		select4,
		select5,
		kitchen,
		genkan,
		niwa,
		washitu,
		shinshitu,
		meter,
		meterbar,
		button,
		num,
		bairitu,
		Change,
		Change2,
		BlackFilter,
		WhiteFilter,
		Tselect,
		sky,
		ground,
		ok,
		text1,
		text2,
		text3,
		text4,
		text5,
		text6,
		text7,
		text8,
		text9,
		text10,
		text11,
		text12,
		textSkip,
		Enemyhp,
		Enemyhp2,
		Enemyhp3,
		SpinGauge,
		SpinBar,
		GameOver,
		noBoss_Select,
		noBoss_Sname,
		hit,
		SPD
	};
	enum tex2dName {
	enemy,//Texture::LoadTexture(0, L"Resources/2d/enemy.png");
	shadow,//Texture::LoadTexture(1, L"Resources/2d/shadow.png");
	effect2,//Texture::LoadTexture(3, L"Resources/2d/effect2.png");
	effect3,
	net,//Texture::LoadTexture(6, L"Resources/2d/Resporn.png");
	water,
	Charge,
	ChargeEffect,
	spawnhp,
	SELECTTex,
	SELECTTex2,
	Stun,
	Hit,
	Attension,
	clearStage1,
	clearStage2,
	clearStage3,
	clearStage4,
	clearStage5,
	offStage1,
	offStage2,
	offStage3,
	offStage4,
	offStage5,
	onStage1,
	onStage2,
	onStage3,
	onStage4,
	onStage5,
	};
public:
	static ImageManager* GetIns();		//Žæ“¾—p

	void Load2D();
	void LoadTex2D();

};

