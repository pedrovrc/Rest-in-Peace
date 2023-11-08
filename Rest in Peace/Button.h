#ifndef BUTTON_H
#define BUTTON_H

#include <bits/stdc++.h>
using namespace std;

#include "Component.h"
#include "Sprite.h"

class Button : public Component {
private:
	bool isHovered;
	Sprite* overlay;
	Rect overlaybox;

public:
	Button(GameObject& associated, string type);
	void Update(float dt);
	void Render();
	void Start();
	bool Is(string type);
	void NotifyCollision(GameObject& other);
};

#endif
