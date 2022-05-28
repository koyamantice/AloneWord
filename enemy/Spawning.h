#pragma once
#include "InterBoss.h"

class Spawning :public InterBoss {
public:
	Spawning();

	void Initialize(bool shadow = true) override;
	void Finalize() override;
	void Spec() override;
	void App(int Timer) override{};
	void Roll(int Timer) override {};
	void specialDraw() override;
	void End(int Timer) override {};
private:
	unique_ptr<Texture> net[2] = { nullptr };
	unique_ptr<Texture> BossHp[1]{};
	XMFLOAT2 AfterPos[2]{};
	enum {
		now,
	};
	XMFLOAT3 smooth{ pos.x, pos.y + 4.5f,pos.z };
};
