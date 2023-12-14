#include "EndState.h"
#include "Game.h"
#include "Sprite.h"
#include "Music.h"
#include "Text.h"
#include "GameData.h"
#include "GeneralFunctions.h"
#include "ScrollerText.h"

EndState::EndState(string opponent, string ambient) {
	quitRequested = false;
	this->opponent = opponent;
	this->ambient = ambient;
	flagInitialScreen = true;
	flagChoice = false;
	end = false;
	timeText = new GameObject;
}

EndState::~EndState() {
	while (objectArray.empty() == false) {
		objectArray.erase(objectArray.end() - 1);
	}
	objectArray.clear();
}

void EndState::LoadAssets() {
	LoadAmbient(ambient);

	LoadTextAndMusic();

	LoadOpponent(opponent);
}

void EndState::LoadAmbient(string type) {
	GameObject* go_bg = new GameObject();
	string filename;

	if (flagInitialScreen) {
		if (type == "living room") {
			filename = "img/old_haunted_house_sketch_full_blur.png";
		}
		CreateAddSprite(go_bg, filename, 1, 0, *new Vec2(0,0), WINDOW_WIDTH, WINDOW_HEIGHT);
	}

	if (flagChoice) {
		if (type == "living room") {
			filename = "img/old_haunted_house_sketch.png";
		}
		CreateAddSprite(go_bg, filename, 1, 0, *new Vec2(0,0), 550, 900);
	}
	AddObject(go_bg);
}

void EndState::LoadTextAndMusic() {
	Game& game = game.GetInstance();
	Colors color = Colors::GetInstance();

	GameObject* textQuit = new GameObject;
	if (GameData::playerVictory) {
		// vitoria
		// carrega bg
		CreateAddText(textQuit, NK57, 90, "VITÓRIA!", -1, -1, color.black, 0);

		// carrega musica
		backgroundMusic.Open("audio/winMusic.mp3");
	} else {
		// derrota
		// carrega bg
		CreateAddText(textQuit, NK57, 90, "DERROTA!", -1, -1, color.black, 0);

		// carrega musica
		backgroundMusic.Open("audio/loseMusic.mp3");
	}
	textQuit->box.SetCenterPosition(*new Vec2(800,450));
	AddObject(textQuit);

	GameObject* textPrompt = new GameObject;
	if (game.gameData.playerVictory) {
		CreateAddText(textPrompt, NK57, 50, "Pressione espaço para continuar", -1, -1, color.black, 0);
	} else {
		CreateAddText(textPrompt, NK57, 50, "Pressione espaço para recomeçar", -1, -1, color.black, 0);
	}
	textPrompt->box.SetCenterPosition(*new Vec2(800,800));
	AddObject(textPrompt);
}

void EndState::LoadOpponent(string type) {
	Game& game = game.GetInstance();
	Colors& color = color.GetInstance();

	if (flagInitialScreen) {
		GameObject* text = new GameObject;
		if (type == "diabrete") {
			// carrega texto do diabrete
			if (game.gameData.playerVictory) {
				CreateAddText(text, NK57, 30, "Você derrotou o diabrete!", -1, -1, color.white, 0);
			} else {
				CreateAddText(text, NK57, 30, "Você não resistiu aos truques do diabrete.", -1, -1, color.white, 0);
			}
		}
		text->box.SetCenterPosition(*new Vec2(800, 600));
		AddObject(text);
	}

	if (flagChoice) {
		GameObject* opponent = new GameObject;
		GameObject* name = new GameObject;
		if (type == "diabrete") {
			CreateAddCenteredSprite(opponent, "img/enemies/diabrete.png", 1, 0, *new Vec2(275, 450), -1, -1);
			CreateAddText(name, NK57, 30, "Diabrete", -1, -1, color.white, 0);
			name->box.SetCenterPosition(*new Vec2(275,40));
		}
		AddObject(opponent);
		AddObject(name);
	}
}

void EndState::Update(float dt) {
	Game& game = game.GetInstance();
	InputManager* input = &(InputManager::GetInstance());
	UpdateArray(dt);

	if (end) {
		Button* button = GetButton("continue");
		if (button->IsHovered() && input->MousePress(LEFT_MOUSE_BUTTON)) {
			popRequested = true;
		}
	}

	if (flagChoice) {
		Button* option1 = GetButton("deal");
		Button* option2 = GetButton("exorcism");

		if (option1->IsHovered() && input->MousePress(LEFT_MOUSE_BUTTON)) {
			// pacto
			DeleteText("vitoria diabrete");
			DeleteButton("deal");
			DeleteButton("exorcism");
			LoadButton("continue", "centered");
			LoadText("pacto diabrete");
			end = true;
			flagChoice = false;
			Game& game = game.GetInstance();
			game.gameData.timePassed++;
			UpdateTime();
		}

		if (option2->IsHovered() && input->MousePress(LEFT_MOUSE_BUTTON)) {
			// exorcismo
			DeleteText("vitoria diabrete");
			DeleteButton("deal");
			DeleteButton("exorcism");
			LoadButton("continue", "centered");
			LoadText("exorcizar diabrete");
			end = true;
			flagChoice = false;
			Game& game = game.GetInstance();
			game.gameData.timePassed++;
			UpdateTime();
		}
	}

	// checa por espaço
	if (flagInitialScreen && input->KeyPress(SPACE_KEY)) {
		if (game.gameData.playerVictory) {
			// continuar -> cena de pacto
			flagChoice = true;
			flagInitialScreen = false;

			EraseAllObjects();
			LoadScreen();
			LoadAmbient(ambient);
			LoadOpponent(opponent);
			LoadText("vitoria diabrete");
			LoadButton("deal", "1 of 2");
			LoadButton("exorcism", "2 of 2");
			backgroundMusic.Open("audio/moonlight sonata reversed.mp3");
			backgroundMusic.Play();
			LoadPlayerProfile();
			UpdateTime();
			AddObject(timeText);
		} else {
			// recomeçar -> reiniciar jogo
			popRequested = true;
		}
	}

	// checa por quit
	if (input->QuitRequested() || input->KeyPress(ESCAPE_KEY)) {
		quitRequested = true;
	}
}

