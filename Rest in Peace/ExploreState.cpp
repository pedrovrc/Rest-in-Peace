#include "ExploreState.h"
#include "Sprite.h"
#include "Button.h"
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
	LoadText(1);

	// carrega botões de opções dada a situação
	// ATUALMENTE : carrega botão de opção inicial da cena
	LoadButton("name");

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

void ExploreState::LoadText(int part) {
	Colors color = Colors::GetInstance();

	if (part == 1) {
		GameObject* event = new GameObject;
		event->box.SetPosition(*new Vec2(570,10));

		string text = ReadAllFromFile("text/eventoinicial1.txt");
		Text* eventText = CreateAddText(event, PETROV, 20, text, 650, 600, color.white, 0);

		Component* textScroller = new ScrollerText(*event, eventText, "texto evento pt1");
		event->AddComponent(textScroller);

		AddObject(event);
	}

	if (part == 2) {
		// deleta texto antigo
		Component* cpt = nullptr;
		GameObject* go;
		for (int i = 0; i < objectArray.size(); i++) {
			go = objectArray[i].get();
			cpt = go->GetComponent("ScrollerText");
			if (cpt != nullptr && ((ScrollerText*)cpt)->GetID() == "texto evento pt1") {
				DeleteObject(go);
			}
		}

		GameObject* event = new GameObject;
		event->box.SetPosition(*new Vec2(570,10));

		string text = ReadAllFromFile("text/eventoinicial2.txt");
		Text* eventText = CreateAddText(event, PETROV, 20, text, 650, 600, color.white, 0);

		Component* textScroller = new ScrollerText(*event, eventText, "texto evento pt2");
		event->AddComponent(textScroller);

		AddObject(event);
	}

	if (part == 3) {
		// deleta texto antigo
		Component* cpt = nullptr;
		GameObject* go;
		for (int i = 0; i < objectArray.size(); i++) {
			go = objectArray[i].get();
			cpt = go->GetComponent("ScrollerText");
			if (cpt != nullptr && ((ScrollerText*)cpt)->GetID() == "texto evento pt2") {
				DeleteObject(go);
			}
		}

		GameObject* event = new GameObject;
		event->box.SetPosition(*new Vec2(570,10));

		string text = ReadAllFromFile("text/placeholder.txt");
		Text* eventText = CreateAddText(event, PETROV, 20, text, 650, 600, color.white, 0);

		Component* textScroller = new ScrollerText(*event, eventText, "texto evento pt3");
		event->AddComponent(textScroller);

		AddObject(event);
	}
}

void ExploreState::LoadButton(string type) {
	Colors color = Colors::GetInstance();

	GameObject* button = new GameObject;

	if (type == "name") {
		CreateAddButton(button, "main menu", 505, 121, *new Vec2(1000, 800), type);
		CreateAddText(button, NK57, 40, "Diga seu nome", -1, -1, color.white, 0);
	}

	if (type == "take keys") {
		// deleta botao antigo
		Component* cpt = nullptr;
		for (int i = 0; i < button_list.size(); i++) {
			cpt = button_list[i]->GetComponent("Button");
			if (cpt != nullptr && ((Button*)cpt)->GetID() == "name") {
				button_list.erase(button_list.begin() + i);
			}
		}
		GameObject* go;
		cpt = nullptr;
		for (int i = 0; i < objectArray.size(); i++) {
			go = objectArray[i].get();
			cpt = go->GetComponent("Button");
			if (cpt != nullptr && ((Button*)cpt)->GetID() == "name") {
				DeleteObject(go);
			}
		}

		CreateAddButton(button, "main menu", 505, 121, *new Vec2(1000, 800), type);
		CreateAddText(button, NK57, 40, "Pegue as chaves", -1, -1, color.white, 0);
	}

	if (type == "combat") {
		// deleta botao antigo
		Component* cpt = nullptr;
		for (int i = 0; i < button_list.size(); i++) {
			cpt = button_list[i]->GetComponent("Button");
			if (cpt != nullptr && ((Button*)cpt)->GetID() == "take keys") {
				button_list.erase(button_list.begin() + i);
			}
		}
		GameObject* go;
		cpt = nullptr;
		for (int i = 0; i < objectArray.size(); i++) {
			go = objectArray[i].get();
			cpt = go->GetComponent("Button");
			if (cpt != nullptr && ((Button*)cpt)->GetID() == "take keys") {
				DeleteObject(go);
			}
		}

		CreateAddButton(button, "main menu", 505, 121, *new Vec2(1000, 800), type);
		CreateAddText(button, NK57, 40, "Ir para combate", -1, -1, color.white, 0);
	}

	AddObject(button);
	button_list.push_back(button);
}

void ExploreState::Update(float dt) {
	UpdateArray(dt);

	InputManager* input = &(InputManager::GetInstance());
	popRequested = input->QuitRequested();

	// implementa funcionalidade do botão
	Button* currentbutton;
	if (currentStage == 1) {
		for (int i = 0; i < button_list.size(); i++) {
			currentbutton = (Button*) button_list[i]->GetComponent("Button");
			if (currentbutton->GetID() == "name") break;
		}
	}
	if (currentStage == 2) {
		for (int i = 0; i < button_list.size(); i++) {
			currentbutton = (Button*) button_list[i]->GetComponent("Button");
			if (currentbutton->GetID() == "take keys") break;
		}
	}
	if (currentStage == 3) {
		for (int i = 0; i < button_list.size(); i++) {
			currentbutton = (Button*) button_list[i]->GetComponent("Button");
			if (currentbutton->GetID() == "combat") break;
		}
	}


	if (currentbutton->IsHovered() && input->MousePress(LEFT_MOUSE_BUTTON)) {
		if (currentStage == 3) {
			Game& game = game.GetInstance();
			State* state = (State*) new CombatState();
			game.Push(state);
		}

		if (currentStage == 2) {
			LoadText(3);
			LoadButton("combat");
			currentStage = 3;
		}

		if (currentStage == 1) {
			LoadText(2);
			LoadButton("take keys");
			currentStage = 2;
		}
	}
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
