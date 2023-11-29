#include "IntroState.h"
#include "Sprite.h"
#include "Colors.h"
#include "Text.h"
#include "Button.h"
#include "InputManager.h"
#include "ScrollerText.h"
#include "GeneralFunctions.h"

using namespace std;

IntroState::IntroState() {
	quitRequested = false;
	popRequested = false;
	started = false;
	currentStage = 0;
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
	LoadAmbient("Placeholder");

	// carrega texto inicial de cutscene
	LoadIntroText(1);

	// carrega botão que avança cutscene
	LoadButton("continue");

	currentStage = 1;
}

void IntroState::LoadScreen() {
	// Carrega imagem do fundo da tela
	GameObject* screen = new GameObject;
	CreateAddSprite(screen, "img/screens/dialoguescreen.png", 1, 0, *new Vec2(0,0));
	AddObject(screen);
}

void IntroState::LoadAmbient(string type) {
	// Carrega ilustração do fundo da tela
	GameObject* ambient = new GameObject;
	string filename;
	if (type == "Placeholder") {
		filename = "img/living_room_crop.png";
	}
	CreateAddSprite(ambient, filename, 1, 0, *new Vec2(0,0));
	AddObject(ambient);
}

void IntroState::LoadIntroText(int part) {
	Colors color = Colors::GetInstance();

	if (part == 1) {
		// cria texto
		GameObject* intro = new GameObject;
		intro->box.SetPosition(*new Vec2(570,10));

		string text = ReadAllFromFile("text/intro1.txt");
		Text* introText = CreateAddText(intro, "PetrovSans-Regular.ttf", 20, text, 650, 600, color.white, 0);

		Component* textScroller = new ScrollerText(*intro, introText, "texto intro pt1");
		intro->AddComponent(textScroller);

		AddObject(intro);
	}

	if (part == 2) {
		// deleta texto antigo
		Component* cpt = nullptr;
		GameObject* go;
		for (int i = 0; i < objectArray.size(); i++) {
			go = objectArray[i].get();
			cpt = go->GetComponent("ScrollerText");
			if (cpt != nullptr && ((ScrollerText*)cpt)->GetID() == "texto intro pt1") {
				DeleteObject(go);
			}
		}

		// cria novo texto
		GameObject* intro = new GameObject;
		intro->box.SetPosition(*new Vec2(570,10));

		string text = ReadAllFromFile("text/intro2.txt");
		Text* introText = CreateAddText(intro, "PetrovSans-Regular.ttf", 20, text, 650, 600, color.white, 0);

		Component* textScroller = new ScrollerText(*intro, introText, "texto intro pt2");
		intro->AddComponent(textScroller);

		AddObject(intro);
	}
}

void IntroState::LoadButton(string type) {
	Colors color = Colors::GetInstance();
	Vec2 position;
	position.Set(1080, 800);

	if (type == "continue") {
		GameObject* contin = new GameObject;
		CreateAddButton(contin, "main menu", 505, 121, position, "continue");
		CreateAddText(contin, "nk57-monospace-no-rg.otf", 40, "Entrar", -1, -1, color.white, 0);

		AddObject(contin);
		button_list.push_back(contin);
	}

	if (type == "end" ) {
		// deleta botao antigo
		Component* cpt = nullptr;
		for (int i = 0; i < button_list.size(); i++) {
			cpt = button_list[i]->GetComponent("Button");
			if (cpt != nullptr && ((Button*)cpt)->GetID() == "continue") {
				button_list.erase(button_list.begin() + i);
			}
		}
		GameObject* go;
		cpt = nullptr;
		for (int i = 0; i < objectArray.size(); i++) {
			go = objectArray[i].get();
			cpt = go->GetComponent("Button");
			if (cpt != nullptr && ((Button*)cpt)->GetID() == "continue") {
				DeleteObject(go);
			}
		}

		// cria novo botao
		GameObject* explore = new GameObject;

		CreateAddButton(explore, "main menu", 505, 121, position, "end");
		CreateAddText(explore, "nk57-monospace-no-rg.otf", 40, "Explorar", -1, -1, color.white, 0);

		AddObject(explore);
		button_list.push_back(explore);
	}
}


void IntroState::Update(float dt) {
	UpdateArray(dt);

	InputManager* input = &(InputManager::GetInstance());

	// implementa funcionalidade dos botões
	Button* currentbutton;
	if (currentStage == 1) {
		for (int i = 0; i < button_list.size(); i++) {
			currentbutton = (Button*) button_list[i]->GetComponent("Button");
			if (currentbutton->GetID() == "continue") break;
		}
	}
	if (currentStage == 2) {
		for (int i = 0; i < button_list.size(); i++) {
			currentbutton = (Button*) button_list[i]->GetComponent("Button");
			if (currentbutton->GetID() == "end") break;
		}
	}

	// implementa funcionalidade do botao da parte 1
	if (currentStage == 1 && currentbutton->IsHovered() && input->KeyPress(SPACE_KEY)) {
		LoadIntroText(2);
		LoadButton("end");
		currentStage = 2;
	}

	// implementa funcionalidade do botao da parte 2
	if (currentStage == 2 && currentbutton->IsHovered() && input->MousePress(LEFT_MOUSE_BUTTON)) {
		popRequested = true;
	}
}

void IntroState::Render() {
	this->RenderArray();
}

void IntroState::Start() {
	LoadAssets();
}

void IntroState::Pause() {

}

void IntroState::Resume() {

}

