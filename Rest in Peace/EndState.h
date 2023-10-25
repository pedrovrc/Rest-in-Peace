#ifndef ENDSTATE_H
#define ENDSTATE_H

#include "State.h"
#include "Music.h"

class EndState : public State {
	Music backgroundMusic;

public:
	EndState();
	~EndState();

	void LoadAssets();
	void Update(float dt);
	void Render();

	void Start();
	void Pause();
	void Resume();

	weak_ptr<GameObject> GetPlayerGO();
};

#endif
