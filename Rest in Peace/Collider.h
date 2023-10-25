#ifndef COLLIDER_H
#define COLLIDER_H

#include <bits/stdc++.h>
using namespace std;

#include "Component.h"

/*
 * 	Class Collider
 *
 * 	Componente utilizado para implementar detecção de colisões
 * 	entre GameObjects.
 */
class Collider : public Component {
	Vec2 scale;
	Vec2 offset;
	bool debugFlag;
public:
	Collider( GameObject& associated,
			  Vec2 scale = *new Vec2(1,1),
			  Vec2 offset = *new Vec2(0,0));
	Rect box;
	void Update(float dt);
	void Render();
	void Start();
	bool Is(string type);
	void SetScale(Vec2 newScale);
	void SetOffset(Vec2 newOffset);
	void NotifyCollision(GameObject& other);
};

#endif
