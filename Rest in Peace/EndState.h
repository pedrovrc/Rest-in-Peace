#ifndef ENDSTATE_H
#define ENDSTATE_H

#include "State.h"
#include "Music.h"

/*
 * Classe EndState
 *
 * Classe que implementa a tela de fim de jogo.
 */

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
};

#endif
