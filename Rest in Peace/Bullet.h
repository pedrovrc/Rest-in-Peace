#ifndef BULLET_H
#define BULLET_H

#include <bits/stdc++.h>
using namespace std;

#include "Component.h"

#define BULLET_SPEED 50

/*
 * Class Bullet
 *
 * Classe que representa o projétil atirado pelo alien.
 */
class Bullet : public Component {
	Vec2 speed;
	float distanceLeft;
	int damage;

	bool PlayerHit(GameObject& go);
	bool AlienHit(GameObject& go);
public:
	bool targetsPlayer;

	Bullet( GameObject& associated,
			float angle,
			int damage,
			float maxDistance,
			string sprite,
			int frameCount,
			int frameTime,
			bool targetsPlayer );
	void Update(float dt);
	void Render();
	bool Is(string type);
	int GetDamage();
	void Start();
	void NotifyCollision(GameObject& other);
};

#endif
