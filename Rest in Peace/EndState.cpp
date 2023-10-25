#include "EndState.h"
#include "Game.h"
#include "Sprite.h"
#include "Music.h"
#include "Text.h"
#include "GameData.h"
#include "Camera.h"

EndState::EndState() {
	quitRequested = false;

	if (GameData::playerVictory) {
		// vitoria
		// carrega bg
		GameObject* go_bg = new GameObject();
		Component* bg = new Sprite(*go_bg, "img/win.jpg", 1, 0);
		go_bg->AddComponent(bg);
		go_bg->box.MoveThis(*new Vec2(0,0));
		AddObject(go_bg);

		// carrega musica
		backgroundMusic.Open("audio/endStateWin.ogg");
	} else {
		// derrota
		// carrega bg
		GameObject* go_bg = new GameObject();
		Component* bg = new Sprite(*go_bg, "img/lose.jpg", 1, 0);
		go_bg->AddComponent(bg);
		go_bg->box.MoveThis(*new Vec2(0,0));
		AddObject(go_bg);

		// carrega musica
		backgroundMusic.Open("audio/endStateLose.ogg");
	}

	// carrega texto
	GameObject* go_textQuit = new GameObject();
	SDL_Color black;
	black.r = 0;
	black.g = 0;
	black.b = 0;
	black.a = 255;
	Text* textQuit = new Text(*go_textQuit,
						  "font/Call me maybe.ttf", 16,
						  Text::TextStyle::SOLID,
						  "Press ESC to quit",
						  black, 0.5);
	go_textQuit->AddComponent((Component*) textQuit);
	go_textQuit->box.SetPosition(*new Vec2(250,500));
	go_textQuit->box.w = 500;
	go_textQuit->box.h = 100;
	AddObject(go_textQuit);

	GameObject* go_textPlay = new GameObject();
	Text* textPlay = new Text(*go_textPlay,
						  "font/Call me maybe.ttf", 16,
						  Text::TextStyle::SOLID,
						  "Press SPACEBAR to play again",
						  black, 0.5);
	go_textPlay->AddComponent((Component*) textPlay);
	go_textPlay->box.SetPosition(*new Vec2(250,450));
	go_textPlay->box.w = 500;
	go_textPlay->box.h = 100;
	AddObject(go_textPlay);

}

EndState::~EndState() {

}

void EndState::LoadAssets() {

}

void EndState::Update(float dt) {
	InputManager* input = &(InputManager::GetInstance());
	UpdateArray(dt);

	// checa por jogar novamente
	if (input->KeyPress(SPACE_KEY)) {
		popRequested = true;
	}

	// checa por quit
	if (input->QuitRequested() || input->KeyPress(ESCAPE_KEY)) {
		quitRequested = true;
	}
}

void EndState::Render() {
	RenderArray();
}

void EndState::Start() {
	backgroundMusic.Play();
	LoadAssets();
	StartArray();
	started = true;
}

void EndState::Pause() {

}

void EndState::Resume() {
	Camera::pos.x = 0;
	Camera::pos.y = 0;
}

/*
 * 	weak_ptr<GameObject> StageState::GetPlayerGO()
 *
 * 	Retorna weak_ptr apontando para o GO do player.
 */
weak_ptr<GameObject> EndState::GetPlayerGO() {
	int i = 0;
	while (objectArray.begin() + i != objectArray.end()) {
		if (objectArray[i].get()->GetComponent("PenguinBody") != nullptr) return weak_ptr<GameObject>(objectArray[i]);
		i++;
	}
	return weak_ptr<GameObject>();
}


