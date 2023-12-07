#include "ExploreState.h"
#include "Sprite.h"
#include "Text.h"
#include "InputManager.h"
#include "Game.h"
#include "CombatState.h"
#include "ScrollerText.h"
#include "GeneralFunctions.h"
#include "IntroState.h"

ExploreState::ExploreState(string type) {
	quitRequested = false;
	started = false;
	if (type == "intro") intro = true;
	else intro = false;
	currentStage = 0;
	choiceActive = false;
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

	// carrega ilustrações e dados do painel do player
	LoadPlayerProfile();

	// carrega texto do local
	LoadText("event pt1");

	// carrega botões de opções dada a situação
	// ATUALMENTE : carrega botão de opção inicial da cena
	LoadButton("name", "centered");

	currentStage = 1;
}

void ExploreState::LoadExecIntro() {
	//cria estado IntroState e coloca na pilha
	Game& game = game.GetInstance();
	State* state = (State*) new IntroState();
	game.Push(state);
}

void ExploreState::LoadScreen() {
	// Carrega imagem do fundo da tela
	GameObject* screen = new GameObject;
	CreateAddSprite(screen, "img/screens/dialoguescreen.png", 1, 0, *new Vec2(0,0), -1, -1);
	AddObject(screen);
}

void ExploreState::LoadAmbient(string type) {
	// Carrega ilustração do fundo da tela
	GameObject* ambient = new GameObject;
	string filename;
	if (type == "Placeholder") {
		filename = "img/living_room_crop.png";
	}
	CreateAddSprite(ambient, filename, 1, 0, *new Vec2(0,0), -1, -1);
	AddObject(ambient);
}

void ExploreState::LoadPlayerProfile() {
	Colors& color = Colors::GetInstance();

	// carrega avatar do player
	GameObject* avatar = new GameObject;
	CreateAddSprite(avatar, "img/MC/avatar v2.png", 1, 0,
					*new Vec2(AVATAR_POS_X, AVATAR_POS_Y), -1, -1);
	AddObject(avatar);

	// carrega textos
	// carrega nome
	GameObject* name = new GameObject;
	CreateAddText(name, "nk57-monospace-no-rg.otf", 40, "Sofia", -1, -1, color.white, 0);
	name->box.SetCenterPosition(*new Vec2(1505, 40));
	AddObject(name);

	Player* player = Player::GetInstance();

	// Carrega HUD HP -------------------
	// barra vermelha
	GameObject* redbar = new GameObject;
	CreateAddSprite(redbar, "img/resources/red bar.png", 1, 0,
					*new Vec2(HUD_POS_X, HUD_POS_Y), HUDBAR_W, HUDBAR_H);
	AddObject(redbar);

	// barra verde
	GameObject* hpbar = new GameObject;
	CreateAddSprite(hpbar, "img/resources/green bar.png", 1, 0,
					*new Vec2(HUD_POS_X, HUD_POS_Y),
					HUDBAR_W * ((float)player->GetHP()/PLAYER_MAX_HP), HUDBAR_H);
	playerData.push_back(hpbar);

	// string na barra
	string hp = "Vida: " + to_string(player->GetHP()) + "/" + to_string(PLAYER_MAX_HP);
	GameObject* go_hpdata = new GameObject();
	CreateAddText(go_hpdata, NK57, 15, hp, -1, -1, color.white, 0);
	go_hpdata->box.SetCenterPosition(redbar->box.GetCenter());
	playerData.push_back(go_hpdata);

	// Carrega HUD SP -----------------------
	// barra cinza.
	GameObject* graybar = new GameObject;
	CreateAddSprite(graybar, "img/resources/gray bar.png", 1, 0,
			*new Vec2(HUD_POS_X, HUD_POS_Y + HUD_Y_OFFSET), HUDBAR_W, HUDBAR_H);
	AddObject(graybar);

	// barra branca
	GameObject* spbar = new GameObject;
	CreateAddSprite(spbar, "img/resources/white bar.png", 1, 0,
				*new Vec2(HUD_POS_X, HUD_POS_Y + HUD_Y_OFFSET),
				HUDBAR_W * ((float)player->GetSP()/PLAYER_MAX_SP), HUDBAR_H);
	playerData.push_back(spbar);

	// string na barra
	string sp = "Sanidade: " + to_string(player->GetSP()) + "/" + to_string(PLAYER_MAX_SP);
	GameObject* go_spdata = new GameObject();
	CreateAddText(go_spdata, NK57, 15, sp, -1, -1, color.black, 0);
	go_spdata->box.SetCenterPosition(graybar->box.GetCenter());
	playerData.push_back(go_spdata);
}

