#include "HotWater.h"
#include "ImageManager.h"
#include <Easing.h>

void HotWater::Init() {
	hot = Texture::Create(ImageManager::Resporn, { 0,0,0 }, { 1,1,1 }, { 1,1,1,1 });
	hot->TextureCreate();
	hot->SetPosition({ 0.0f,0.0f,0.0f });
	hot->SetRotation({ 90.0f,0, 0 });
	hot->SetScale({ 0.3f,0.3f,0.3f });

}

void HotWater::Upda() {
	hot->Update();
	if(IsAlive){
	if (frame < 1.0f) {
	frame += 0.002f;
	} else {
	frame = 0;
	}
	sca = {
	Ease(In,Quint,frame,(float)sca.x,(float)0),
	Ease(In,Quint,frame,(float)sca.y,(float)0),
	Ease(In,Quint,frame,(float)sca.z,(float)0),
	};
	hot->SetScale(sca);
	if (sca.x <= 0.0f) {
		IsAlive = false;
		sca = { 0.3f,0.3f,0.3f };
	}
	}
}

void HotWater::Draw() {
	Texture::PreDraw();
	if (IsAlive) {
		hot->Draw();
	}
}

void HotWater::Set(const XMFLOAT3& pos) {
	if (!IsAlive) {
		IsAlive = true;
		hot->SetPosition(pos);
	}
}

void HotWater::Final() {
	delete hot;
}
