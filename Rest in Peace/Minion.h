#ifndef MINION_H
#define MINION_H

#include <bits/stdc++.h>
using namespace std;

#include "Component.h"

#define ANG_VELOC M_PI/60
#define BULLET_DMG 10
#define BULLET_MAX_DISTANCE 1000
#define MINION_ARC_SIZE 150
#define MINION_DMG 10

/*
 * Class Minion
 *
 * Classe que representa as entidades menores do oponente.
 */
class Minion : public Component {
	GameObject* alienCenter;
	float arc;
public:
	Minion( GameObject& associated,
			weak_ptr<GameObject> alienCenter,
			float arcOffsetDeg = 0,
			float size = 1 );
	void Update(float dt);
	void Render();
	void Start();
	bool Is(string type);
	void Shoot(Vec2 target);
	void NotifyCollision(GameObject& other);
};

#endif
