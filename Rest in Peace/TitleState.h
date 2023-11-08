#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "State.h"

class TitleState : public State {
private:
	vector<GameObject*> button_list;
public:
	TitleState();
	~TitleState();

	void LoadAssets();
	void Update(float dt);
	void Render();

	void Start();
	void Pause();
	void Resume();
	weak_ptr<GameObject> GetPlayerGO();
};

#endif
