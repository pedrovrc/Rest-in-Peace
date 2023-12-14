#include "Event.h"
#include "Colors.h"
#include "GeneralFunctions.h"
#include "ScrollerText.h"
#include "InputManager.h"
#include "Game.h"
#include "CombatState.h"

Event::Event(string type, ExploreState* state) {
	motherState = state;
	currentStage = 0;
	choiceActive = false;
	started = false;
	ended = false;
	passTime = false;
}

Event::~Event() {

}

void Event::LoadAssets() {
	// carrega texto do evento
	LoadText("event pt1");

	// carrega botões de opções dada a situação
	// ATUALMENTE : carrega botão de opção inicial da cena
	LoadButton("walk", "centered");

	currentStage = 1;
	started = true;
}

int Event::GetStage() {
	return currentStage;
}

bool Event::IsChoiceActive() {
	return choiceActive;
}

int Event::GetChoiceResult(int choiceID) {
	if (choiceID < (int)choiceArray.size() && choiceID >= 0)
		return choiceArray[choiceID];
	else
		return -1;
}

bool Event::Started() {
	return started;
}

bool Event::Ended() {
	return ended;
}

void Event::LoadText(string id) {
	Colors color = Colors::GetInstance();

	GameObject* newText = new GameObject;
	newText->box.SetPosition(*new Vec2(570,10));
	newText->box.SetDimensions(650, 600);

	string text;

	if (id == "event pt1") {
		text = ReadAllFromFile("text/eventoinicial1.txt");
	}

	if (id == "event pt2") {
		text = ReadAllFromFile("text/eventoinicial2.txt");
	}

	if (id == "event pt3") {
		text = ReadAllFromFile("text/eventoinicial3.txt");
	}

	if (id == "event pt4") {
		text = ReadAllFromFile("text/eventoinicial4.txt");
	}

	if (id == "event pt5") {
		text = ReadAllFromFile("text/eventoinicial5.txt");
	}

	if (id == "event end1") {
		text = ReadAllFromFile("text/eventoinicialfim1.txt");
	}

	if (id == "placeholder") {
		text = ReadAllFromFile("text/placeholder.txt");
	}

	Text* eventText = CreateAddText(newText, PETROV, REGULAR_SIZE, text, 650, 600, color.white, 0);

	Component* textScroller = new ScrollerText(*newText, eventText, id);
	newText->AddComponent(textScroller);

	motherState->AddObject(newText);
}

void Event::LoadButton(string id, string position) {
	Colors color = Colors::GetInstance();

	GameObject* button = new GameObject;
	CreateAddButton(button, "main menu", 505, 121, *new Vec2(0, 0), id);

	if (id == "walk") {
		CreateAddText(button, NK57, 40, "Ande um pouco mais", -1, -1, color.white, 0);
	}

	if (id == "name") {
		CreateAddText(button, NK57, 40, "Diga seu nome", -1, -1, color.white, 0);
	}

	if (id == "death") {
		CreateAddText(button, NK57, 40, "...elas morrem?", -1, -1, color.white, 0);
	}

	if (id == "take keys") {
		CreateAddText(button, NK57, 40, "Pegue as chaves", -1, -1, color.white, 0);
	}

	if (id == "training") {
		CreateAddText(button, NK57, 40, "Treinar", -1, -1, color.white, 0);
	}

	if (id == "skip") {
		CreateAddText(button, NK57, 40, "Pular treino", -1, -1, color.white, 0);
	}

	if (id == "explore") {
		CreateAddText(button, NK57, 40, "Explorar", -1, -1, color.white, 0);
	}

	if (id == "combat") {
		CreateAddText(button, NK57, 40, "Ir para combate", -1, -1, color.white, 0);
	}

	if (position == "centered") {
		button->box.SetCenterPosition(*new Vec2(900, 760));
	}
	if (position == "1 of 2") {
		button->box.SetCenterPosition(*new Vec2(900, 700));
	}
	if (position == "2 of 2") {
		button->box.SetCenterPosition(*new Vec2(900, 820));
	}

	motherState->AddButton(button);
}

