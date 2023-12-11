#include "EndState.h"
#include "Game.h"
#include "Sprite.h"
#include "Music.h"
#include "Text.h"
#include "GameData.h"
#include "GeneralFunctions.h"

EndState::EndState(string opponent, string ambient) {
	quitRequested = false;
	this->opponent = opponent;
	this->ambient = ambient;
	flagInitialScreen = false;
	flagChoice = false;
}

EndState::~EndState() {

}

void EndState::LoadAssets() {
	LoadAmbient(ambient);

	LoadTextAndMusic();

	LoadOpponent(opponent);

	flagInitialScreen = true;
}

void EndState::LoadAmbient(string type) {
	GameObject* go_bg = new GameObject();
	string filename;

	if (type == "living room") {
		filename = "img/old_haunted_house_full_blur.png";
	}

	CreateAddSprite(go_bg, filename, 1, 0, *new Vec2(0,0), WINDOW_WIDTH, WINDOW_HEIGHT);
	AddObject(go_bg);
}

void EndState::LoadTextAndMusic() {
	Colors color = Colors::GetInstance();
	GameObject* textQuit = new GameObject();

	if (GameData::playerVictory) {
		// vitoria
		// carrega bg
		CreateAddText(textQuit, NK57, 90, "VITÓRIA!", -1, -1, color.white, 0);

		// carrega musica
		backgroundMusic.Open("audio/winMusic.mp3");
	} else {
		// derrota
		// carrega bg
		CreateAddText(textQuit, NK57, 90, "DERROTA!", -1, -1, color.white, 0);

		// carrega musica
		backgroundMusic.Open("audio/loseMusic.mp3");
	}

	textQuit->box.SetCenterPosition(*new Vec2(800,450));
	AddObject(textQuit);

	GameObject* textPrompt = new GameObject;
	CreateAddText(textPrompt, NK57, 50, "Pressione espaço para continuar", -1, -1, color.white, 0);
	textPrompt->box.SetCenterPosition(*new Vec2(800,550));
	AddObject(textPrompt);
}

void EndState::LoadOpponent(string type) {
	if (type == "diabrete") {
		// carrega sprite do diabrete dependendo de vitória ou derrota

		// carrega texto do diabrete
		// "Você não resistiu aos truques dos diabretes."
	}
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
	LoadAssets();
	backgroundMusic.Play();
	StartArray();
	started = true;
}

void EndState::Pause() {

}

void EndState::Resume() {

}
