#ifndef EXPLORESTATE_H
#define EXPLORESTATE_H

#include "State.h"
#include "Button.h"
#include "Event.h"
class Event;

#define AVATAR_POS_X 1268
#define AVATAR_POS_Y 21
#define AVATAR_SIZE 146
#define HUDBAR_W 150
#define HUDBAR_H 25
#define HUD_POS_Y 85
#define HUD_Y_OFFSET 35
#define HUD_POS_X 1430

/*
 * Classe ExploreState
 *
 * Classe que implementa a tela de exploração.
 */

class ExploreState : public State {
	vector<GameObject*> button_list;
	vector<GameObject*> playerData;
	Event* event;
	bool intro;

	void LoadScreen();
	void LoadAmbient(string type);
	void LoadPlayerProfile();
	void LoadExecIntro();

	void RenderPlayerData();

public:
	ExploreState(string type);
	~ExploreState();

	void LoadAssets();
	void LoadCombatState();
	void Update(float dt);
	void Render();

	void Start();
	void Pause();
	void Resume();

	void AddButton(GameObject* button);

	Button* GetButton(string id);

	void DeleteButton(string id);
	void DeleteText(string id);
};

#endif /* EXPLORESTATE_H_ */
