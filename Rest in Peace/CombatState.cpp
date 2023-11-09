#include "CombatState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Text.h"
#include "Player.h"
#include "Colors.h"

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
	Colors& color = Colors::GetInstance();

	// carrega sprite do oponente
	GameObject* opponent = new GameObject;
	Component* sprite = new Sprite(*opponent, "img/enemies/diabrete.png", 1, 0);
	opponent->AddComponent(sprite);
	opponent->box.SetCenterPosition(*new Vec2(ILLUST_CENTER_X,ILLUST_CENTER_Y));
	AddObject(opponent);

	// carrega textos
	// carrega nome
	GameObject* go_name = new GameObject();
	Text* name = new Text(*go_name,
						  "font/nk57-monospace-no-rg.otf", 30,
						  Text::TextStyle::BLENDED,
						  "Diabrete",
						  color.white, 0);
	go_name->AddComponent((Component*) name);
	go_name->box.SetCenterPosition(*new Vec2(ILLUST_CENTER_X,40));
	AddObject(go_name);

	// carrega HP
	GameObject* go_hpdata = new GameObject();
	Text* hpdata = new Text(*go_hpdata,
						  "font/nk57-monospace-no-rg.otf", 30,
						  Text::TextStyle::BLENDED,
						  "HP 20/20",
						  color.white, 0);
	go_hpdata->AddComponent((Component*) hpdata);
	go_hpdata->box.SetCenterPosition(*new Vec2(ILLUST_CENTER_X,80));
	AddObject(go_hpdata);
}

