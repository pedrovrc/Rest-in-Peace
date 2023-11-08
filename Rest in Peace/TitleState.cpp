#include "TitleState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "CombatState.h"
#include "Text.h"
#include "Button.h"

TitleState::TitleState() {

}

TitleState::~TitleState() {

}

void TitleState::Update(float dt) {
	UpdateArray(dt);

	InputManager* input = &(InputManager::GetInstance());
	quitRequested = input->QuitRequested();
	GameObject* startbutton = button_list[0];
	GameObject* quitbutton = button_list[4];

	if (quitbutton->box.Contains(input->GetMousePoint()) && input->MousePress(LEFT_MOUSE_BUTTON)) {
		quitRequested = true;
	}

	if (startbutton->box.Contains(input->GetMousePoint()) && input->MousePress(LEFT_MOUSE_BUTTON)) {
		Game& game = game.GetInstance();
		State* state = (State*) new CombatState();
		game.Push(state);
	}
}

void TitleState::LoadAssets() {
	// carrega imagem de fundo
	GameObject* go = new GameObject();
	Component* bg = new Sprite(*go, "img/screens/mainmenu.png", 1, 0);
	go->AddComponent(bg);
	go->box.MoveThis(*new Vec2(0,0));
	AddObject(go);

	// carrega botoes
	GameObject* start = new GameObject;
	Component* startbutton = new Button(*start, "main menu");
	start->box.SetDimensions(505, 121);
	start->box.SetCenterPosition(*new Vec2(320, 355));
	start->AddComponent(startbutton);
	AddObject(start);
	button_list.push_back(start);

	GameObject* load = new GameObject;
	Component* loadbutton = new Button(*load, "main menu");
	load->box.SetDimensions(505, 121);
	load->box.SetCenterPosition(*new Vec2(320, 476));
	load->AddComponent(loadbutton);
	AddObject(load);
	button_list.push_back(load);

	GameObject* options = new GameObject;
	Component* optionsbutton = new Button(*options, "main menu");
	options->box.SetDimensions(505, 121);
	options->box.SetCenterPosition(*new Vec2(320, 597));
	options->AddComponent(optionsbutton);
	AddObject(options);
	button_list.push_back(options);

	GameObject* credits = new GameObject;
	Component* creditsbutton = new Button(*credits, "main menu");
	credits->box.SetDimensions(505, 121);
	credits->box.SetCenterPosition(*new Vec2(320, 718));
	credits->AddComponent(creditsbutton);
	AddObject(credits);
	button_list.push_back(credits);

	GameObject* quit = new GameObject;
	Component* quitbutton = new Button(*quit, "main menu");
	quit->box.SetDimensions(505, 121);
	quit->box.SetCenterPosition(*new Vec2(320, 839));
	quit->AddComponent(quitbutton);
	AddObject(quit);
	button_list.push_back(quit);

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
