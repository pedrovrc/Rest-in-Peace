#include "ExploreState.h"
#include "Sprite.h"
#include "Button.h"
#include "Text.h"
#include "InputManager.h"
#include "Game.h"
#include "CombatState.h"

ExploreState::ExploreState() {
	quitRequested = false;
	started = false;
}

ExploreState::~ExploreState() {
	while (objectArray.empty() == false) {
		objectArray.erase(objectArray.end() - 1);
	}
	objectArray.clear();
}

void ExploreState::LoadAssets() {
	// carrega imagem do fundo da tela
	LoadScreen();

	// carrega ilustracao de ambiente
	LoadAmbient("Placeholder");

	// carrega botão que leva para tela de combate
	LoadButton("combat");
}

void ExploreState::LoadScreen() {
	// Carrega imagem do fundo da tela
	GameObject* screen = new GameObject;
	Component* bg = new Sprite(*screen, "img/screens/dialoguescreen.png", 1, 0);
	screen->AddComponent(bg);
	screen->box.MoveThis(*new Vec2(0,0));
	AddObject(screen);
}

void ExploreState::LoadAmbient(string type) {
	// Carrega ilustração do fundo da tela
	GameObject* ambient = new GameObject;
	Component* bg;

	if (type == "Placeholder") {
		bg = new Sprite(*ambient, "img/living_room_crop.png", 1, 0);
	}

	ambient->AddComponent(bg);
	ambient->box.MoveThis(*new Vec2(0,0));
	AddObject(ambient);
}

void ExploreState::LoadButton(string type) {
	Colors color = Colors::GetInstance();

	GameObject* combat = new GameObject;

	Component* combatbutton = new Button(*combat, "main menu");
	combat->box.SetDimensions(505, 121);
	combat->box.SetCenterPosition(*new Vec2(800, 450));
	combat->AddComponent(combatbutton);

	Component* buttontext = new Text(*combat,
									"font/nk57-monospace-no-rg.otf", 40,
									Text::TextStyle::BLENDED,
									"Ir para combate",
									color.white, 0);
	combat->AddComponent(buttontext);

	AddObject(combat);
	button_list.push_back(combat);
}

void ExploreState::Update(float dt) {
	UpdateArray(dt);

	InputManager* input = &(InputManager::GetInstance());
	popRequested = input->QuitRequested();

	// implementa funcionalidade do botão
	Button* combatbutton = (Button*) button_list[0]->GetComponent("Button");

	if (combatbutton->IsHovered() && input->MousePress(LEFT_MOUSE_BUTTON)) {
		Game& game = game.GetInstance();
		State* state = (State*) new CombatState();
		game.Push(state);
	}
}

void ExploreState::Render() {
	this->RenderArray();
}

void ExploreState::Start() {
	LoadAssets();
}

void ExploreState::Pause() {

}

void ExploreState::Resume() {

}
