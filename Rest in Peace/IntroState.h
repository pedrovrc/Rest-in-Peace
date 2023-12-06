#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "State.h"
#include "Text.h"

#define AVATAR_POS_X 1268
#define AVATAR_POS_Y 21
#define AVATAR_SIZE 146
#define HUDBAR_W 150
#define HUDBAR_H 25
#define HUD_POS_Y 85
#define HUD_Y_OFFSET 35
#define HUD_POS_X 1430

/*
 * Classe IntroState
 *
 * Classe que implementa a tela de exploração.
 */

class IntroState : public State {
	vector<GameObject*> button_list;
	vector<GameObject*> playerData;
	GameObject* profileCover;
	bool animate;
	int currentStage;

	void LoadScreen();
	void LoadAmbient(string type);
	void LoadPlayerProfile();
	void LoadProfileCover();
	void LoadIntroText(int part);
	void LoadButton(string type);

	void DeleteButton(string id);
	void DeleteText(string id);

	void RenderPlayerData();

public:
	IntroState();
	~IntroState();

	void LoadAssets();
	void Update(float dt);
	void Render();

	void Start();
	void Pause();
	void Resume();
};



#endif /* INTROSTATE_H_ */
