#include "ImageManager.h"

ImageManager* ImageManager::GetIns() {
	static ImageManager instans;
	return &instans;
}

void ImageManager::Load2D() {
	// �e�N�X�`���ǂݍ���
	Sprite::LoadTexture(playerHp, L"Resources/2d/HPBar.png");
	Sprite::LoadTexture(arrow, L"Resources/2d/Arrow.png");
	Sprite::LoadTexture(arrow2, L"Resources/2d/Arrow2.png");
	Sprite::LoadTexture(life, L"Resources/2d/Life.png");
	Sprite::LoadTexture(concent, L"Resources/2d/concent.png");
	Sprite::LoadTexture(concent2, L"Resources/2d/concent2.png");
	Sprite::LoadTexture(concent3, L"Resources/2d/concent3.png");
	Sprite::LoadTexture(concent4, L"Resources/2d/concent4.png");
	Sprite::LoadTexture(concent5, L"Resources/2d/concent5.png");
	Sprite::LoadTexture(vignette, L"Resources/2d/Vignette.png");
	Sprite::LoadTexture(CLEAR, L"Resources/2d/GAMECLEAR.png");
	Sprite::LoadTexture(OVER, L"Resources/2d/GAMEOVER.png");
	Sprite::LoadTexture(TITLE, L"Resources/2d/TitleParts/layoutImage.png");
	Sprite::LoadTexture(SELECT, L"Resources/2d/kariSelect.png");
	Sprite::LoadTexture(SELECT1, L"Resources/2d/noSelect.png");
	Sprite::LoadTexture(playerhp, L"Resources/2d/HPBar.png");
	Sprite::LoadTexture(hpGauge, L"Resources/2d/HPGauge.png");
	Sprite::LoadTexture(energy, L"Resources/2d/HPmark_energy.png");
	Sprite::LoadTexture(pinch, L"Resources/2d/HPmark_pinch.png");
	Sprite::LoadTexture(weak, L"Resources/2d/HPmark_weak.png");
	Sprite::LoadTexture(select1, L"Resources/2d/Selected.png");
	Sprite::LoadTexture(select2, L"Resources/2d/kine_select.png");
	Sprite::LoadTexture(select3, L"Resources/2d/shoes_Select.png");
	Sprite::LoadTexture(select4, L"Resources/2d/washitu2.png");
	Sprite::LoadTexture(select5, L"Resources/2d/wayway.png");
	Sprite::LoadTexture(kitchen, L"Resources/2d/kitchen.png");
	Sprite::LoadTexture(genkan, L"Resources/2d/shoes_Sname.png");
	Sprite::LoadTexture(niwa, L"Resources/2d/kine_Sname.png");
	Sprite::LoadTexture(washitu, L"Resources/2d/washitu.png");
	Sprite::LoadTexture(wait, L"Resources/2d/wayway_Sname.png");
	Sprite::LoadTexture(meter, L"Resources/2d/hotWaterGauge.png");
	Sprite::LoadTexture(meterbar, L"Resources/2d/hotWaterBar.png");
	Sprite::LoadTexture(button, L"Resources/2d/select.png");
	Sprite::LoadTexture(num, L"Resources/2d/Num.png");
	Sprite::LoadTexture(bairitu, L"Resources/2d/Bairitu.png");
	Sprite::LoadTexture(Change, L"Resources/2d/Change.png");
	Sprite::LoadTexture(Change2, L"Resources/2d/Change2.png");
	Sprite::LoadTexture(BlackFilter, L"Resources/2d/Blackfilter.png");
	Sprite::LoadTexture(WhiteFilter, L"Resources/2d/Whitefilter.png");
	Sprite::LoadTexture(Tbutton, L"Resources/2d/Title1.png");
	Sprite::LoadTexture(Tselect, L"Resources/2d/TitleParts/menu.png");
	Sprite::LoadTexture(sky, L"Resources/2d/sky.png");
	Sprite::LoadTexture(ground, L"Resources/2d/ground.png");
	Sprite::LoadTexture(ok, L"Resources/2d/Ok.png");
	Sprite::LoadTexture(okSheet, L"Resources/2d/OkShit.png");
	Sprite::LoadTexture(text1, L"Resources/2d/text/text1.png");
	Sprite::LoadTexture(text2, L"Resources/2d/text/text2.png");
	Sprite::LoadTexture(text3, L"Resources/2d/text/text3.png");
	Sprite::LoadTexture(text4, L"Resources/2d/text/text4.png");
	Sprite::LoadTexture(text5, L"Resources/2d/text/text5.png");
	Sprite::LoadTexture(text6, L"Resources/2d/text/text6.png");
	Sprite::LoadTexture(text7, L"Resources/2d/text/text7.png");
	Sprite::LoadTexture(text8, L"Resources/2d/text/text8.png");
	Sprite::LoadTexture(text9, L"Resources/2d/text/text9.png");
	Sprite::LoadTexture(text10,L"Resources/2d/text/text10.png");
	Sprite::LoadTexture(text11,L"Resources/2d/text/text11.png");
	Sprite::LoadTexture(Enemyhp,  L"Resources/2d/EnemyHPBar.png");
	Sprite::LoadTexture(Enemyhp2, L"Resources/2d/EnemyHPDownBar.png");
	Sprite::LoadTexture(Enemyhp3, L"Resources/2d/EnemyHPGauge.png");
	Sprite::LoadTexture(SpinGauge, L"Resources/2d/spinGauge.png");
	Sprite::LoadTexture(SpinBar, L"Resources/2d/spinGaugeBar.png");




}

void ImageManager::LoadTex2D() {
	Texture::LoadTexture(enemy, L"Resources/2d/enemy.png");
	Texture::LoadTexture(shadow, L"Resources/2d/shadow.png");
	Texture::LoadTexture(Resporn, L"Resources/2d/Resporn.png");
	Texture::LoadTexture(effect2, L"Resources/2d/effect2.png");
	Texture::LoadTexture(effect3, L"Resources/2d/effect3.png");
	Texture::LoadTexture(playerhp, L"Resources/2d/HPBar.png");
	Texture::LoadTexture(magic, L"Resources/2d/magic2.png");
	Texture::LoadTexture(net, L"Resources/2d/motiNet.png");
	Texture::LoadTexture(water, L"Resources/2d/puddle.png");
	Texture::LoadTexture(Charge, L"Resources/2d/Charge.png");
	Texture::LoadTexture(ChargeEffect, L"Resources/2d/ChargeEffect.png");
	Texture::LoadTexture(spawnhp, L"Resources/2d/EHubHP.png");
	Texture::LoadTexture(SELECTTex, L"Resources/2d/kariSelect.png");
	Texture::LoadTexture(Stun, L"Resources/2d/stun.png");
}
