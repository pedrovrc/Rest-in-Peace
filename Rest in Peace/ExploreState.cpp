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

	// carrega texto do local
	LoadText();

	// carrega botões de opções dada a situação
	// ATUALMENTE : carrega botão que leva para tela de combate
	LoadButton("combat");
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
	CreateAddSprite(screen, "img/screens/dialoguescreen.png", 1, 0, *new Vec2(0,0));
	AddObject(screen);
}

void ExploreState::LoadAmbient(string type) {
	// Carrega ilustração do fundo da tela
	GameObject* ambient = new GameObject;
	string filename;
	if (type == "Placeholder") {
		filename = "img/living_room_crop.png";
	}
	CreateAddSprite(ambient, filename, 1, 0, *new Vec2(0,0));
	AddObject(ambient);
}

void ExploreState::LoadText() {
	Colors color = Colors::GetInstance();

	GameObject* event = new GameObject;
	event->box.SetPosition(*new Vec2(570,10));

	string text = ReadAllFromFile("text/salao_entrada.txt");
	Text* eventText = CreateAddText(event, "PetrovSans-Regular.ttf", 20, text, 650, 600, color.white, 0);

	Component* textScroller = new ScrollerText(*event, eventText, "texto evento pt1");
	event->AddComponent(textScroller);

	AddObject(event);
}

void ExploreState::LoadButton(string type) {
	Colors color = Colors::GetInstance();

	GameObject* combat = new GameObject;

	CreateAddButton(combat, "main menu", 505, 121, *new Vec2(1000, 800), "combat");
	CreateAddText(combat, "nk57-monospace-no-rg.otf", 40, "Ir para combate", -1, -1, color.white, 0);

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
}

void ExploreState::Render() {
	this->RenderArray();
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
