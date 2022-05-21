#include "Human.h"
#include "LeftHand.h"
#include "RightHand.h"
#include <stdlib.h>

void Human::SetAttack() {
	if (lefthand->GetActive() == false && righthand->GetActive() == false) {
		if (AttackCount < 180) {
			AttackCount++;
		}
		else {
			action = (rand() % 2);
		}
	}
}