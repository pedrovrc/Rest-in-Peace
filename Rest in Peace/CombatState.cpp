#include "CombatState.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Text.h"
#include "Player.h"
#include "Button.h"
#include "GeneralFunctions.h"
#include "Game.h"
#include "EndState.h"
#include <time.h>

CombatState::CombatState(string ambient, string opponent) {
	quitRequested = false;
	started = false;
	turnCounter = 0;
	enemy = new Enemy();
	this->ambient = ambient;
	this->opponent = opponent;
	espreitarCount = -1;
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
	LoadAmbient(ambient);

	// carrega ilustracao e dados do painel do 	oponente
	LoadOpponent(opponent);

	// carrega ilustrações e dados do painel do player
	LoadPlayerProfile();

	// carrega ilustrações e dados do painel de combate
	LoadCombatAssets();
}

void CombatState::LoadScreen() {
	// Carrega imagem do fundo da tela
	GameObject* screen = new GameObject;
	CreateAddSprite(screen, "img/screens/combatscreen.png", 1, 0, *new Vec2(0,0), -1, -1);
	AddObject(screen);
}

void CombatState::LoadAmbient(string type) {
	// Carrega ilustração do fundo da tela
	GameObject* ambient = new GameObject;
	string filename;
	if (type == "living room") {
		filename = "img/old_haunted_house_blur.png";
	}
	CreateAddSprite(ambient, filename, 1, 0, *new Vec2(0,0), -1, -1);
	AddObject(ambient);

	// abre musica
	combatMusic.Open("audio/combatMusic.mp3");
}

void CombatState::LoadOpponent(string type) {
	Colors& color = Colors::GetInstance();

	// carrega sprite do oponente
	GameObject* opponent = new GameObject;
	CreateAddCenteredSprite(opponent, "img/enemies/diabrete.png", 1, 0,
							*new Vec2(ILLUST_CENTER_X,ILLUST_CENTER_Y), -1, -1);
	AddObject(opponent);

	// carrega textos
	// carrega nome
	GameObject* go_name = new GameObject();
	CreateAddText(go_name, "nk57-monospace-no-rg.otf", 30, "Diabrete", -1, -1, color.white, 0);
	go_name->box.SetCenterPosition(*new Vec2(ILLUST_CENTER_X,40));
	AddObject(go_name);

	// carrega HP
	GameObject* go_hpdata = new GameObject();
	CreateAddText(go_hpdata, "nk57-monospace-no-rg.otf", 30, "PV 20/20", -1, -1, color.white, 0);
	go_hpdata->box.SetCenterPosition(*new Vec2(ILLUST_CENTER_X,80));
	enemyData.push_back(go_hpdata);

	GameObject* go_freeze = new GameObject();
	CreateAddText(go_freeze, "nk57-monospace-no-rg.otf", 15, "Congelado: 0", -1, -1, color.white, 0);
	go_freeze->box.SetCenterPosition(*new Vec2(ILLUST_CENTER_X,120));
	enemyData.push_back(go_freeze);

	GameObject* go_weakness = new GameObject();
	CreateAddText(go_weakness, "nk57-monospace-no-rg.otf", 15, "Fraqueza: 0", -1, -1, color.white, 0);
	go_weakness->box.SetCenterPosition(*new Vec2(ILLUST_CENTER_X,160));
	enemyData.push_back(go_weakness);
}

void CombatState::LoadPlayerProfile() {
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
	CreateAddText(go_spdata, NK57, 20, sp, -1, -1, color.black, 0);
	go_spdata->box.SetCenterPosition(graybar->box.GetCenter());
	playerData.push_back(go_spdata);

	// Carrega HUD Actions ----------------------
	// barra cinza
	GameObject* graybar2 = new GameObject;
	CreateAddSprite(graybar2, "img/resources/gray bar.png", 1, 0,
					*new Vec2(HUD_POS_X, HUD_POS_Y + (2 * HUD_Y_OFFSET)),
					HUDBAR_W, HUDBAR_H);
	AddObject(graybar2);

	// barra amarela
	GameObject* apbar = new GameObject;
	CreateAddSprite(apbar, "img/resources/yellow bar.png", 1, 0,
					*new Vec2(HUD_POS_X, HUD_POS_Y + (2 * HUD_Y_OFFSET)),
					HUDBAR_W * ((float)player->GetAP()/PLAYER_MAX_AP), HUDBAR_H);
	playerData.push_back(apbar);

	// texto na barra
	string ap = "Ações: " + to_string(player->GetAP()) + "/" + to_string(PLAYER_MAX_AP);
	GameObject* go_apdata = new GameObject();
	CreateAddText(go_apdata, NK57, 20, ap, -1, -1, color.black, 0);
	go_apdata->box.SetCenterPosition(graybar2->box.GetCenter());
	playerData.push_back(go_apdata);
}

