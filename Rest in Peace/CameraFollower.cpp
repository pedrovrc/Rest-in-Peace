#include "CameraFollower.h"
#include "Camera.h"

CameraFollower::CameraFollower(GameObject& go) : Component(go) {

}

/*
 * void CameraFollower::Update(float dt)
 *
 * Atualiza parâmetros para seguir câmera.
 */
void CameraFollower::Update(float dt) {
	associated.box.SetPosition(Camera::pos);
}

void CameraFollower::Start() {

}

void CameraFollower::Render() {

}

bool CameraFollower::Is(string type) {
	if (type == "CameraFollower") return true;
	return false;
}

void CameraFollower::NotifyCollision(GameObject& other) {

}
