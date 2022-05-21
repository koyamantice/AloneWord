#pragma once
class LeftHand;
class RightHand;
class Human {
public:
	const int& GetAction() { return action; }
	const int& GetAttackCount() { return AttackCount; }
	const bool& GetActive() { return active; }
public:
	Human();
	void SetAttack();

public:
	int AttackCount = 0;
	int action = 0;
	bool active = false;
	LeftHand* lefthand = nullptr;
	RightHand* righthand = nullptr;
};