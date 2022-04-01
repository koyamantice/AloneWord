#include "Spawning.h"

Spawning::Spawning() {
	model = Model::CreateFromOBJ("chr_knight");
	object3d = new Object3d();

}

void Spawning::Initialize() {
	object3d = Object3d::Create();
	object3d->SetModel(model);
	object3d->SetPosition(pos);
	object3d->SetScale({ 1,1,1});

}

void Spawning::Update() {
	object3d->Update();
}

void Spawning::Finalize() {
	delete object3d;
}

void Spawning::Draw() {
	Object3d::PreDraw();
	object3d->Draw();
}
