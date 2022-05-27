#pragma once
class LeftShose;
class RightShose;

class Foot {
public:
	const int& GetAction() { return action; }
	const int& GetAttackCount() { return AttackCount; }
	const bool& GetActive() { return active; }
public:
	//Human();
	void init();
	void SetAttack(LeftShose* leftshose, RightShose* rightshose);

public:
	int AttackCount = 0;
	int action = 0;
	bool active = false;
	bool act = false;
	LeftShose* leftshose = nullptr;
	RightShose* rightshose = nullptr;
};