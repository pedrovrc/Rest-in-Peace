#ifndef BUTTON_H
#define BUTTON_H

#include <bits/stdc++.h>
using namespace std;

#include "Component.h"

class Button : public Component {

public:
	Button(GameObject& associated);
	void Update(float dt);
	void Render();
	void Start();
	bool Is(string type);
	void NotifyCollision(GameObject& other);
};

#endif
