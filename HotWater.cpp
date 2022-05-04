#include "HotWater.h"
#include "ImageManager.h"
#include <Easing.h>

void HotWater::Init() {
	hot = Texture::Create(ImageManager::water, { 0,0,0 }, { 1,1,1 }, { 1,1,1,1 });
	hot->TextureCreate();
	hot->TextureCreate();
	hot->SetPosition({ 0.0f,-50.0f,0.0f });
	hot->SetRotation({ 90.0f,0, 0 });
	hot->SetScale({ 0.3f,0.3f,0.3f });

}

void HotWater::Upda() {
	hot->Update();
	if (IsAlive) {

	if(shrink) {
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
	} else {
		if(sca.x<0.5f) {
			sca.x += 0.02f;
			sca.y += 0.02f;
			sca.z += 0.02f;
		} else {
			if (!shrink) {
				shrink = true;
			}
		}
	}
	hot->SetScale(sca);
	if (sca.x <= 0.0f) {
		IsAlive = false;
		shrink = false;
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
		hot->SetPosition(pos);
		if (!IsAlive) {
			IsAlive = true;
		}
}

void HotWater::Final() {
	delete hot;
}
