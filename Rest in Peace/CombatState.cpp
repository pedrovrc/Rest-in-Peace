#include "CombatState.h"
#include "Sprite.h"

CombatState::CombatState() {
	quitRequested = false;
	started = false;
}

CombatState::~CombatState() {
	while (objectArray.empty() == false) {
		objectArray.erase(objectArray.end() - 1);
	}
	objectArray.clear();
}

void CombatState::LoadAssets() {
	// Carrega imagem do fundo da tela
	GameObject* ambient = new GameObject;
	Component* bg = new Sprite(*ambient, "img/combatScreen.jpg", 1, 0);
	ambient->AddComponent(bg);
	ambient->box.MoveThis(*new Vec2(0,0));
	AddObject(ambient);

	// carrega imagem do fundo da tela
	LoadScreen();
	// carrega ilustracao de ambiente
	LoadAmbient("Placeholder");
	// carrega ilustracao e dados do painel do 	oponente
	LoadOpponent("Placeholder");
	// carrega ilustrações e dados do painel do player
	LoadPlayerProfile();
	// carrega ilustrações e dados do painel de combate
	LoadCombatAssets();

	// abre musica
	combatMusic.Open("audio/stageState.ogg");
}

void CombatState::Update(float dt) {

}

void CombatState::Render() {

}

void CombatState::Start() {

}

void CombatState::Pause() {

}

void CombatState::Resume() {

}

weak_ptr<GameObject> CombatState::GetPlayerGO() {

}
