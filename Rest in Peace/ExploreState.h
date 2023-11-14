#ifndef EXPLORESTATE_H
#define EXPLORESTATE_H

#include "State.h"

/*
 * Classe ExploreState
 *
 * Classe que implementa a tela de exploração.
 */

class ExploreState : public State {
	vector<GameObject*> button_list;

public:
	ExploreState();
	~ExploreState();

	void LoadAssets();
	void Update(float dt);
	void Render();

	void Start();
	void Pause();
	void Resume();

	void LoadScreen();
	void LoadAmbient(string type);
	void LoadButton(string type);
};



#endif /* EXPLORESTATE_H_ */