void ExploreState::LoadText(string id) {
	Colors color = Colors::GetInstance();

	GameObject* newText = new GameObject;
	newText->box.SetPosition(*new Vec2(570,10));

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

	if (id == "event end1") {
		text = ReadAllFromFile("text/eventoinicialfim1.txt");
	}

	if (id == "placeholder") {
		text = ReadAllFromFile("text/placeholder.txt");
	}

	Text* eventText = CreateAddText(newText, PETROV, REGULAR_SIZE, text, 650, 600, color.white, 0);

	Component* textScroller = new ScrollerText(*newText, eventText, id);
	newText->AddComponent(textScroller);

	AddObject(newText);

}

void ExploreState::DeleteText(string id) {
	if (id == "") return;

	Component* cpt = nullptr;
	GameObject* go;
	for (int i = 0; i < objectArray.size(); i++) {
		go = objectArray[i].get();
		cpt = go->GetComponent("ScrollerText");
		if (cpt != nullptr && ((ScrollerText*)cpt)->GetID() == id) {
			DeleteObject(go);
		}
	}
}

void ExploreState::LoadButton(string id, string position) {
	Colors color = Colors::GetInstance();

	GameObject* button = new GameObject;
	CreateAddButton(button, "main menu", 505, 121, *new Vec2(0, 0), id);

	if (id == "name") {
		CreateAddText(button, NK57, 40, "Diga seu nome", -1, -1, color.white, 0);
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

	AddObject(button);
	button_list.push_back(button);
}

void ExploreState::DeleteButton(string id) {
	if (id == "") return;

	Component* cpt = nullptr;
	for (int i = 0; i < button_list.size(); i++) {
		cpt = button_list[i]->GetComponent("Button");
		if (cpt != nullptr && ((Button*)cpt)->GetID() == id) {
			button_list.erase(button_list.begin() + i);
		}
	}
	GameObject* go;
	cpt = nullptr;
	for (int i = 0; i < objectArray.size(); i++) {
		go = objectArray[i].get();
		cpt = go->GetComponent("Button");
		if (cpt != nullptr && ((Button*)cpt)->GetID() == id) {
			DeleteObject(go);
		}
	}
}

void ExploreState::Update(float dt) {
	UpdateArray(dt);

	InputManager* input = &(InputManager::GetInstance());
	popRequested = input->QuitRequested();

	// seleciona botões de acordo com estágio da cena
	Button* currentbutton = GetButton(1);;
	Button* currentbutton2 = nullptr;
	if (currentStage == 3) currentbutton2 = GetButton(2);

	if(currentStage == 3) choiceActive = true;
	else choiceActive = false;

	// implementa funcionamento dos botões
	// caso seja um estágio sem escolhas
	if (choiceActive == false) {
		if (currentbutton->IsHovered() && input->MousePress(LEFT_MOUSE_BUTTON)) {
			if (currentStage == 5) {
				Game& game = game.GetInstance();
				State* state = (State*) new CombatState();
				game.Push(state);
			}

			if (currentStage == 4) {
				if (GetChoiceResult(0) == 1) {

				} else if (GetChoiceResult(0) == 2) {
					DeleteButton("explore");
					DeleteText("event end1");
					LoadText("placeholder");
					LoadButton("combat", "centered");
				}
				currentStage = 5;
			}

			if (currentStage == 2) {
				DeleteText("event pt2");
				LoadText("event pt3");
				DeleteButton("take keys");
				LoadButton("training", "1 of 2");
				LoadButton("skip", "2 of 2");
				currentStage = 3;
			}

			if (currentStage == 1) {
				DeleteText("event pt1");
				LoadText("event pt2");
				DeleteButton("name");
				LoadButton("take keys", "centered");
				currentStage = 2;
			}
		}
	} else {	// caso seja um estágio com escolhas
		if (currentStage == 3) {
			if (currentbutton->IsHovered() && input->MousePress(LEFT_MOUSE_BUTTON)) {	// botão 1 - treinamento
				cout << "botão 1" << endl;
				choiceArray.push_back(1);
			}
			if (currentbutton2->IsHovered() && input->MousePress(LEFT_MOUSE_BUTTON)) {	// botão 2 - pular
				cout << "botão 2" << endl;
				choiceArray.push_back(2);
				DeleteButton("training");
				DeleteButton("skip");
				DeleteText("event pt3");
				LoadText("event end1");
				LoadButton("explore", "centered");
				currentStage = 4;
			}
		}
	}
}

int ExploreState::GetChoiceResult(int choiceID) {
	return choiceArray[choiceID];
}

Button* ExploreState::GetButton(int index) {
	Button* button;

	if (currentStage == 1) {
		if (index == 1) {
			for (int i = 0; i < button_list.size(); i++) {
				button = (Button*) button_list[i]->GetComponent("Button");
				if (button->GetID() == "name") return button;;
			}
			return nullptr;
		}
		if (index == 2) return nullptr;
	}
	if (currentStage == 2) {
		if (index == 1) {
			for (int i = 0; i < button_list.size(); i++) {
				button = (Button*) button_list[i]->GetComponent("Button");
				if (button->GetID() == "take keys") return button;;
			}
			return nullptr;
		}
		if (index == 2) return nullptr;
	}
	if (currentStage == 3) {
		if (index == 1) {
			for (int i = 0; i < button_list.size(); i++) {
				button = (Button*) button_list[i]->GetComponent("Button");
				if (button->GetID() == "training") return button;;
			}
			return nullptr;
		}
		if (index == 2) {
			for (int i = 0; i < button_list.size(); i++) {
				button = (Button*) button_list[i]->GetComponent("Button");
				if (button->GetID() == "skip") return button;;
			}
			return nullptr;
		}
	}
	if (currentStage == 4) {
		if (index == 1) {
			for (int i = 0; i < button_list.size(); i++) {
				button = (Button*) button_list[i]->GetComponent("Button");
				if (button->GetID() == "explore") return button;;
			}
			return nullptr;
		}
		if (index == 2) return nullptr;
	}
	if (currentStage == 5) {
		if (GetChoiceResult(0) == 1) {

		} else if (GetChoiceResult(0) == 2) {
			if (index == 1) {
				for (int i = 0; i < button_list.size(); i++) {
					button = (Button*) button_list[i]->GetComponent("Button");
					if (button->GetID() == "combat") return button;;
				}
				return nullptr;
			}
			if (index == 2) return nullptr;
		}
	}

	return nullptr;
}

void ExploreState::Render() {
	this->RenderArray();
	this->RenderPlayerData();
}

void ExploreState::RenderPlayerData() {
	for (int i = 0; i < (int)playerData.size(); i++) {
		playerData[i]->Render();
	}
}

void ExploreState::Start() {
	// carrega e executa cutscene inicial
	if (intro) LoadExecIntro();

	LoadAssets();
}

void ExploreState::Pause() {

}

void ExploreState::Resume() {
	if (intro == true) intro = false;
}
