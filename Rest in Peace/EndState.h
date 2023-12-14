#ifndef ENDSTATE_H
#define ENDSTATE_H

#include "State.h"
#include "Music.h"
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
 * Classe EndState
 *
 * Classe que implementa a tela de fim de jogo.
 */

class EndState : public State {
	Music backgroundMusic;
	vector<GameObject*> button_list;
	string opponent;
	string ambient;
	bool flagInitialScreen;
	bool flagChoice;
	bool end;
	GameObject* timeText;

	void LoadAmbient(string type);
	void LoadTextAndMusic();
	void LoadOpponent(string type);
	void LoadScreen();
	void LoadButton(string id, string position);
	void LoadText(string id);
	void LoadPlayerProfile();

	void UpdateTime();

	void EraseAllObjects();
	void DeleteButton(string id);
	void DeleteText(string id);

	Button* GetButton(string id);

public:
	EndState(string opponent, string ambient);
	~EndState();

	void LoadAssets();
	void Update(float dt);
	void Render();

	void Start();
	void Pause();
	void Resume();
};

#endif
