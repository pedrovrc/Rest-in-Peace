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
	event = new Event(type, this);
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

	// carrega dados do evento
	event->LoadAssets();
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

void ExploreState::LoadCombatState() {
	Game& game = game.GetInstance();
	State* state = (State*) new CombatState();
	game.Push(state);
	popRequested = true;
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

void ExploreState::AddButton(GameObject* button) {
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

	event->Update(dt);
}

Button* ExploreState::GetButton(string id) {
	Button* button;

	for (int i = 0; i < button_list.size(); i++) {
		button = (Button*) button_list[i]->GetComponent("Button");
		if (button->GetID() == id) return button;;
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
