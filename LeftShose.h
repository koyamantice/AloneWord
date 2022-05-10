#pragma once
#include "InterBoss.h"

class LeftShose :public InterBoss {
public:
	LeftShose();

	void Initialize() override;
	void Finalize() override;
	void Spec() override;
	void App() override;
	void specialDraw() override;

private:

	float y = 0.0f;
	//‘Ò‹@ƒ‚[ƒVƒ‡ƒ“‚Ì‚½‚ß‚Ì‚â‚Â
	enum Motion {
		Up,
		Down
	};
	

};