#ifndef PENGUINBODY_H
#define PENGUINBODY_H

#include <bits/stdc++.h>
using namespace std;

#include "Component.h"

#define HP_MAX 30
#define ACCELERATION 0.8
#define VEL_MAX 10
#define VEL_MIN -6
#define ANGLE_CHANGE 5
#define FRICTION 0.2
#define HORIZONTAL_LIMIT 1408
#define VERTICAL_LIMIT 1280

class PenguinBody : public Component {
	weak_ptr<GameObject> pcannon;
	Vec2 speed;
	float linearSpeed;
	float angle;
	int hp;
public:
	static PenguinBody* player;

	PenguinBody(GameObject& associated);
	~PenguinBody();
	void Start();
	void Update(float dt);
	void Render();
	bool Is(string type);
	void NotifyCollision(GameObject& other);
	void PlayDeathAnimation();
};

#endif