void CombatState::LoadPlayerProfile() {
	Colors& color = Colors::GetInstance();

	// carrega avatar do player
	GameObject* avatar = new GameObject;
	Component* mugshot = new Sprite(*avatar, "img/MC/avatar v2.png", 1, 0);
	avatar->AddComponent(mugshot);
	avatar->box.MoveThis(*new Vec2(AVATAR_POS_X,AVATAR_POS_Y));
	AddObject(avatar);

	// carrega textos
	// carrega nome
	GameObject* name = new GameObject;
	Component* nametext = new Text(*name,
							  "font/nk57-monospace-no-rg.otf", 40,
							  Text::TextStyle::BLENDED,
							  "Sofia",
							  color.white, 0);
	name->AddComponent(nametext);
	name->box.SetCenterPosition(*new Vec2(1505, 40));
	AddObject(name);

	Player* player = Player::GetInstance();

	// Comeca com 5 armor para demonstração
	//player->GainArmor(5);

	// Carrega HUD HP -------------------
	// barra vermelha
	GameObject* redbar = new GameObject;
	Component* redbar_img = new Sprite(*redbar, "img/resources/red bar.png", 1, 0);
	redbar->AddComponent(redbar_img);
	redbar->box.SetDimensions(HUDBAR_W, HUDBAR_H);
	redbar->box.MoveThis(*new Vec2(HUD_POS_X, HUD_POS_Y));
	AddObject(redbar);

	// barra verde
	GameObject* hpbar = new GameObject;
	Component* hpbar_img = new Sprite(*hpbar, "img/resources/green bar.png", 1, 0);
	hpbar->AddComponent(hpbar_img);
	hpbar->box.SetDimensions(HUDBAR_W * ((float)player->GetHP()/PLAYER_MAX_HP), HUDBAR_H);
	hpbar->box.MoveThis(*new Vec2(HUD_POS_X, HUD_POS_Y));
	playerData.push_back(hpbar);

	// string na barra
	string hp = "Vida: " + to_string(player->GetHP()) + "/" + to_string(PLAYER_MAX_HP);
	GameObject* go_hpdata = new GameObject();
	Text* hpdata = new Text(*go_hpdata,
						  "font/nk57-monospace-no-rg.otf", 15,
						  Text::TextStyle::BLENDED,
						  hp,
						  color.white, 0);
	go_hpdata->AddComponent((Component*) hpdata);
	go_hpdata->box.SetCenterPosition(redbar->box.GetCenter());
	playerData.push_back(go_hpdata);

	// Carrega HUD SP -----------------------
	// barra cinza.
	GameObject* graybar = new GameObject;
	Component* graybar_img = new Sprite(*graybar, "img/resources/gray bar.png", 1, 0);
	graybar->AddComponent(graybar_img);
	graybar->box.SetDimensions(HUDBAR_W, HUDBAR_H);
	graybar->box.MoveThis(*new Vec2(HUD_POS_X, HUD_POS_Y + HUD_Y_OFFSET));
	AddObject(graybar);

	// barra branca
	GameObject* spbar = new GameObject;
	Component* spbar_img = new Sprite(*spbar, "img/resources/white bar.png", 1, 0);
	spbar->AddComponent(spbar_img);
	spbar->box.SetDimensions(HUDBAR_W * ((float)player->GetSP()/PLAYER_MAX_SP), HUDBAR_H);
	spbar->box.MoveThis(*new Vec2(HUD_POS_X, HUD_POS_Y + HUD_Y_OFFSET));
	playerData.push_back(spbar);

	// string na barra
	string sp = "Sanidade: " + to_string(player->GetSP()) + "/" + to_string(PLAYER_MAX_SP);
	GameObject* go_spdata = new GameObject();
	Text* spdata = new Text(*go_spdata,
						  "font/nk57-monospace-no-rg.otf", 20,
						  Text::TextStyle::BLENDED,
						  sp,
						  color.black, 0);
	go_spdata->AddComponent((Component*) spdata);
	go_spdata->box.SetCenterPosition(graybar->box.GetCenter());
	playerData.push_back(go_spdata);

	// Carrega HUD Actions ----------------------
	// barra cinza
	GameObject* graybar2 = new GameObject;
	Component* graybar_img2 = new Sprite(*graybar2, "img/resources/gray bar.png", 1, 0);
	graybar2->AddComponent(graybar_img2);
	graybar2->box.SetDimensions(HUDBAR_W, HUDBAR_H);
	graybar2->box.MoveThis(*new Vec2(HUD_POS_X, HUD_POS_Y + (2 * HUD_Y_OFFSET)));
	AddObject(graybar2);

	// barra amarela
	GameObject* apbar = new GameObject;
	Component* apbar_img = new Sprite(*apbar, "img/resources/yellow bar.png", 1, 0);
	apbar->AddComponent(apbar_img);
	apbar->box.SetDimensions(HUDBAR_W * ((float)player->GetAP()/PLAYER_MAX_AP), HUDBAR_H);
	apbar->box.MoveThis(*new Vec2(HUD_POS_X, HUD_POS_Y + (2 * HUD_Y_OFFSET)));
	playerData.push_back(spbar);

	// texto na barra
	string ap = "Acoes: " + to_string(player->GetAP()) + "/" + to_string(PLAYER_MAX_AP);
	GameObject* go_apdata = new GameObject();
	Text* apdata = new Text(*go_apdata,
						  "font/nk57-monospace-no-rg.otf", 20,
						  Text::TextStyle::BLENDED,
						  ap,
						  color.black, 0);
	go_apdata->AddComponent((Component*) apdata);
	go_apdata->box.SetCenterPosition(graybar2->box.GetCenter());
	playerData.push_back(go_apdata);
}

void CombatState::LoadCombatAssets() {
	Player::GetInstance()->DrawHand(PLAYER_HAND_SIZE);
}

