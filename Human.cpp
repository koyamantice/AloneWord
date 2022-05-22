#include "Human.h"
#include <stdlib.h>
#include "LeftHand.h"
#include "RightHand.h"

Human::Human() {
	lefthand = new LeftHand();
	righthand = new RightHand();
}
void Human::SetAttack() {
	if ((lefthand->GetActive() == true) && (righthand->GetActive() == true)) {
		if (AttackCount < 181) {
			AttackCount++;
		}
		else {
			action = (rand() % 2);
		}
	}
}