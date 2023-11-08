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
	GameObject* startbutton;

	for (int i = 0; i < (int)objectArray.size(); i++) {
		if (objectArray[i]->GetComponent("Button") != nullptr) {
			startbutton = objectArray[i].get();
		}
	}

	if (input->MousePress(LEFT_MOUSE_BUTTON) && startbutton->box.Contains(input->GetMousePoint())) {
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

	GameObject* startbutton = new GameObject;
	startbutton->box.SetDimensions(505, 121);
	startbutton->box.MoveThis(*new Vec2(70, 295));
	Component* button = new Button(*startbutton);
	startbutton->AddComponent(button);
	AddObject(startbutton);
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
