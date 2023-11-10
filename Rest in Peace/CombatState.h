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

/*
 * Classe CombatState
 *
 * Clase do estado (tela) de combate.
 */

class CombatState : public State {
	Music combatMusic;
	vector<GameObject*> playerData;
	vector<GameObject*> enemyData;
	int turnCounter;
	Enemy * enemy;

	void LoadScreen();
	void LoadAmbient(string type);
	void LoadOpponent(string type);
	void LoadPlayerProfile();
	void LoadCombatAssets();
	void UpdatePlayerData();
	void RenderPlayerData();
	void UpdateEnemyData();
	void RenderEnemyData();
	bool UseCard(int val);
	void TurnPass();

public:
	CombatState();
	~CombatState();

	void LoadAssets();
	void Update(float dt);
	void Render();

	void Start();
	void Pause();
	void Resume();
};

#endif /* COMBATSTAGE_H_ */