Button* Event::GetButton(int index) {
	if (currentStage == 1) {
		if (index == 1) return motherState->GetButton("walk");
	}
	if (currentStage == 2) {
		if (index == 1) return motherState->GetButton("name");
	}
	if (currentStage == 3) {
		if (index == 1) return motherState->GetButton("death");
	}
	if (currentStage == 4) {
		if (index == 1) return motherState->GetButton("take keys");
	}
	if (currentStage == 5) {
		if (index == 1) return motherState->GetButton("training");
		if (index == 2) return motherState->GetButton("skip");
	}
	if (currentStage == 6) {
		if (index == 1) return motherState->GetButton("explore");
	}
	if (currentStage == 7) {
		if (GetChoiceResult(0) == 1) {
			return motherState->GetButton("combat");
		} else if (GetChoiceResult(0) == 2 && index == 1) {
			return motherState->GetButton("combat");
		}
	}

	return nullptr;
}

void Event::Update(float dt) {
	if (ended) {
		motherState->LoadCombatState();
	}

	InputManager* input = &(InputManager::GetInstance());

	// seleciona botões de acordo com estágio da cena
	Button* currentbutton = GetButton(1);;
	Button* currentbutton2 = nullptr;
	if (currentStage == 5) currentbutton2 = GetButton(2);

	if(currentStage == 5) choiceActive = true;
	else choiceActive = false;

	// implementa funcionamento dos botões
	// caso seja um estágio sem escolhas
	if (choiceActive == false) {
		if (currentbutton->IsHovered() && input->MousePress(LEFT_MOUSE_BUTTON)) {
			if (currentStage == 7) {
				ended = true;
			}

			if (currentStage == 6) {
				// passa tempo após escolha
				passTime = true;
				if (GetChoiceResult(0) == 1) {
					// executa tutorial aqui

				} else if (GetChoiceResult(0) == 2) {
					// pula tutorial
					motherState->DeleteButton("explore");
					motherState->DeleteText("event end1");
					LoadText("placeholder");
					LoadButton("combat", "centered");
				}
				currentStage = 7;
			}

			if (currentStage == 4) {
				motherState->DeleteText("event pt4");
				LoadText("event pt5");
				motherState->DeleteButton("take keys");
				LoadButton("training", "1 of 2");
				LoadButton("skip", "2 of 2");
				currentStage = 5;
			}

			if (currentStage == 3) {
				motherState->DeleteText("event pt3");
				LoadText("event pt4");
				motherState->DeleteButton("death");
				LoadButton("take keys", "centered");
				currentStage = 4;
			}

			if (currentStage == 2) {
				motherState->DeleteText("event pt2");
				LoadText("event pt3");
				motherState->DeleteButton("name");
				LoadButton("death", "centered");
				currentStage = 3;
			}

			if (currentStage == 1) {
				motherState->DeleteText("event pt1");
				LoadText("event pt2");
				motherState->DeleteButton("walk");
				LoadButton("name", "centered");
				currentStage = 2;
			}
		}
	} else {	// caso seja um estágio com escolhas
		if (currentStage == 5) {
			if (currentbutton->IsHovered() && input->MousePress(LEFT_MOUSE_BUTTON)) {	// botão 1 - treinamento
				choiceArray.push_back(1);
				motherState->DeleteButton("training");
				motherState->DeleteButton("skip");
				motherState->DeleteText("event pt5");
				LoadText("placeholder");
				LoadButton("combat", "centered");
				currentStage = 7;
			}
			if (currentbutton2->IsHovered() && input->MousePress(LEFT_MOUSE_BUTTON)) {	// botão 2 - pular
				choiceArray.push_back(2);
				motherState->DeleteButton("training");
				motherState->DeleteButton("skip");
				motherState->DeleteText("event pt5");
				LoadText("event end1");
				LoadButton("explore", "centered");
				currentStage = 6;
			}
		}
	}
}
