#include "Human.h"
#include <stdlib.h>
#include "LeftHand.h"
#include "RightHand.h"

Human::Human() {
	lefthand = new LeftHand();
	righthand = new RightHand();
}
void Human::SetAttack() {
	if ((lefthand->GetActive() == false) && (righthand->GetActive() == false)) {
		if (AttackCount < 181) {
			AttackCount++;
		}
		else {
			AttackCount = 0;
			action = (rand() % 2);
		}
	}
}