void CombatState::LoadCombatAssets() {
	Player::GetInstance()->DrawRequired();
	Player::GetInstance()->DrawHand(PLAYER_HAND_SIZE-Player::GetInstance()->GetHandSize());
}

void CombatState::UpdatePlayerData() {
	Colors& color = Colors::GetInstance();
	Player* player = Player::GetInstance();

	// Atualiza HUD HP ---------------------
	// refaz barra verde
	GameObject* hpbar = new GameObject;
	CreateAddSprite(hpbar, "img/resources/green bar.png", 1, 0,
					*new Vec2(HUD_POS_X, HUD_POS_Y),
					HUDBAR_W * ((float)player->GetHP()/PLAYER_MAX_HP), HUDBAR_H);

	// refaz string de vida
	string hp = "Vida: " + to_string(player->GetHP()) + "/" + to_string(PLAYER_MAX_HP);
	GameObject* go_hpdata = new GameObject();
	CreateAddText(go_hpdata, NK57, 18, hp, -1, -1, color.white, 0);
	go_hpdata->box.SetCenterPosition(playerData[1]->box.GetCenter());

	// Atualiza HUD SP -------------------------------
	// refaz barra branca
	GameObject* spbar = new GameObject;
	CreateAddSprite(spbar, "img/resources/white bar.png", 1, 0,
					*new Vec2(HUD_POS_X, HUD_POS_Y + HUD_Y_OFFSET),
					HUDBAR_W * ((float)player->GetSP()/PLAYER_MAX_SP), HUDBAR_H);

	// refaz string de sanidade
	string sp = "Sanidade: " + to_string(player->GetSP()) + "/" + to_string(PLAYER_MAX_SP);
	GameObject* go_spdata = new GameObject();
	CreateAddText(go_spdata, NK57, 15, sp, -1, -1, color.black, 0);
	go_spdata->box.SetCenterPosition(playerData[3]->box.GetCenter());

	// Atualiza HUD Actions ----------------------------
	// refaz barra amarela
	GameObject* apbar = new GameObject;
	CreateAddSprite(apbar, "img/resources/yellow bar.png", 1, 0,
					*new Vec2(HUD_POS_X, HUD_POS_Y + (2 * HUD_Y_OFFSET)),
					HUDBAR_W * ((float)player->GetAP()/PLAYER_MAX_AP), HUDBAR_H);

	// refaz string de acoes
	string ap = "Ações: " + to_string(player->GetAP()) + "/" + to_string(PLAYER_MAX_AP);
	GameObject* go_apdata = new GameObject();
	CreateAddText(go_apdata, NK57, 20, ap, -1, -1, color.black, 0);
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
		CreateAddSprite(bluebar, "img/resources/blue bar.png", 1, 0,
						*new Vec2(HUD_POS_X, HUD_POS_Y + (3 * HUD_Y_OFFSET)), HUDBAR_W, HUDBAR_H);

		// atualiza string de armadura
		string armor = "Armadura: " + to_string(player->GetArmor());
		GameObject* go_armordata = new GameObject();
		CreateAddText(go_armordata, NK57, 18, armor, -1, -1, color.white, 0);
		go_armordata->box.SetCenterPosition(bluebar->box.GetCenter());

		// adiciona elementos
		playerData.push_back(bluebar);
		playerData.push_back(go_armordata);
	}
}