void EndState::UpdateTime() {
	Component* cpt = timeText->GetComponent("Text");
	if (cpt != nullptr) timeText->RemoveComponent(cpt);

	Game& game = game.GetInstance();
	Colors color = Colors::GetInstance();
	string hour = GetTimeFromTable(game.gameData.timePassed);
	CreateAddText(timeText, NK57, 40, hour, -1, -1, color.white, 0);
	timeText->box.SetCenterPosition(*new Vec2(1420, 850));
}

void EndState::LoadPlayerProfile() {
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
	AddObject(hpbar);

	// string na barra
	string hp = "Vida: " + to_string(player->GetHP()) + "/" + to_string(PLAYER_MAX_HP);
	GameObject* go_hpdata = new GameObject();
	CreateAddText(go_hpdata, NK57, 15, hp, -1, -1, color.white, 0);
	go_hpdata->box.SetCenterPosition(redbar->box.GetCenter());
	AddObject(go_hpdata);

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
	AddObject(spbar);

	// string na barra
	string sp = "Sanidade: " + to_string(player->GetSP()) + "/" + to_string(PLAYER_MAX_SP);
	GameObject* go_spdata = new GameObject();
	CreateAddText(go_spdata, NK57, 15, sp, -1, -1, color.black, 0);
	go_spdata->box.SetCenterPosition(graybar->box.GetCenter());
	AddObject(go_spdata);
}

void EndState::LoadText(string id) {
	Colors color = Colors::GetInstance();

	GameObject* newText = new GameObject;
	newText->box.SetPosition(*new Vec2(570,10));
	newText->box.SetDimensions(650, 600);

	string text;

	if (id == "vitoria diabrete") {
		text = ReadAllFromFile("text/vitoriadiabrete.txt");
	}

	if (id == "exorcizar diabrete") {
		text = ReadAllFromFile("text/exorcizadiabrete.txt");
	}

	if (id == "pacto diabrete") {
		text = ReadAllFromFile("text/pactodiabrete.txt");
	}

	Text* eventText = CreateAddText(newText, PETROV, REGULAR_SIZE, text, 650, 600, color.white, 0);

	Component* textScroller = new ScrollerText(*newText, eventText, id);
	newText->AddComponent(textScroller);

	AddObject(newText);
}

void EndState::LoadButton(string id, string position) {
	Colors color = Colors::GetInstance();

	GameObject* button = new GameObject;
	CreateAddButton(button, "main menu", 505, 121, *new Vec2(0, 0), id);

	if (id == "deal") {
		CreateAddText(button, NK57, 40, "Criar pacto", -1, -1, color.white, 0);
	}

	if (id == "exorcism") {
		CreateAddText(button, NK57, 40, "Exorcizar", -1, -1, color.white, 0);
	}

	if (id == "continue") {
		CreateAddText(button, NK57, 40, "Continuar", -1, -1, color.white, 0);
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

Button* EndState::GetButton(string id) {
	Button* button;

	for (int i = 0; i < (int)button_list.size(); i++) {
		button = (Button*) button_list[i]->GetComponent("Button");
		if (button->GetID() == id) return button;;
	}
	return nullptr;
}

void EndState::LoadScreen() {
	// Carrega imagem do fundo da tela
	GameObject* screen = new GameObject;
	CreateAddSprite(screen, "img/screens/dialoguescreen.png", 1, 0, *new Vec2(0,0), -1, -1);
	AddObject(screen);
}

void EndState::EraseAllObjects() {
	while (objectArray.empty() == false) {
		objectArray.erase(objectArray.end() - 1);
	}
	objectArray.clear();
}

void EndState::DeleteButton(string id) {
	if (id == "") return;

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

void EndState::DeleteText(string id) {
	if (id == "") return;

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

void EndState::Render() {
	RenderArray();
}

void EndState::Start() {
	LoadAssets();
	backgroundMusic.Play();
	StartArray();
	started = true;
}

void EndState::Pause() {

}

void EndState::Resume() {

}
