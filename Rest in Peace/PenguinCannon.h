#ifndef PENGUINCANNON_H
#define PENGUINCANNON_H

#include <bits/stdc++.h>
using namespace std;

#include "Component.h"
#include "Timer.h"

#define PENGUIN_DMG 10
#define PENGUIN_MAX_DISTANCE 1000
#define BULLET_OFFSET 70
#define SHOT_COOLDOWN 0.5

class PenguinCannon : public Component {
	weak_ptr<GameObject> pbody;
	float angle;
	Timer cooldown;
public:
	PenguinCannon(GameObject& associated, weak_ptr<GameObject> penguinBody);
	void Update(float dt);
	void Render();
	bool Is(string type);
	void Start();
	void Shoot();
	void NotifyCollision(GameObject& other);
};

#endif
