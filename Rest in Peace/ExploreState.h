#ifndef EXPLORESTATE_H
#define EXPLORESTATE_H

#include "State.h"
#include "Button.h"

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
	bool intro;
	int currentStage;
	bool choiceActive;
	vector<int> choiceArray;

	void LoadScreen();
	void LoadAmbient(string type);
	void LoadPlayerProfile();
	void LoadExecIntro();
	void LoadText(string id);
	void LoadButton(string id, string position);

	void DeleteButton(string id);
	void DeleteText(string id);

	int GetChoiceResult(int choiceID);
	Button* GetButton(int index);

	void RenderPlayerData();

public:
	ExploreState(string type);
	~ExploreState();

	void LoadAssets();
	void Update(float dt);
	void Render();

	void Start();
	void Pause();
	void Resume();
};



#endif /* EXPLORESTATE_H_ */
