#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <bits/stdc++.h>
using namespace std;

#define INCLUDE_SDL
#include "SDL_include.h"

#include "Vec2.h"

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT
#define SPACE_KEY SDLK_SPACE
#define A_KEY SDLK_a
#define D_KEY SDLK_d
#define P_KEY SDLK_p
#define S_KEY SDLK_s
#define W_KEY SDLK_w
#define Y_KEY SDLK_y
#define SHIFT_KEY SDLK_LSHIFT
#define CTRL_KEY SDLK_LCTRL

/*
 * Classe InputManager
 *
 * Responsável por encapsular todas as operações de aquisição de input.
 */
class InputManager {
	bool mouseState[6];
	int mouseUpdate[6];
	unordered_map<int,bool> keyState;
	unordered_map<int, int> keyUpdate;
	bool quitRequested;
	int updateCounter = 0;
	int mouseX;
	int mouseY;
	InputManager();
	~InputManager();
	void UpdateKeyOrButtonMaps( int index,
								SDL_Event event,
								string type);
	bool IsDirectional(int key);
public:
	void Update();
	bool KeyPress(int key);
	bool KeyRelease(int key);
	bool IsKeyDown(int key);
	bool MousePress(int button);
	bool MouseRelease(int button);
	bool IsMouseDown(int button);
	int GetMouseX();
	int GetMouseY();
	Vec2& GetMousePoint();
	bool QuitRequested();
	static InputManager& GetInstance();
	bool MultiKeyPress( int quantity,
						SDL_Keycode k1,
						SDL_Keycode k2,
						SDL_Keycode k3 = SDLK_0);
};

#endif
