#ifndef STAGESTATE_H
#define STAGESTATE_H

#include "State.h"
#include "Music.h"

/*
 * Classe State
 *
 * Responsável por gerenciar as telas de jogo e os GameObjects.
 */
class StageState : public State {
	Music backgroundMusic;
public:
	StageState();
	~StageState();

	void LoadAssets();
	void Update(float dt);
	void Render();

	void Start();
	void Pause();
	void Resume();

	weak_ptr<GameObject> GetPlayerGO();
};

#endif
