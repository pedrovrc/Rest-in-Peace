#ifndef CAMERAFOLLOWER_H
#define CAMERAFOLLOWER_H

#include <bits/stdc++.h>
using namespace std;

#include "Component.h"

/*
 * Classe CameraFollower
 *
 * Responsável por seguir a câmera e ajudar no foco de objetos em cena.
 */
class CameraFollower : public Component {
public:
	CameraFollower(GameObject& go);
	void Update(float dt);
	void Render();
	void Start();
	bool Is(string type);
	void NotifyCollision(GameObject& other);
};

#endif
