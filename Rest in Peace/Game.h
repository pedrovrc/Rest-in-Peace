#ifndef GAME_H
#define GAME_H

#include <bits/stdc++.h>
using namespace std;

#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include "State.h"
#include "InputManager.h"
#include "GameData.h"

#define GAME_TITLE "Pedro Victor Rodrigues de Carvalho 170113043"
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 600

/*
 * Classe Game
 *
 * Segue o padrão singleton, instanciada na função main e responsável por executar o jogo.
 */
class Game {
	int frameStart;
	float dt;
	static Game* instance;
	State* storedState;
	stack<unique_ptr<State>> stateStack;
	SDL_Window* window;
	SDL_Renderer* renderer;
	void CalculateDeltaTime();
public:
	Game(string title, int width, int height);
	~Game();
	void Run();
	SDL_Renderer* GetRenderer();
	State& GetCurrentState();
	void Push(State* state);
	static Game& GetInstance();
	float GetDeltaTime();
	GameData gameData;
};
#endif
