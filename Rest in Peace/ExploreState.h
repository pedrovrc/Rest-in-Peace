#ifndef EXPLORESTATE_H
#define EXPLORESTATE_H

#include "State.h"

/*
 * Classe ExploreState
 *
 * Classe que implementa a tela de exploração.
 */

class ExploreState : public State {
public:
	ExploreState();
	~ExploreState();

	void LoadAssets();
	void Update(float dt);
	void Render();

	void Start();
	void Pause();
	void Resume();
};



#endif /* EXPLORESTATE_H_ */
