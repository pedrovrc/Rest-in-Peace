#include "TitleState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "CombatState.h"
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
	Component* bg = new Sprite(*go, "img/screens/mainmenu.png", 1, 0);
	go->AddComponent(bg);
	go->box.MoveThis(*new Vec2(0,0));
	AddObject(go);

	GameObject* go_text = new GameObject();
	SDL_Color white;
	white.r = 255;
	white.g = 255;
	white.b = 255;
	white.a = 255;
	Text* text = new Text(*go_text,
						  "font/nk57-monospace-no-rg.otf", 20,
						  Text::TextStyle::BLENDED,
						  "Aperte BARRA DE ESPACO para iniciar jogo",
						  white, 0.5);
	go_text->AddComponent((Component*) text);
	go_text->box.SetPosition(*new Vec2(1000,800));
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

}

weak_ptr<GameObject> TitleState::GetPlayerGO() {
	return weak_ptr<GameObject>();
}
