#include "ExpandChange.h"
#include "ImageManager.h"
#include"Collision.h"
#include "DebugText.h"
#include "imgui.h"
ExpandChange::ExpandChange() {
	
	change = Sprite::Create(ImageManager::Change, { 0.0f,0.0f });
	change->SetPosition(pos);
	change->SetAnchorPoint({ 0.5f, 0.5f });
	//change->SetSize({ 2.5f,2.5f });
}

void ExpandChange::Update() {

	if (startchange) {
		Expand();
	}

	else {
		scale = 1.0f;
	}

	change->SetPosition(pos);

	change->SetScale(scale);
}

const void ExpandChange::Draw() {

	//ImGui::Begin("test");
	////ImGExpandChange::SliderFloat("HP", &BossHP, 50, 0.0f);
	///*ImGExpandChange::SliderFloat("angle", &angle, 200, -25);
	//ImGExpandChange::SliderFloat("rot.x", &rot.x, 360, -360);
	//ImGExpandChange::SliderFloat("rot.z", &rot.z, 360, -360);*/
	////ImGExpandChange::SliderFloat("rot.y", &frame, 360, -360);
	////ImGExpandChange::Text("Move:%d", appearMove);
	////ImGExpandChange::Text("Action:%d", action);
	////ImGExpandChange::Text("Active:%d", active);
	//////ImGExpandChange::Unindent();
	////ImGui::SliderFloat("scale", &scale, 2, 0);
	//ImGui::Text("Timer:%d", timer);
	//ImGui::Text("startchange:%d", startchange);
	//ImGui::End();
	//if (startchange || endchange) {
	//
	//}
	if (startchange) {
		change->Draw();
	}
	
}

void ExpandChange::Finalize() {
	delete change;
}

//ƒ{ƒX‚É‚æ‚Á‚ÄÕŒ‚”g‚ª‘–‚é
void ExpandChange::Expand() {
	scale = 1.1f;
	timer++;
	if (timer >= 60) {
		timer = 0;
		startchange = false;
	}

}

