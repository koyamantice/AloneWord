#include "ShockWave.h"
#include "ImageManager.h"

void ShockWave::Init() {
	wave = Texture::Create(ImageManager::Resporn, { 0,0,0 }, { 12,12,12 }, { 1,1,1,0.6f });
	wave->TextureCreate();
	wave->SetPosition({ 0.0f,0.0f,0.0f });
	wave->SetRotation({ 90.0f, 0.0f, 0.0f });
	wave->SetScale(scale);
	//limit->SetScale({ 6,5,5 }); 
}

void ShockWave::Upda(Pastel* pastel) {
	SetWave(pastel);
	wave->Update();
}

void ShockWave::Draw() {
	ImGui::Begin("test");
	ImGui::SliderFloat("pos.x", &pos.x, 25, -25);
	ImGui::Text("expand::%d", expand);
	////ImGui::Unindent();
	ImGui::End();
	if (expand) {
		wave->Draw();
	}
}

void ShockWave::Final() {
	delete wave;
}

//ƒ{ƒX‚É‚æ‚Á‚ÄÕŒ‚”g‚ª‘–‚é
void ShockWave::SetWave(Pastel* pastel) {
	int action = pastel->GetAction();
	XMFLOAT3 pos = pastel->GetPosition();
	if (action == 3 && pos.y == 0.0f && !expand) {
		this->pos = pos;
		expand = true;
	}

	if (expand == true) {
		scale.x += 0.01f;
		scale.y += 0.01f;
		scale.z += 0.01f;

		if (scale.x >= 50.0f) {
			expand = false;
			scale = { 0.0f,0.0f,0.0f };
		}
	}

	wave->SetPosition(this->pos);
	wave->SetScale(scale);
}
