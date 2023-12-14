#include "IntroState.h"
#include "Sprite.h"
#include "Colors.h"
#include "Text.h"
#include "Button.h"
#include "InputManager.h"
#include "ScrollerText.h"
#include "GeneralFunctions.h"
#include "Player.h"

using namespace std;

IntroState::IntroState() {
	quitRequested = false;
	popRequested = false;
	started = false;
	currentStage = 0;
	animate = false;
	profileCover = nullptr;
}

IntroState::~IntroState() {
	while (objectArray.empty() == false) {
		objectArray.erase(objectArray.end() - 1);
	}
	objectArray.clear();
}

void IntroState::LoadAssets() {
	// carrega imagem do fundo da tela
	LoadScreen();

	// carrega ilustracao de ambiente
	LoadAmbient("mansion");

	// carrega ilustrações e dados do painel do player
	LoadPlayerProfile();

	// carrega cobertura para painel do player
	LoadProfileCover();

	// carrega texto inicial de cutscene
	LoadIntroText(1);

	// carrega botão que avança cutscene
	LoadButton("continue");

	currentStage = 1;
}

void IntroState::LoadScreen() {
	// Carrega imagem do fundo da tela
	GameObject* screen = new GameObject;
	CreateAddSprite(screen, "img/screens/dialoguescreen.png", 1, 0, *new Vec2(0,0), -1, -1);
	AddObject(screen);
}

void IntroState::LoadAmbient(string type) {
	// Carrega ilustração do fundo da tela
	GameObject* ambient = new GameObject;
	string filename;
	if (type == "mansion") {
		filename = "img/forest mansion sketch.png";
	}
	CreateAddSprite(ambient, filename, 1, 0, *new Vec2(0,0), -1, -1);
	AddObject(ambient);

	introMusic.Open("audio/dark forest ambience.mp3");
}

void IntroState::LoadIntroText(int part) {
	Colors color = Colors::GetInstance();

	if (part == 1) {
		// cria texto
		GameObject* intro = new GameObject;
		intro->box.SetPosition(*new Vec2(570,10));
		intro->box.SetDimensions(650, 600);

		string text = ReadAllFromFile("text/intro1.txt");
		Text* introText = CreateAddText(intro, PETROV, REGULAR_SIZE, text, 650, 600, color.white, 0);

		Component* textScroller = new ScrollerText(*intro, introText, "texto intro pt1");
		intro->AddComponent(textScroller);

		AddObject(intro);
	}

	if (part == 2) {
		// deleta texto antigo
		DeleteText("texto intro pt1");

		// cria novo texto
		GameObject* intro = new GameObject;
		intro->box.SetPosition(*new Vec2(570,10));
		intro->box.SetDimensions(650, 600);

		string text = ReadAllFromFile("text/intro2.txt");
		Text* introText = CreateAddText(intro, PETROV, REGULAR_SIZE, text, 650, 600, color.white, 0);

		Component* textScroller = new ScrollerText(*intro, introText, "texto intro pt2");
		intro->AddComponent(textScroller);

		AddObject(intro);
	}
}

void IntroState::DeleteText(string id) {
	Component* cpt = nullptr;
	GameObject* go;
	for (int i = 0; i < (int)objectArray.size(); i++) {
		go = objectArray[i].get();
		cpt = go->GetComponent("ScrollerText");
		if (cpt != nullptr && ((ScrollerText*)cpt)->GetID() == id) {
			DeleteObject(go);
		}
	}
}

void IntroState::LoadPlayerProfile() {
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

void IntroState::LoadProfileCover() {
	profileCover = new GameObject;
	CreateAddSprite(profileCover, "img/screens/screencover.png", 1, 0, *new Vec2(1243, 0), -1, -1);
	//AddObject(profileCover);
}

void IntroState::LoadButton(string type) {
	Colors color = Colors::GetInstance();
	Vec2 position;
	position.Set(1080, 800);

	GameObject* button = new GameObject;

	if (type == "continue") {
		// cria novo botao
		CreateAddButton(button, "main menu", 505, 121, position, "continue");
		CreateAddText(button, NK57, 40, "Entrar", -1, -1, color.white, 0);
	}

	if (type == "end" ) {
		// deleta botao antigo
		DeleteButton("continue");

		// cria novo botao
		CreateAddButton(button, "main menu", 505, 121, position, "end");
		CreateAddText(button, NK57, 40, "Explorar", -1, -1, color.white, 0);
	}

	button->box.SetCenterPosition(*new Vec2(900, 760));

	AddObject(button);
	button_list.push_back(button);
}

void IntroState::DeleteButton(string id) {
	Component* cpt = nullptr;
	for (int i = 0; i < (int)button_list.size(); i++) {
		cpt = button_list[i]->GetComponent("Button");
		if (cpt != nullptr && ((Button*)cpt)->GetID() == id) {
			button_list.erase(button_list.begin() + i);
		}
	}
	GameObject* go;
	cpt = nullptr;
	for (int i = 0; i < (int)objectArray.size(); i++) {
		go = objectArray[i].get();
		cpt = go->GetComponent("Button");
		if (cpt != nullptr && ((Button*)cpt)->GetID() == id) {
			DeleteObject(go);
		}
	}
}


void IntroState::Update(float dt) {
	UpdateArray(dt);

	InputManager* input = &(InputManager::GetInstance());
	popRequested = input->QuitRequested();

	// seleciona botão de acordo com estágio botões
	Button* currentbutton;
	if (currentStage == 1) {
		for (int i = 0; i < (int)button_list.size(); i++) {
			currentbutton = (Button*) button_list[i]->GetComponent("Button");
			if (currentbutton->GetID() == "continue") break;
		}
	}
	if (currentStage == 2) {
		for (int i = 0; i < (int)button_list.size(); i++) {
			currentbutton = (Button*) button_list[i]->GetComponent("Button");
			if (currentbutton->GetID() == "end") break;
		}
	}

	// estágio final - animando painel lateral
	if (currentStage == 3 && profileCover->box.x > 1600) {
		popRequested = true;
	}

	if (currentStage != 3 && currentbutton->IsHovered() && input->MousePress(LEFT_MOUSE_BUTTON)) {
		// implementa funcionalidade do botao da parte 2
		if (currentStage == 2) {
			currentStage = 3;
			animate = true;
		}

		// implementa funcionalidade do botao da parte 1
		if (currentStage == 1) {
			LoadIntroText(2);
			LoadButton("end");
			currentStage = 2;
		}
	}
}

void IntroState::Render() {
	this->RenderArray();
	this->RenderPlayerData();
	if (animate) profileCover->box.MoveThis(*new Vec2(10, 0));
	profileCover->Render();
}

void IntroState::RenderPlayerData() {
	for (int i = 0; i < (int)playerData.size(); i++) {
		playerData[i]->Render();
	}
}

void IntroState::Start() {
	LoadAssets();
	introMusic.Play();
}

void IntroState::Pause() {
	introMusic.Stop();
}

void IntroState::Resume() {
	introMusic.Play();
}

