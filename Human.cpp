#include "Human.h"
#include <stdlib.h>

void Human::SetAttack() {
	if (AttackCount < 180) {
		AttackCount++;
	}
	else {
		action = (rand() % 2);
	}
}