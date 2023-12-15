#ifndef COMBATSTATE_H_
#define COMBATSTATE_H_

#include "State.h"
#include "Music.h"
#include "Enemy.h"

#define AVATAR_POS_X 1268
#define AVATAR_POS_Y 21
#define AVATAR_SIZE 146
#define HUDBAR_W 150
#define HUDBAR_H 25
#define HUD_POS_Y 85
#define HUD_Y_OFFSET 35
#define HUD_POS_X 1430
#define ILLUST_CENTER_X 275
#define ILLUST_CENTER_Y 450
#define ILLUST_W 550
#define ILLUST_H 900
#define COMBATBUTTON_W 77
#define COMBATBUTTON_H 77
#define ANIM_THRESHOLD 400

/*
 * Classe CombatState
 *
 * Clase do estado (tela) de combate.
 */

class CombatState : public State {
	Music combatMusic;
	vector<GameObject*> buttonList;
	vector<GameObject*> playerData;
	vector<GameObject*> enemyData;
	vector<GameObject*> historyData;
	vector<string> matchHistory;
	GameObject* enemyHurt;
	GameObject* playerHurt;
	GameObject* playerHeal;
	GameObject movingBox;
	int animationFlag;
	int turnCounter;
	Enemy * enemy;
	string ambient;
	string opponent;
	int espreitarCount;

	void LoadScreen();
	void LoadButtons();
	void LoadAmbient(string type);
	void LoadOpponent(string type);
	void LoadPlayerProfile();
	void LoadCombatAssets();
	void UpdatePlayerData();
	void RenderPlayerData();
	void UpdateEnemyData();
	void RenderEnemyData();
	void UpdateHistoryData();
	void RenderHistoryData();
	bool UseCard(int val);
	void TurnPass();

public:
	CombatState(string ambient, string opponent);
	~CombatState();

	void LoadAssets();
	void Update(float dt);
	void Render();

	void Start();
	void Pause();
	void Resume();

	void DeleteText(string id);
};

#endif /* COMBATSTAGE_H_ */
