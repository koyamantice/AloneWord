#include "SceneChange.h"
#include "ImageManager.h"
#include"Collision.h"
#include "DebugText.h"
#include "imgui.h"
SceneChange::SceneChange() {
	
	change = Sprite::Create(ImageManager::TITLE, { 0.0f,0.0f });
	change->SetScale(scale);
	change->SetPosition(pos);
	change->SetAnchorPoint({ 0.5f, 0.5f });
}

void SceneChange::Update() {
	if (startchange) {
		ExpandChange();
	}

	if (endchange) {
		ShrinkChange();
	}

	change->SetPosition(pos);
	change->SetScale(scale);
}

const void SceneChange::Draw() {

	ImGui::Begin("test");
	//ImGSceneChange::SliderFloat("HP", &BossHP, 50, 0.0f);
	/*ImGSceneChange::SliderFloat("angle", &angle, 200, -25);
	ImGSceneChange::SliderFloat("rot.x", &rot.x, 360, -360);

	ImGSceneChange::SliderFloat("rot.z", &rot.z, 360, -360);*/
	//ImGSceneChange::SliderFloat("rot.y", &frame, 360, -360);
	//ImGSceneChange::Text("Move:%d", appearMove);
	//ImGSceneChange::Text("Action:%d", action);
	//ImGSceneChange::Text("Active:%d", active);
	////ImGSceneChange::Unindent();
	ImGui::SliderFloat("pos.x", &pos.x, 360, -360);
	ImGui::SliderFloat("pos.y", &pos.y, 360, -360);
	ImGui::SliderFloat("scale", &scale, 2, 0);
	ImGui::End();
	if (startchange || endchange) {
		
	}
	change->Draw();
}

void SceneChange::Finalize() {
	delete change;
}

//ƒ{ƒX‚É‚æ‚Á‚ÄÕŒ‚”g‚ª‘–‚é
void SceneChange::ExpandChange() {
	scale = 1.1f;
	timer++;
	if (timer >= 20) {
		startchange = false;
	}

}

void SceneChange::ShrinkChange() {
	scale = 0.9f;
	timer++;
	if (timer >= 20) {
		endchange = false;
	}
}

