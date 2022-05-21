#include "ShrinkChange.h"
#include "ImageManager.h"
#include"Collision.h"
#include "DebugText.h"
#include "imgui.h"
ShrinkChange::ShrinkChange() {

	change = Sprite::Create(ImageManager::Change2, { 0.0f,0.0f });
	change->SetPosition(pos);
	change->SetAnchorPoint({ 0.5f, 0.5f });
	//change->SetSize({ 2.5f,2.5f });
}

void ShrinkChange::Update() {

	//�t���O�����Ək�����n�܂�
	if (endchange) {
		Shrink();
	}

	else {
		scale = 1.0f;
	}

	change->SetPosition(pos);

	change->SetScale(scale);
}

const void ShrinkChange::Draw() {

	//ImGui::Begin("test");
	////ImGShrinkChange::SliderFloat("HP", &BossHP, 50, 0.0f);
	///*ImGShrinkChange::SliderFloat("angle", &angle, 200, -25);
	//ImGShrinkChange::SliderFloat("rot.x", &rot.x, 360, -360);
	//ImGShrinkChange::SliderFloat("rot.z", &rot.z, 360, -360);*/
	////ImGShrinkChange::SliderFloat("rot.y", &frame, 360, -360);
	////ImGShrinkChange::Text("Move:%d", appearMove);
	////ImGShrinkChange::Text("Action:%d", action);
	////ImGShrinkChange::Text("Active:%d", active);
	//////ImGShrinkChange::Unindent();
	////ImGui::SliderFloat("scale", &scale, 2, 0);
	//ImGui::Text("Timer:%d", timer);
	//ImGui::Text("endflag", endchange);
	//ImGui::End();
	//if (startchange || endchange) {
	//
	//}
	if (endchange) {
		change->Draw();
	}

}

void ShrinkChange::Finalize() {
	delete change;
}

//�V�[���؂�ւ�
void ShrinkChange::Shrink() {
	//�ʏ�T�C�Y��scale���������
	scale = 0.9f;
	timer++;
	//���̃T�C�Y(�����܂�)�܂ōs���Ək���������
	if (timer >= 70) {
		timer = 0;
		endchange = false;
	}
}

