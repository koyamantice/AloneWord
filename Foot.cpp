#include "Foot.h"
#include <stdlib.h>
#include "LeftShose.h"
#include "RightShose.h"
#include "LeftShose.h"

//Foot::Foot() {
//	
//}

void Foot::init() {
	leftshose = new LeftShose();
	rightshose = new RightShose();
}
void Foot::SetAttack(LeftShose* leftshose, RightShose* rightshose) {
	if ((leftshose->GetActive() == false) && (rightshose->GetActive() == false)) {
		leftshose->SetActive(false);
		rightshose->SetActive(false);
		if (AttackCount < 151) {
			AttackCount++;
		}
		else {
			if ((leftshose->GetHP() <= 0) || (rightshose->GetHP() <= 0)) {
				AttackCount = 30;
			}
			else {
				AttackCount = 0;
			}
			action = (rand() % 3);
			if ((leftshose->GetHP() <= 0) || (rightshose->GetHP() <= 0) && action == 1) {
				action = 0;
			}

			/*leftshose->SetActive(true);
			rightshose->SetActive(true);*/
		}
	}
}