void CombatState::UpdatePlayerData() {
	Colors& color = Colors::GetInstance();
	Player* player = Player::GetInstance();

	// Atualiza HUD HP ---------------------
	// refaz barra verde
	GameObject* hpbar = new GameObject;
	Component* hpbar_img = new Sprite(*hpbar, "img/resources/green bar.png", 1, 0);
	hpbar->AddComponent(hpbar_img);
	hpbar->box.SetDimensions(HUDBAR_W * ((float)player->GetHP()/PLAYER_MAX_HP), HUDBAR_H);
	hpbar->box.MoveThis(*new Vec2(HUD_POS_X, HUD_POS_Y));

	// refaz string de vida
	string hp = "Vida: " + to_string(player->GetHP()) + "/" + to_string(PLAYER_MAX_HP);
	GameObject* go_hpdata = new GameObject();
	Text* hpdata = new Text(*go_hpdata,
						  "font/nk57-monospace-no-rg.otf", 18,
						  Text::TextStyle::BLENDED,
						  hp,
						  color.white, 0);
	go_hpdata->AddComponent((Component*) hpdata);
	go_hpdata->box.SetCenterPosition(playerData[1]->box.GetCenter());

	// Atualiza HUD SP -------------------------------
	// refaz barra branca
	GameObject* spbar = new GameObject;
	Component* spbar_img = new Sprite(*spbar, "img/resources/white bar.png", 1, 0);
	spbar->AddComponent(spbar_img);
	spbar->box.SetDimensions(HUDBAR_W * ((float)player->GetSP()/PLAYER_MAX_SP), HUDBAR_H);
	spbar->box.MoveThis(*new Vec2(HUD_POS_X, HUD_POS_Y + HUD_Y_OFFSET));

	// refaz string de sanidade
	string sp = "Sanidade: " + to_string(player->GetSP()) + "/" + to_string(PLAYER_MAX_SP);
	GameObject* go_spdata = new GameObject();
	Text* spdata = new Text(*go_spdata,
						  "font/nk57-monospace-no-rg.otf", 15,
						  Text::TextStyle::BLENDED,
						  sp,
						  color.black, 0);
	go_spdata->AddComponent((Component*) spdata);
	go_spdata->box.SetCenterPosition(playerData[3]->box.GetCenter());

	// Atualiza HUD Actions ----------------------------
	// refaz barra amarela
	GameObject* apbar = new GameObject;
	Component* apbar_img = new Sprite(*apbar, "img/resources/yellow bar.png", 1, 0);
	apbar->AddComponent(apbar_img);
	apbar->box.SetDimensions(HUDBAR_W * ((float)player->GetAP()/PLAYER_MAX_AP), HUDBAR_H);
	apbar->box.MoveThis(*new Vec2(HUD_POS_X, HUD_POS_Y + (2 * HUD_Y_OFFSET)));

	// refaz string de acoes
	string ap = "Acoes: " + to_string(player->GetAP()) + "/" + to_string(PLAYER_MAX_AP);
	GameObject* go_apdata = new GameObject();
	Text* apdata = new Text(*go_apdata,
						  "font/nk57-monospace-no-rg.otf", 20,
						  Text::TextStyle::BLENDED,
						  ap,
						  color.black, 0);
	go_apdata->AddComponent((Component*) apdata);
	go_apdata->box.SetCenterPosition(playerData[5]->box.GetCenter());

	// deleta elementos antigos e adiciona atualizados
	playerData.clear();
	playerData.push_back(hpbar);
	playerData.push_back(go_hpdata);
	playerData.push_back(spbar);
	playerData.push_back(go_spdata);
	playerData.push_back(apbar);
	playerData.push_back(go_apdata);

	// Atualiza HUD Armor -------------------------
	// detecta presenca de armadura
	if (player->GetArmor() != 0) {

		// carrega barra azul
		GameObject* bluebar = new GameObject;
		Component* bluebar_img = new Sprite(*bluebar, "img/resources/blue bar.png", 1, 0);
		bluebar->AddComponent(bluebar_img);
		bluebar->box.SetDimensions(HUDBAR_W, HUDBAR_H);
		bluebar->box.MoveThis(*new Vec2(HUD_POS_X, HUD_POS_Y + (3 * HUD_Y_OFFSET)));

		// atualiza string de armadura
		string armor = "Armadura: " + to_string(player->GetArmor());
		GameObject* go_armordata = new GameObject();
		Text* armordata = new Text(*go_armordata,
							  "font/nk57-monospace-no-rg.otf", 18,
							  Text::TextStyle::BLENDED,
							  armor,
							  color.white, 0);
		go_armordata->AddComponent((Component*) armordata);
		go_armordata->box.SetCenterPosition(bluebar->box.GetCenter());

		// adiciona elementos
		playerData.push_back(bluebar);
		playerData.push_back(go_armordata);
	}
}

void CombatState::Update(float dt) {
	UpdateArray(dt);

	InputManager* input = &(InputManager::GetInstance());
	popRequested = input->QuitRequested();

	// comportamentos para teste do HUD dinâmico
	// Espaco -> diminui atributos
	Player* player = Player::GetInstance();
	if (input->KeyPress(SPACE_KEY)) {
		player->TakeDamage(1);
		player->SpendAP(1);
		player->LoseSP(1);
	}

	// P -> aumenta atributos
	if (input->KeyPress(P_KEY)) {
		player->Heal(1);
		player->ResetAP();
		player->GainSP(1);
		player->GainArmor(1);
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
