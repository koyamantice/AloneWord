#pragma once
#include "InterBoss.h"

class Spawning :public InterBoss {
public:
	Spawning();

	void Initialize(bool shadow = true) override;
	void Finalize() override;
	void Spec() override;
	void App(int Timer) override{};
	void specialDraw() override;

private:
	Texture* net[2] = { nullptr };
	Texture* texture = nullptr;
	XMFLOAT3 smooth{ pos.x, pos.y + 4.5f,pos.z };
};
