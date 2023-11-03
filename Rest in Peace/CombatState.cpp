#include "CombatState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Text.h"
#include "Player.h"

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

void CombatState::LoadScreen() {
	// Carrega imagem do fundo da tela
	GameObject* screen = new GameObject;
	Component* bg = new Sprite(*screen, "img/screens/combatscreen.png", 1, 0);
	screen->AddComponent(bg);
	screen->box.MoveThis(*new Vec2(0,0));
	AddObject(screen);
}

void CombatState::LoadAmbient(string type) {
	// Carrega ilustração do fundo da tela
	GameObject* ambient = new GameObject;
	Component* bg = new Sprite(*ambient, "img/living_room_crop.png", 1, 0);
	ambient->AddComponent(bg);
	ambient->box.MoveThis(*new Vec2(0,0));
	AddObject(ambient);
}

void CombatState::LoadOpponent(string type) {
	// carrega sprite
	GameObject* opponent = new GameObject;
	Component* sprite = new Sprite(*opponent, "img/enemies/diabrete.png", 1, 0);
	opponent->AddComponent(sprite);
	opponent->box.SetCenterPosition(*new Vec2(ILLUST_CENTER_X,ILLUST_CENTER_Y));
	AddObject(opponent);

	// carrega texto
	SDL_Color white;
	white.r = 255;
	white.g = 255;
	white.b = 255;
	white.a = 255;

	GameObject* go_name = new GameObject();
	Text* name = new Text(*go_name,
						  "font/nk57-monospace-no-rg.otf", 30,
						  Text::TextStyle::BLENDED,
						  "Diabrete",
						  white, 0);
	go_name->AddComponent((Component*) name);
	go_name->box.SetCenterPosition(*new Vec2(ILLUST_CENTER_X,40));
	AddObject(go_name);

	GameObject* go_hpdata = new GameObject();
	Text* hpdata = new Text(*go_hpdata,
						  "font/nk57-monospace-no-rg.otf", 30,
						  Text::TextStyle::BLENDED,
						  "HP 20/20",
						  white, 0);
	go_hpdata->AddComponent((Component*) hpdata);
	go_hpdata->box.SetCenterPosition(*new Vec2(ILLUST_CENTER_X,80));
	AddObject(go_hpdata);
}

void CombatState::LoadPlayerProfile() {
	// carrega avatar
	GameObject* avatar = new GameObject;
	Component* mugshot = new Sprite(*avatar, "img/MC/avatar.png", 1, 0);
	avatar->AddComponent(mugshot);
	avatar->box.MoveThis(*new Vec2(AVATAR_POS_X,AVATAR_POS_Y));
	AddObject(avatar);

	// carrega texto
	SDL_Color white;
	white.r = 255;
	white.g = 255;
	white.b = 255;
	white.a = 255;

	Player* player = Player::GetInstance();

	string hp = "HP: " + to_string(player->GetHP()) + "/" + to_string(PLAYER_MAX_HP);
	GameObject* go_hpdata = new GameObject();
	Text* hpdata = new Text(*go_hpdata,
						  "font/nk57-monospace-no-rg.otf", 30,
						  Text::TextStyle::BLENDED,
						  hp,
						  white, 0);
	go_hpdata->AddComponent((Component*) hpdata);
	go_hpdata->box.SetPosition(*new Vec2(1400,20));
	playerData.push_back(go_hpdata);

	string ap = "AP: " + to_string(player->GetAP()) + "/" + to_string(PLAYER_MAX_AP);
	GameObject* go_apdata = new GameObject();
	Text* apdata = new Text(*go_apdata,
						  "font/nk57-monospace-no-rg.otf", 30,
						  Text::TextStyle::BLENDED,
						  ap,
						  white, 0);
	go_apdata->AddComponent((Component*) apdata);
	go_apdata->box.SetPosition(*new Vec2(1400,60));
	playerData.push_back(go_apdata);

	string sp = "SP: " + to_string(player->GetSP()) + "/" + to_string(PLAYER_MAX_SP);
	GameObject* go_spdata = new GameObject();
	Text* spdata = new Text(*go_spdata,
						  "font/nk57-monospace-no-rg.otf", 30,
						  Text::TextStyle::BLENDED,
						  sp,
						  white, 0);
	go_spdata->AddComponent((Component*) spdata);
	go_spdata->box.SetPosition(*new Vec2(1400,100));
	playerData.push_back(go_spdata);
}

void CombatState::LoadCombatAssets() {
	Player::GetInstance()->DrawHand(PLAYER_HAND_SIZE);
}

void CombatState::UpdatePlayerData() {
	SDL_Color white;
	white.r = 255;
	white.g = 255;
	white.b = 255;
	white.a = 255;
	playerData.clear();
	Player* player = Player::GetInstance();

	string hp = "HP: " + to_string(player->GetHP()) + "/" + to_string(PLAYER_MAX_HP);
	GameObject* go_hpdata = new GameObject();
	Text* hpdata = new Text(*go_hpdata,
						  "font/nk57-monospace-no-rg.otf", 30,
						  Text::TextStyle::BLENDED,
						  hp,
						  white, 0);
	go_hpdata->AddComponent((Component*) hpdata);
	go_hpdata->box.SetPosition(*new Vec2(1400,20));
	playerData.push_back(go_hpdata);

	string ap = "AP: " + to_string(player->GetAP()) + "/" + to_string(PLAYER_MAX_AP);
	GameObject* go_apdata = new GameObject();
	Text* apdata = new Text(*go_apdata,
						  "font/nk57-monospace-no-rg.otf", 30,
						  Text::TextStyle::BLENDED,
						  ap,
						  white, 0);
	go_apdata->AddComponent((Component*) apdata);
	go_apdata->box.SetPosition(*new Vec2(1400,60));
	playerData.push_back(go_apdata);

	string sp = "SP: " + to_string(player->GetSP()) + "/" + to_string(PLAYER_MAX_SP);
	GameObject* go_spdata = new GameObject();
	Text* spdata = new Text(*go_spdata,
						  "font/nk57-monospace-no-rg.otf", 30,
						  Text::TextStyle::BLENDED,
						  sp,
						  white, 0);
	go_spdata->AddComponent((Component*) spdata);
	go_spdata->box.SetPosition(*new Vec2(1400,100));
	playerData.push_back(go_spdata);
}

void CombatState::Update(float dt) {
	UpdateArray(dt);

	InputManager* input = &(InputManager::GetInstance());
	popRequested = input->QuitRequested();

	Player* player = Player::GetInstance();
	if (input->KeyPress(SPACE_KEY)) {
		player->TakeDamage(1);
		player->SpendAP(1);
		player->LoseSP(1);
	}

	if (input->KeyPress(P_KEY)) {
		player->Heal(1);
		player->ResetAP();
		player->GainSP(1);
	}

	UpdatePlayerData();
}

void CombatState::Render() {
	this->RenderArray();
	this->RenderPlayerData();
	Player::GetInstance()->RenderHand();
}

void CombatState::RenderPlayerData() {
	for (int i = 0; i < playerData.size(); i++) {
		playerData[i]->Render();
	}
}

void CombatState::Start() {
	LoadAssets();
}

void CombatState::Pause() {

}

void CombatState::Resume() {

}

weak_ptr<GameObject> CombatState::GetPlayerGO() {

}
