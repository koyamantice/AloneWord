#include "Spawning.h"

Spawning::Spawning() {
	model = Model::CreateFromOBJ("chr_knight");
	object3d = new Object3d();

}

void Spawning::Initialize() {
	object3d = Object3d::Create();
	object3d->SetModel(model);
	object3d->SetPosition(pos);
	object3d->SetScale({3,3,3});

}

void Spawning::Update() {
	object3d->Update();
	object3d->SetPosition(pos);
	if (sizeof(enemy)>0) {
		if (enemy[0]==nullptr) {
		} else {
			for (int i = 0; i < 10; i++) {
				enemy[i]->SetBasePos(pos);
				enemy[i]->Update();
			}
		}
	}

}

void Spawning::Finalize() {
	delete object3d;
}

void Spawning::Draw() {
	Object3d::PreDraw();
	object3d->Draw();
}

void Spawning::SetEnemy(const int& i, InterMob* enemy) {
	this->enemy[i] = enemy;
}
