#include "Colors.h"

Colors* Colors::instance;

Colors::Colors() {
	if (instance != nullptr) {
		cout << "ERRO: Jogo ja esta em execucao" << endl;
		return;
	}
	instance = this;

	white.r = 255;
	white.g = 255;
	white.b = 255;
	white.a = 255;

	gray.r = 127;
	gray.g = 127;
	gray.b = 127;
	gray.a = 127;

	black.r = 0;
	black.g = 0;
	black.b = 0;
	black.a = 0;
}

Colors& Colors::GetInstance() {
	if (instance == nullptr) {
		instance = new Colors();
	}
		return *instance;
}

