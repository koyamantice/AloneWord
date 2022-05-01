#pragma once
#include "InterBoss.h"

class GreenTea :public InterBoss {
public:
	GreenTea();

	void Initialize() override;
	void Finalize() override;
	void Spec() override;
private:

	float y = 0.0f;
	//‘Ò‹@ƒ‚[ƒVƒ‡ƒ“‚Ì‚½‚ß‚Ì‚â‚Â
	enum Motion {
		Up,
		Down
	};
};