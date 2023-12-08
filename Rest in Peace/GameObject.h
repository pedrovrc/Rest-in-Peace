#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <bits/stdc++.h>
using namespace std;

class Component;

#include "Rect.h"
#include "Component.h"

/*
 * Clase GameObject
 *
 * Responsável por conter um ou mais objetos derivados da classe Component.
 */
class GameObject {
	vector<unique_ptr<Component>> components{};

	bool isDead;
public:
	Rect box;
	bool started;
	double angleDeg;

	GameObject();
	~GameObject();
	void Update(float dt);
	void Render();
	void Start();
	void AddComponent(Component* cpt);
	void RemoveComponent(Component* cpt);
	Component* GetComponent(string type);
	bool IsDead();
	void RequestDelete();
};

#endif
