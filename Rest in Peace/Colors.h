#ifndef COLORS_H
#define COLORS_H

#include <bits/stdc++.h>
using namespace std;

#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"


/*
 * Classe Colors
 *
 * Possui declarações de cores SDL usáveis.
 */

class Colors {
	static Colors* instance;
public:
	SDL_Color white;
	SDL_Color gray;
	SDL_Color black;
	SDL_Color red;

	Colors();
	static Colors& GetInstance();
};

#endif /* COLORS_H_ */
