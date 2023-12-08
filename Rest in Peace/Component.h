#ifndef COMPONENT_H
#define COMPONENT_H

#include <bits/stdc++.h>
using namespace std;

class GameObject;

#include "GameObject.h"

/*
 * Classe Component
 *
 * Classe abstrata que serve de molde para classes de assets.
 */
class Component {
protected:
	GameObject& associated;
public:
	Component(GameObject& associated);
	virtual ~Component();
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void Start() = 0;
	virtual bool Is(string type) = 0;
};

#endif
