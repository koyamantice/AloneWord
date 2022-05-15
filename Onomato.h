#pragma once
#include "Texture.h"
class Onomato {
	static Onomato* GetInstance() {
		static Onomato instance;
		return &instance;
	};

	void Init();

	void Run(const int& num);

	void Draw();
	enum tex2D {
		punyu,
		doka,
	};

	Texture* onomato;

};

