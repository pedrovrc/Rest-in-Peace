#include "TitleState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "ExploreState.h"
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

	// implementa funcionalidade dos botões do menu
	Button* startbutton = (Button*) button_list[0]->GetComponent("Button");
	Button* loadbutton = (Button*) button_list[1]->GetComponent("Button");
	Button* optionsbutton = (Button*) button_list[2]->GetComponent("Button");
	Button* creditsbutton = (Button*) button_list[3]->GetComponent("Button");
	Button* quitbutton = (Button*) button_list[4]->GetComponent("Button");
	if (quitbutton->IsHovered() && input->MousePress(LEFT_MOUSE_BUTTON)) {
		quitRequested = true;
	}
	if (startbutton->IsHovered() && input->MousePress(LEFT_MOUSE_BUTTON)) {
		Game& game = game.GetInstance();
		State* state = (State*) new ExploreState();
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
	start->box.SetDimensions(MENUBUTTON_W, MENUBUTTON_H);
	start->box.SetCenterPosition(*new Vec2(MENUBUTTON_CENTER_X, MENUBUTTON_CENTER_Y));
	start->AddComponent(startbutton);
	AddObject(start);
	button_list.push_back(start);

	GameObject* load = new GameObject;
	Component* loadbutton = new Button(*load, "main menu");
	load->box.SetDimensions(MENUBUTTON_W, MENUBUTTON_H);
	load->box.SetCenterPosition(*new Vec2(MENUBUTTON_CENTER_X, MENUBUTTON_CENTER_Y + MENUBUTTON_H));
	load->AddComponent(loadbutton);
	AddObject(load);
	button_list.push_back(load);

	GameObject* options = new GameObject;
	Component* optionsbutton = new Button(*options, "main menu");
	options->box.SetDimensions(505, 121);
	options->box.SetCenterPosition(*new Vec2(MENUBUTTON_CENTER_X, MENUBUTTON_CENTER_Y + 2 * MENUBUTTON_H));
	options->AddComponent(optionsbutton);
	AddObject(options);
	button_list.push_back(options);

	GameObject* credits = new GameObject;
	Component* creditsbutton = new Button(*credits, "main menu");
	credits->box.SetDimensions(MENUBUTTON_W, MENUBUTTON_H);
	credits->box.SetCenterPosition(*new Vec2(MENUBUTTON_CENTER_X, MENUBUTTON_CENTER_Y + 3 * MENUBUTTON_H));
	credits->AddComponent(creditsbutton);
	AddObject(credits);
	button_list.push_back(credits);

	GameObject* quit = new GameObject;
	Component* quitbutton = new Button(*quit, "main menu");
	quit->box.SetDimensions(MENUBUTTON_W, MENUBUTTON_H);
	quit->box.SetCenterPosition(*new Vec2(MENUBUTTON_CENTER_X, MENUBUTTON_CENTER_Y + 4 * MENUBUTTON_H));
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
