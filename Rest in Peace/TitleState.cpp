#include "TitleState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "CombatState.h"
#include "Camera.h"
#include "Text.h"

TitleState::TitleState() {
}

TitleState::~TitleState() {

}

void TitleState::Update(float dt) {
	UpdateArray(dt);

	InputManager* input = &(InputManager::GetInstance());
	quitRequested = input->QuitRequested();

	if (input->KeyPress(SPACE_KEY)) {
		Game& game = game.GetInstance();
		State* state = (State*) new CombatState();
		game.Push(state);
	}
}

void TitleState::LoadAssets() {
	GameObject* go = new GameObject();
	Component* bg = new Sprite(*go, "img/title.jpg", 1, 0);
	go->AddComponent(bg);
	go->box.MoveThis(*new Vec2(0,0));
	AddObject(go);

	GameObject* go_text = new GameObject();
	SDL_Color black;
	black.r = 0;
	black.g = 0;
	black.b = 0;
	black.a = 255;
	Text* text = new Text(*go_text,
						  "font/Call me maybe.ttf", 16,
						  Text::TextStyle::SOLID,
						  "Press SPACEBAR to start game",
						  black, 0.5);
	go_text->AddComponent((Component*) text);
	go_text->box.SetCenterPosition(*new Vec2(400,500));
	go_text->box.w = 500;
	go_text->box.h = 100;
	AddObject(go_text);
}

void TitleState::Render() {
	this->RenderArray();
}

void TitleState::Start() {
	LoadAssets();
}

void TitleState::Pause() {

}

void TitleState::Resume() {
	Camera::pos = *new Vec2(0,0);
}

weak_ptr<GameObject> TitleState::GetPlayerGO() {
	return weak_ptr<GameObject>();
}
