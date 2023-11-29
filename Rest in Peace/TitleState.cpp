#include "TitleState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "ExploreState.h"
#include "Text.h"
#include "Button.h"
#include "GeneralFunctions.h"

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
		State* state = (State*) new ExploreState("intro");
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
	// START
	GameObject* startbutton = new GameObject;
	CreateAddButton(startbutton, "main menu", MENUBUTTON_W, MENUBUTTON_H,
					*new Vec2(MENUBUTTON_CENTER_X, MENUBUTTON_CENTER_Y), "start");
	AddObject(startbutton);
	button_list.push_back(startbutton);

	// LOAD
	GameObject* loadbutton = new GameObject;
	CreateAddButton(loadbutton, "main menu", MENUBUTTON_W, MENUBUTTON_H,
						*new Vec2(MENUBUTTON_CENTER_X, MENUBUTTON_CENTER_Y + MENUBUTTON_H), "load");
	AddObject(loadbutton);
	button_list.push_back(loadbutton);

	// OPTIONS
	GameObject* optionsbutton = new GameObject;
	CreateAddButton(optionsbutton, "main menu", MENUBUTTON_W, MENUBUTTON_H,
							*new Vec2(MENUBUTTON_CENTER_X, MENUBUTTON_CENTER_Y + 2 * MENUBUTTON_H), "options");
	AddObject(optionsbutton);
	button_list.push_back(optionsbutton);

	// CREDITS
	GameObject* creditsbutton = new GameObject;
	CreateAddButton(creditsbutton, "main menu", MENUBUTTON_W, MENUBUTTON_H,
								*new Vec2(MENUBUTTON_CENTER_X, MENUBUTTON_CENTER_Y + 3 * MENUBUTTON_H), "credits");
	AddObject(creditsbutton);
	button_list.push_back(creditsbutton);

	// QUIT
	GameObject* quitbutton = new GameObject;
	CreateAddButton(quitbutton, "main menu", MENUBUTTON_W, MENUBUTTON_H,
								*new Vec2(MENUBUTTON_CENTER_X, MENUBUTTON_CENTER_Y + 4 * MENUBUTTON_H), "quit");
	AddObject(quitbutton);
	button_list.push_back(quitbutton);

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
