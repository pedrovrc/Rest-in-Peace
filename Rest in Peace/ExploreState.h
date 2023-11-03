#ifndef EXPLORESTATE_H
#define EXPLORESTATE_H

#include "State.h"

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
	weak_ptr<GameObject> GetPlayerGO();
};



#endif /* EXPLORESTATE_H_ */
