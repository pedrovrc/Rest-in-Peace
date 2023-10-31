#ifndef COMBATSTATE_H_
#define COMBATSTATE_H_

#include "State.h"
#include "Music.h"

#define AVATAR_POS_X 1273
#define AVATAR_POS_Y 29
#define AVATAR_SIZE 96
#define ILLUST_CENTER_X 275
#define ILLUST_CENTER_Y 450
#define ILLUST_W 550
#define ILLUST_H 900

class CombatState : public State {
	Music combatMusic;

	void LoadScreen();
	void LoadAmbient(string type);
	void LoadOpponent(string type);
	void LoadPlayerProfile();
	void LoadCombatAssets();
public:
	CombatState();
	~CombatState();

	void LoadAssets();
	void Update(float dt);
	void Render();

	void Start();
	void Pause();
	void Resume();
	weak_ptr<GameObject> GetPlayerGO();
};

#endif /* COMBATSTAGE_H_ */