void CombatState::UpdateEnemyData() {
	Colors& color = Colors::GetInstance();
	enemyData.clear();

	// Atualiza HUD HP Inimigo ---------------------
	string hpenemy = "HP: " + to_string(enemy->GetHP()) + "/" + to_string(ENEMY_MAX_HP);
	GameObject* go_hpenemydata = new GameObject();
	CreateAddText(go_hpenemydata, NK57, 30, hpenemy, -1, -1, color.white, 0);
	go_hpenemydata->box.SetCenterPosition(*new Vec2(ILLUST_CENTER_X,80));
	enemyData.push_back(go_hpenemydata);

	// Atualiza HUD Gelo Inimigo ---------------------
	if(enemy->GetFreeze() != 0) {
		string freezeenemy = "Congelado: " + to_string(enemy->GetFreeze());
		GameObject* go_freezeenemydata = new GameObject();
		CreateAddText(go_freezeenemydata, NK57, 15, freezeenemy, -1, -1, color.white, 0);
		go_freezeenemydata->box.SetCenterPosition(*new Vec2(ILLUST_CENTER_X,120));
		enemyData.push_back(go_freezeenemydata);
	}

	// Atualiza HUD Fraqueza Inimigo ---------------------
	if(enemy->GetWeakness() != 0) {
		string weaknessenemy = "Fraqueza: " + to_string(enemy->GetWeakness());
		GameObject* go_weaknessenemydata = new GameObject();
		CreateAddText(go_weaknessenemydata, NK57, 15, weaknessenemy, -1, -1, color.white, 0);
		go_weaknessenemydata->box.SetCenterPosition(*new Vec2(ILLUST_CENTER_X,140));
		enemyData.push_back(go_weaknessenemydata);
	}
}

bool CombatState::UseCard(int val) {
	Player* player = Player::GetInstance();
	if((player->GetAP() >= player->GetCardFromHand(val)->GetCost()) &&
			player->GetSP() >= player->GetCardFromHand(val)->sanityCost)
	    {
			srand((int)time(NULL));
			int temp = rand();

	        switch(player->GetCardFromHand(val)->t)
	        {
	        case DAMAGE:
	            player->SpendAP(player->GetCardFromHand(val)->GetCost());
	            enemy->TakeDamage(player->GetCardFromHand(val)->quantity);
	            player->LoseSP(player->GetCardFromHand(val)->sanityCost);
	            player->DeleteCardFromHand(val);
	            break;
	        case HEALING:
	            player->SpendAP(player->GetCardFromHand(val)->GetCost());
	            player->Heal(player->GetCardFromHand(val)->quantity);
	            player->LoseSP(player->GetCardFromHand(val)->sanityCost);
	            player->DeleteCardFromHand(val);
	            break;
	        case ARMOR:
	            player->SpendAP(player->GetCardFromHand(val)->GetCost());
	            player->GainArmor(player->GetCardFromHand(val)->quantity);
	            player->LoseSP(player->GetCardFromHand(val)->sanityCost);
	            player->DeleteCardFromHand(val);
	            break;
	        case SANITY:
	            player->SpendAP(player->GetCardFromHand(val)->GetCost());
	            player->LoseSP(player->GetCardFromHand(val)->sanityCost);
				player->DiscardHand();
				player->DrawHand(PLAYER_HAND_SIZE);
	        	break;
	        case CONGELADO:
				player->SpendAP(player->GetCardFromHand(val)->GetCost());
				player->LoseSP(player->GetCardFromHand(val)->sanityCost);
				enemy->ApplyFreeze(player->GetCardFromHand(val)->quantity);
				player->DeleteCardFromHand(val);
				break;
	        case LAGRIMAS:
				player->SpendAP(player->GetCardFromHand(val)->GetCost());
				player->LoseSP(player->GetCardFromHand(val)->sanityCost);
				enemy->ApplyWeakness(player->GetCardFromHand(val)->quantity);
				player->DeleteCardFromHand(val);
				break;
	        case TRUQUE:
	        	player->SpendAP(player->GetCardFromHand(val)->GetCost());
				player->LoseSP(player->GetCardFromHand(val)->sanityCost);
				player->DiscardHand();
				player->DrawHand(PLAYER_HAND_SIZE);
				for (int i = 0; i < player->GetHandSize(); i++) {
					if(temp%2 == 1) player->GetCardFromHand(i)->ModifyCost(1);
					else player->GetCardFromHand(i)->ModifyCost(-1);
					temp++;
				}
				break;
	        case DIABRURA:
				player->SpendAP(player->GetCardFromHand(val)->GetCost());
				player->LoseSP(player->GetCardFromHand(val)->sanityCost);
				enemy->TakeDamage(5+(player->GetHP()/4));
				player->DeleteCardFromHand(val);
				break;
	        case RISADA:
				player->SpendAP(player->GetCardFromHand(val)->GetCost());
				player->LoseSP(player->GetCardFromHand(val)->sanityCost);
				enemy->ApplPermayWeakness(2);
				player->GainSP(3);
				player->DeleteCardFromHand(val);
				break;
	        case ESPREITAR:
				player->SpendAP(player->GetCardFromHand(val)->GetCost());
				player->LoseSP(player->GetCardFromHand(val)->sanityCost);
				espreitarCount = 0;
				player->DeleteCardFromHand(val);
				break;
	        case DEVORAR:
				player->SpendAP(player->GetCardFromHand(val)->GetCost());
				player->LoseSP(player->GetCardFromHand(val)->sanityCost);
				if(enemy->GetHP() <= 12) player->Heal(4);
				enemy->TakeDamage(12);
				player->DeleteCardFromHand(val);
				break;
	        }
	        return 1;
	    }
	    else
	    {
	    	return 0;
	    }
	return true;
}

