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
	bool intro;
public:
	ExploreState(string type);
	~ExploreState();

	void LoadAssets();
	void Update(float dt);
	void Render();

	void Start();
	void Pause();
	void Resume();

	void LoadScreen();
	void LoadAmbient(string type);
	void LoadIntroText();
	void LoadButton(string type);

	string ReadAllFromFile(string path);
};



#endif /* EXPLORESTATE_H_ */
