#include"TisGame.h"
#define DIRECTINPUT_VERSION 0x0800

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	Framework* game=new TisGame();

	game->Run();

	delete game;

	return 0;
}