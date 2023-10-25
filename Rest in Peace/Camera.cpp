#include "Camera.h"
#include "PenguinBody.h"
#include "Game.h"

GameObject* Camera::focus;
Vec2 Camera::velocity;
Vec2 Camera::pos;
bool Camera::following;

#define CAMERA_SPEED 10

void Camera::Follow(GameObject* newFocus) {
	following = true;
	focus = newFocus;
}

void Camera::Unfollow() {
	following = false;
	focus = nullptr;
}

/*
 * void Camera::Update(float dt)
 *
 * Atualiza posição da câmera com abse no input e no tempo decorrido.
 */
void Camera::Update(float dt) {
	// atualiza foco
	InputManager& input = InputManager::GetInstance();

	// se camera tiver foco, centralize-o na tela
	if (focus != nullptr) {
		// prevencao de acesso indevido a membro following
		if (following == false) following = true;

		Vec2 focusCenter = focus->box.GetCenter();
		pos.Set(focusCenter.x - (WINDOW_WIDTH/2), focusCenter.y - (WINDOW_HEIGHT/2));
		return;
	}

	// se nao tiver foco, responde a input
	// seta velocidade com base em dt e teclas pressionadas
	// soma-se a posicao
	velocity.x = 0;
	velocity.y = 0;
	if (input.KeyPress(LEFT_ARROW_KEY) || input.IsKeyDown(LEFT_ARROW_KEY)) {
		velocity.x -= CAMERA_SPEED;
	}
	if (input.KeyPress(RIGHT_ARROW_KEY) || input.IsKeyDown(RIGHT_ARROW_KEY)) {
		velocity.x += CAMERA_SPEED;
	}
	if (input.KeyPress(UP_ARROW_KEY) || input.IsKeyDown(UP_ARROW_KEY)) {
		velocity.y -= CAMERA_SPEED;
	}
	if (input.KeyPress(DOWN_ARROW_KEY) || input.IsKeyDown(DOWN_ARROW_KEY)) {
		velocity.y += CAMERA_SPEED;
	}
	pos += velocity;

	// prevencao de acesso indevido a membro following
	if (following == true) following = false;
}
