#ifndef ALIEN_H
#define ALIEN_H

#include <bits/stdc++.h>
using namespace std;

#include "Vec2.h"
#include "GameObject.h"
#include "Minion.h"
#include "Timer.h"

#define MAX_HP 30
#define MAX_SPEED 5.5
#define MINION_COUNT 4
#define ROTATION_SPEED 1
#define MIN_SIZE 0.8
#define MAX_SIZE 1.3
#define ALIEN_DMG 10
#define REST_COOLDOWN 0.2

/*
 * Class Alien
 *
 * Classe que representa a entidade central do oponente.
 */
class Alien : public Component {
	enum AlienState { MOVING, RESTING };
	AlienState state;
	int hp;
	float timeOffset;
	Vec2 speed;
	Vec2 destination;
	Timer restTimer;

	vector<weak_ptr<GameObject>> minionArray;
public:
	static int alienCount;

	Alien(GameObject& associated, int nMinions, int currentCount, float timeOffset);
	~Alien();

	void Start();
	void Update(float dt);
	void Render();
	bool Is(string type);
	void NotifyCollision(GameObject& other);
	Minion* GetClosestMinion(Vec2 target);
	void PlayDeathAnimation();
};

#endif
