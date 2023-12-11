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
	string opponent;
	string ambient;
	bool flagInitialScreen;
	bool flagChoice;

	void LoadAmbient(string type);
	void LoadTextAndMusic();
	void LoadOpponent(string type);

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
