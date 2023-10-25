#ifndef CAMERA_H
#define CAMERA_H

#include <bits/stdc++.h>
using namespace std;

#include "GameObject.h"
#include "InputManager.h"
#include "Game.h"

/*
 * Classe Camera
 *
 * Implementa uma câmera pela qual o jogo será visto.
 */
class Camera {
	static GameObject* focus;
public:
	static Vec2 velocity;
	static Vec2 pos;
	static bool following;
	static void Follow(GameObject* newFocus);
	static void Unfollow();
	static void Update(float dt);
};

#endif
