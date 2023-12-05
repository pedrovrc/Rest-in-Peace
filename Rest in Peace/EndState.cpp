#include "EndState.h"
#include "Game.h"
#include "Sprite.h"
#include "Music.h"
#include "Text.h"
#include "GameData.h"
#include "GeneralFunctions.h"

EndState::EndState() {
	quitRequested = false;
	Colors color = Colors::GetInstance();
	GameObject* go_textQuit = new GameObject();
	GameObject* go_bg = new GameObject();
	CreateAddSprite(go_bg, "img/living_room.jpg", 1, 0, *new Vec2(0,0), WINDOW_WIDTH, WINDOW_HEIGHT);
	AddObject(go_bg);

	if (GameData::playerVictory) {
		// vitoria
		// carrega bg
		CreateAddText(go_textQuit, NK57, 40, "YOU WIN!", -1, -1, color.white, 0);
		go_textQuit->box.SetCenterPosition(*new Vec2(800,450));

		AddObject(go_textQuit);
		// carrega musica
		//backgroundMusic.Open("audio/endStateWin.ogg");
	} else {
		// derrota
		// carrega bg
		CreateAddText(go_textQuit, NK57, 40, "YOU LOSE!", -1, -1, color.white, 0);
		go_textQuit->box.SetCenterPosition(*new Vec2(800,450));

		AddObject(go_textQuit);

		// carrega musica
		//backgroundMusic.Open("audio/endStateLose.ogg");
	}

	// carrega texto

	GameObject* go_textPlay = new GameObject();

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

}
