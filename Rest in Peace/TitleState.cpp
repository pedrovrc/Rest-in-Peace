#include "TitleState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "ExploreState.h"
#include "Text.h"
#include "Button.h"
#include "GeneralFunctions.h"

TitleState::TitleState() {
	tutorialOverlay = new GameObject;
	creditScreen = new GameObject;
	renderTutorial = false;
	renderCredits = false;
	creditsReturnButton.SetDimensions(120, 100);
	creditsReturnButton.SetPosition(*new Vec2(1380, 60));
}

TitleState::~TitleState() {

}

void TitleState::Update(float dt) {
	UpdateArray(dt);

	InputManager* input = &(InputManager::GetInstance());
	quitRequested = input->QuitRequested();

	// implementa funcionalidade dos botões do menu
	Button* startbutton = (Button*) button_list[0]->GetComponent("Button");
	Button* cardsbutton = (Button*) button_list[1]->GetComponent("Button");
	Button* tutorialbutton = (Button*) button_list[2]->GetComponent("Button");
	Button* creditsbutton = (Button*) button_list[3]->GetComponent("Button");
	Button* quitbutton = (Button*) button_list[4]->GetComponent("Button");

	if (input->MousePress(LEFT_MOUSE_BUTTON)) {
		if (renderCredits) {
			if (creditsReturnButton.Contains(input->GetMousePoint())) {
				renderCredits = false;
			}
		} else {
			if (startbutton->IsHovered()) {
				Game& game = game.GetInstance();
				State* state = (State*) new ExploreState("intro");
				game.Push(state);
			}
			if (tutorialbutton->IsHovered()) {
				renderTutorial = !renderTutorial;
			}
			if (creditsbutton->IsHovered()) {
				renderCredits = true;
			}
			if (quitbutton->IsHovered()) {
				quitRequested = true;
			}
		}
	}
}

void TitleState::LoadAssets() {
	// carrega imagem de fundo
	GameObject* go = new GameObject();
	CreateAddSprite(go, "img/screens/mainmenu.png", 1, 0, *new Vec2(0,0), -1, -1);
	AddObject(go);

	// carrega imagem de tutorial
	CreateAddSprite(tutorialOverlay, "img/screens/tutorial.png", 1, 0, *new Vec2(650, 300), -1, -1);

	// carrega iamgem de créditos
	CreateAddSprite(creditScreen, "img/screens/credits.png", 1, 0, *new Vec2(0, 0), -1, -1);

	// carrega botoes
	// START
	GameObject* startbutton = new GameObject;
	CreateAddButton(startbutton, "main menu", MENUBUTTON_W, MENUBUTTON_H,
					*new Vec2(MENUBUTTON_CENTER_X, MENUBUTTON_CENTER_Y), "start");
	AddObject(startbutton);
	button_list.push_back(startbutton);

	// CARDS
	GameObject* cardsbutton = new GameObject;
	CreateAddButton(cardsbutton, "main menu", MENUBUTTON_W, MENUBUTTON_H,
						*new Vec2(MENUBUTTON_CENTER_X, MENUBUTTON_CENTER_Y + MENUBUTTON_H), "load");
	AddObject(cardsbutton);
	button_list.push_back(cardsbutton);

	// TUTORIAL
	GameObject* tutorialbutton = new GameObject;
	CreateAddButton(tutorialbutton, "main menu", MENUBUTTON_W, MENUBUTTON_H,
							*new Vec2(MENUBUTTON_CENTER_X, MENUBUTTON_CENTER_Y + 2 * MENUBUTTON_H), "options");
	AddObject(tutorialbutton);
	button_list.push_back(tutorialbutton);

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
	if (renderTutorial) tutorialOverlay->Render();
	if (renderCredits) creditScreen->Render();
}

void TitleState::Start() {
	LoadAssets();
}

void TitleState::Pause() {

}

void TitleState::Resume() {

}
