#ifndef BUTTON_H
#define BUTTON_H

#include <bits/stdc++.h>
using namespace std;

#include "Component.h"
#include "Sprite.h"

/*
 * Classe Button
 *
 * Classe usada para detecção de botões com interação do mouse e para
 * display de overlays quando mouse estiver sobre o botão.
 */

class Button : public Component {
private:
	bool isHovered;
	Sprite* overlay;
	Rect overlaybox;
	string id;

public:
	Button(GameObject& associated, string type);
	Button(GameObject& associated, string type, string identifier);
	void Update(float dt);
	void Render();
	void Start();
	bool Is(string type);
	void NotifyCollision(GameObject& other);
	bool IsHovered();
	string GetID();
};

#endif
