#pragma once
#include "Texture.h"
class Onomato {
	//static Onomato* GetInstance() {
	//	static Onomato instance;
	//	return &instance;
	//};
public:
	void Init();
	void Update();
	void Run();

	void Draw();
	enum tex2D {
		punyu,
		doka,
	};
private:
	Texture* onomato;

};

