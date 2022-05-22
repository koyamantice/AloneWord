#include "Human.h"
#include <stdlib.h>
#include "LeftHand.h"
#include "RightHand.h"

//Human::Human() {
//	
//}

void Human::init() {
	lefthand = new LeftHand();
	righthand = new RightHand();
}
void Human::SetAttack(LeftHand* lefthand, RightHand* righthand) {
	if ((lefthand->GetActive() == false) && (righthand->GetActive() == false)) {
		lefthand->SetActive(false);
		righthand->SetActive(false);
		if (AttackCount < 181) {
			AttackCount++;
		}
		else {
			AttackCount = 0;
			action = (rand() % 2);
			/*lefthand->SetActive(true);
			righthand->SetActive(true);*/
		}
	}
}