void CombatState::Update(float dt) {
	UpdateArray(dt);
	Player* player = Player::GetInstance();

	// condição de término de jogo
	if(player->GetHP() <= 0 || enemy->GetHP() <= 0) {
		Game& game = game.GetInstance();

		if (player->GetHP() <= 0) {
			game.gameData.playerVictory = false;
		} else {
			game.gameData.playerVictory = true;
		}

		State* state = (State*) new EndState(opponent, ambient);
		game.Push(state);

		popRequested = true;
		return;
	}

	InputManager* input = &(InputManager::GetInstance());
	popRequested = input->QuitRequested();

	// comportamentos para teste do HUD dinâmico
	// Espaco -> diminui atributos
	player->Update(dt);

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

	Button* cardButton;
	for (int i = 0; i < player->GetHandSize(); i++) {
		cardButton = player->GetButtonFromHand(i);
		if(cardButton->IsHovered() && input->MousePress(LEFT_MOUSE_BUTTON)) {
			UseCard(i);
		}
	}

//	if (input->KeyPress(N1_KEY)) {
//		UseCard(0);
//	}
//	if (input->KeyPress(N2_KEY)) {
//		UseCard(2);
//	}
//	if (input->KeyPress(N3_KEY)) {
//		UseCard(3);
//	}
//	if (input->KeyPress(N4_KEY)) {
//			UseCard(4);
//	}
	if (input->KeyPress(N5_KEY)) {
		TurnPass();
	}
	UpdatePlayerData();
	UpdateEnemyData();
	for(int i = 0; i < player->GetHandSize(); i++) {
		GameObject * go = player->GetDeadCard(i);
		if(go != nullptr) {
			player->DeleteCard(go);
		}
	}
}


void CombatState::TurnPass() {
	Player* player = Player::GetInstance();
	player->ResetAP();
	enemy->TurnAction();
	player->DrawHand(PLAYER_HAND_SIZE-player->GetHandSize());
	turnCounter++;
	if(espreitarCount != -1) {
		espreitarCount++;
		if(espreitarCount >= 2) {
			enemy->TakeDamage(30);
		}
	}
}

void CombatState::Render() {
	this->RenderArray();
	this->RenderPlayerData();
	this->RenderEnemyData();
	Player::GetInstance()->RenderHand();
}

void CombatState::RenderPlayerData() {
	for (int i = 0; i < (int)playerData.size(); i++) {
		playerData[i]->Render();
	}
}

void CombatState::RenderEnemyData() {
	for (int i = 0; i < (int)enemyData.size(); i++) {
		enemyData[i]->Render();
	}
}

void CombatState::DeleteText(string id) {

}

void CombatState::Start() {
	LoadAssets();
	combatMusic.Play();
}

void CombatState::Pause() {
	combatMusic.Stop();
}

void CombatState::Resume() {
	combatMusic.Play();
}
