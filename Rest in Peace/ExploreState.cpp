#include "ExploreState.h"
#include "Sprite.h"
#include "Button.h"
#include "Text.h"
#include "InputManager.h"
#include "Game.h"
#include "CombatState.h"

ExploreState::ExploreState(string type) {
	quitRequested = false;
	started = false;
	if (type == "intro") intro = true;
	else intro = false;
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

	// carrega texto de cutscene inicial
	if (intro) LoadIntroText();

	// carrega botão que leva para tela de combate
	LoadButton("combat");
}

void ExploreState::LoadScreen() {
	// Carrega imagem do fundo da tela
	GameObject* screen = new GameObject;
	Component* bg = new Sprite(*screen, "img/screens/dialoguescreen.png", 1, 0);
	screen->AddComponent(bg);
	screen->box.MoveThis(*new Vec2(0,0));
	AddObject(screen);
}

void ExploreState::LoadAmbient(string type) {
	// Carrega ilustração do fundo da tela
	GameObject* ambient = new GameObject;
	Component* bg;

	if (type == "Placeholder") {
		bg = new Sprite(*ambient, "img/living_room_crop.png", 1, 0);
	}

	ambient->AddComponent(bg);
	ambient->box.MoveThis(*new Vec2(0,0));
	AddObject(ambient);
}

void ExploreState::LoadIntroText() {
	Colors color = Colors::GetInstance();

	GameObject* intro = new GameObject;
	intro->box.SetPosition(*new Vec2(570,10));
	string text = ReadAllFromFile("text/intro.txt");
	Component* introText = new Text(*intro,
									"font/PetrovSans-Regular.ttf", 20,
									Text::TextStyle::BLENDED,
									text,
									color.white, 0);
	intro->AddComponent(introText);
	intro->box.w = 650;
	intro->box.h = 600;
	((Text*)introText)->SetScope(0, 0, intro->box.w, intro->box.h);
	AddObject(intro);
}

string ExploreState::ReadAllFromFile(string path) {
	ifstream file(path);
	string text;

	if (file) {	// checa arquivo não nulo
		ostringstream stream;
		stream << file.rdbuf();
		text = stream.str();
	}

	return text;
}

void ExploreState::LoadButton(string type) {
	Colors color = Colors::GetInstance();

	GameObject* combat = new GameObject;

	Component* combatbutton = new Button(*combat, "main menu");
	combat->box.SetDimensions(505, 121);
	combat->box.SetCenterPosition(*new Vec2(920, 800));
	combat->AddComponent(combatbutton);

	Component* buttontext = new Text(*combat,
									"font/nk57-monospace-no-rg.otf", 40,
									Text::TextStyle::BLENDED,
									"Ir para combate",
									color.white, 0);
	combat->AddComponent(buttontext);
	combat->box.w = ((Text*)buttontext)->GetSurfaceWidth();
	combat->box.h = ((Text*)buttontext)->GetSurfaceHeight();
	((Text*)buttontext)->SetScope(0, 0, combat->box.w, combat->box.h);

	AddObject(combat);
	button_list.push_back(combat);
}

void ExploreState::Update(float dt) {
	UpdateArray(dt);

	InputManager* input = &(InputManager::GetInstance());
	popRequested = input->QuitRequested();

	// implementa funcionalidade do botão de combate
	Button* combatbutton = (Button*) button_list[0]->GetComponent("Button");

	if (combatbutton->IsHovered() && input->MousePress(LEFT_MOUSE_BUTTON)) {
		Game& game = game.GetInstance();
		State* state = (State*) new CombatState();
		game.Push(state);
	}

	// scroll do texto
	GameObject* go;
	if (intro && (input->WheelRoll("down") || input->WheelRoll("up")
			  || input->KeyPress(UP_ARROW_KEY) || input->KeyPress(DOWN_ARROW_KEY))) {	// detecta scroll ou seta
		for (int i = 0; i < objectArray.size(); i++) {
			go = objectArray[i].get();
			if (go->GetComponent("Text") != nullptr && go->GetComponent("Button") == nullptr) {	// encontra texto não botão
				Text* text = (Text*)go->GetComponent("Text");

				int y_offset = 0;
				if (input->WheelRoll("down") || input->KeyPress(DOWN_ARROW_KEY)) y_offset = 50;
				if (input->WheelRoll("up") || input->KeyPress(UP_ARROW_KEY)) y_offset = -50;

				text->RollScope(y_offset);
			}
		}
	}
}

void ExploreState::Render() {
	this->RenderArray();
}

void ExploreState::Start() {
	LoadAssets();
}

void ExploreState::Pause() {

}

void ExploreState::Resume() {

}
