#include "InputManager.h"

/*
 * InputManager& InputManager::GetInstance()
 *
 * Método que implementa o padrão "Meyer's Singleton".
 */
InputManager& InputManager::GetInstance() {
	static InputManager manager;
	return manager;
}

InputManager::InputManager() {
	for (auto i : mouseState) {
		mouseState[i] = false;
	}
	for (auto i : mouseUpdate) {
		mouseUpdate[i] = 0;
	}
	quitRequested = false;
	updateCounter = 0;
	mouseX = 0;
	mouseY = 0;
}

InputManager::~InputManager() {

}

/*
 * void InputManager::Update()
 *
 * Atualiza os dados contidos na classe com base nos eventos ocorridos desde o último frame.
 */
void InputManager::Update() {
	SDL_Event event;
	int mouseButton, key, mousewheel;

	SDL_GetMouseState(&mouseX, &mouseY);
	quitRequested = false;
	updateCounter++;

	while (SDL_PollEvent(&event)) {
		// saida
		if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
			quitRequested = true;
		}

		// clique
		if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
			mouseButton = event.button.button;
			UpdateKeyOrButtonMaps(mouseButton, event, "mouse");
		}

		// tecla
		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
			if (event.key.repeat) continue;	// nao registra eventos repetidos
			key = event.key.keysym.sym;
			if (IsDirectional(key)) UpdateKeyOrButtonMaps(key, event, "keyboard");
			else if (event.key.repeat != 1) UpdateKeyOrButtonMaps(key, event, "keyboard");
		}

		// roda
		if (event.type == SDL_MOUSEWHEEL) {
			mousewheel = event.button.button;
			UpdateKeyOrButtonMaps(mousewheel, event, "wheel");
		}
	}
}

/*
 * bool InputManager::IsDirectional(int key)
 *
 * Retorna se tecla fornecida é uma tecla direcional.
 */
bool InputManager::IsDirectional(int key) {
	if (key == LEFT_ARROW_KEY || key == RIGHT_ARROW_KEY
	   || key == UP_ARROW_KEY || key == DOWN_ARROW_KEY) return true;
	return false;
}

/*
 * void InputManager::UpdateKeyOrButtonMaps(int index, SDL_Event event, string type)
 *
 * Atualiza mapas de teclas ou de botões do mouse.
 */
void InputManager::UpdateKeyOrButtonMaps(int index, SDL_Event event, string type) {
	if (type == "mouse") {
		mouseUpdate[index] = updateCounter;
		if (event.type == SDL_MOUSEBUTTONDOWN) mouseState[index] = true;
		if (event.type == SDL_MOUSEBUTTONUP) mouseState[index] = false;
	} else if (type == "keyboard") {
		keyUpdate[index] = updateCounter;
		if (event.type == SDL_KEYDOWN) keyState[index] = true;
		if (event.type == SDL_KEYUP) keyState[index] = false;
	} else if (type == "wheel") {
		if (event.type == SDL_MOUSEWHEEL) {
			mouseWheelUpdate = updateCounter;
			if (event.wheel.y > 0) mouseWheelState = 1;
			else if (event.wheel.y < 0) mouseWheelState = -1;
		}
	} else {
		cout << "Invalid type selected. Use 'mouse', 'keyboard' or 'wheel' only." << endl;
	}
}

/*
 * bool InputManager::KeyPress (int key)
 *
 * Retorna se tecla foi pressionada no último frame.
 */
bool InputManager::KeyPress(int key) {
	if (keyState[key] == true && keyUpdate[key] == updateCounter) return true;
	else return false;
}

/*
 * bool InputManager::KeyRelease(int key)
 *
 * Retorna se tecla foi solta no último frame.
 */
bool InputManager::KeyRelease(int key) {
	if (keyState[key] == false && keyUpdate[key] == updateCounter) return true;
	else return false;
}

/*
 * bool InputManager::IsKeyDown(int key)
 *
 * Retorna se tecla está pressionada atualmente.
 */
bool InputManager::IsKeyDown(int key) {
	if (keyState[key] == true) return true;
	else return false;
}

/*
 * bool InputManager::MousePress(int button)
 *
 * Retorna se botão do mouse foi pressionado no último frame.
 */
bool InputManager::MousePress(int button) {
	if (mouseState[button] == true && mouseUpdate[button] == updateCounter) return true;
	else return false;
}

/*
 * bool InputManager::MouseRelease(int button)
 *
 * Retorna se botão do mouse foi solto no último frame.
 */
bool InputManager::MouseRelease(int button) {
	if (mouseState[button] == false && mouseUpdate[button] == updateCounter) return true;
	else return false;
}

/*
 * bool InputManager::IsMouseDown(int button)
 *
 * Retorna se botão do mouse está pressionado atualmente.
 */
bool InputManager::IsMouseDown(int button) {
	if (mouseState[button] == true) return true;
	else return false;
}

/*
 * Retorna:
 * 		1 	- Roda foi rolada para cima
 * 		-1 	- Roda foi rolada para baixo
 * 		0 	- Roda não foi rolada
 */
bool InputManager::WheelRoll(string direction) {
	if (direction == "up" && mouseWheelState == 1 && mouseWheelUpdate == updateCounter) {
		mouseWheelState = 0;
		return true;
	} else if (direction == "down" && mouseWheelState == -1 && mouseWheelUpdate == updateCounter) {
		mouseWheelState = 0;
		return true;
	} else return false;
}

int InputManager::GetMouseX() {
	return mouseX;
}

int InputManager::GetMouseY() {
	return mouseY;
}

Vec2& InputManager::GetMousePoint() {
	return *new Vec2(mouseX, mouseY);
}

bool InputManager::QuitRequested() {
	return quitRequested;
}

/*
 * bool InputManager::MultiKeyPress(int quantity, SDL_Keycode k1, SDL_Keycode k2, SDL_Keycode k3)
 *
 * Detecta pressionamento simultâneo de 2 ou 3 teclas.
 * Retorna falso se quantity for diferente de 2 ou 3.
 */
bool InputManager::MultiKeyPress(int quantity, SDL_Keycode k1, SDL_Keycode k2, SDL_Keycode k3) {
	if (quantity == 2) {
		return ((KeyPress(k2) && IsKeyDown(k1)) ||
				(KeyPress(k1) && IsKeyDown(k2)));
	} else if (quantity == 3) {
		return ((KeyPress(k1) && IsKeyDown(k2) && IsKeyDown(k3)) ||
				(KeyPress(k2) && IsKeyDown(k1) && IsKeyDown(k3)) ||
				(KeyPress(k3) && IsKeyDown(k2) && IsKeyDown(k1)));
	} else {
		return false;
	}
}
