#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "State.h"
#include "Music.h"

#define MENUBUTTON_W 505
#define MENUBUTTON_H 121
#define MENUBUTTON_CENTER_X 320
#define MENUBUTTON_CENTER_Y 355

/*
 * Classe TitleState
 *
 * Implementa a tela de menu principal.
 */

class TitleState : public State {
private:
	Music backgroundMusic;
	vector<GameObject*> button_list;
	GameObject* tutorialOverlay;
	GameObject* creditScreen;
	Rect creditsReturnButton;
	bool renderTutorial;
	bool renderCredits;
public:
	TitleState();
	~TitleState();

	void LoadAssets();
	void Update(float dt);
	void Render();

	void Start();
	void Pause();
	void Resume();
};

#endif
