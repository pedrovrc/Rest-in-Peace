#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "State.h"
#include "Text.h"

/*
 * Classe IntroState
 *
 * Classe que implementa a tela de exploração.
 */

class IntroState : public State {
	vector<GameObject*> button_list;
	int currentStage;
public:
	IntroState();
	~IntroState();

	void LoadAssets();
	void Update(float dt);
	void Render();

	void Start();
	void Pause();
	void Resume();

	void LoadScreen();
	void LoadAmbient(string type);
	void LoadIntroText(int part);
	void LoadButton(string type);
};



#endif /* INTROSTATE_H_ */
