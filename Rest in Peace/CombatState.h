#ifndef COMBATSTATE_H_
#define COMBATSTATE_H_

#include "State.h"
#include "Music.h"

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
