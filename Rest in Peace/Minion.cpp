#include "Minion.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Game.h"
#include "GeneralFunctions.h"
#include "Collider.h"
#include "Alien.h"

Minion::Minion( GameObject& associated,
				weak_ptr<GameObject> alienCenterArg,
				float arcOffsetDeg,
				float size ) : Component(associated) {
	Component* img = new Sprite(associated, "img/minion.png", 1, 0);
	associated.AddComponent(img);
	alienCenter = alienCenterArg.lock().get();

	// tratamento de entrada
	if (arcOffsetDeg < 0) arcOffsetDeg = -arcOffsetDeg;
	if (arcOffsetDeg > 360) arcOffsetDeg = (int)arcOffsetDeg % 360;
	arc = Deg2Rad(arcOffsetDeg);

	//calcular primeiro valor da box
	Vec2 offset;
	offset.Set(MINION_ARC_SIZE,0);
	offset.RotateThis(arc);
	offset += alienCenter->box.GetCenter();
	offset -= *new Vec2(associated.box.w/2, associated.box.h/2);
	associated.box.SetPosition(offset);

	// aplicar tamanho
	Sprite* spriteimg = (Sprite*)img;
	spriteimg->SetScale(size, size);

	Component* collider = new Collider(associated);
	associated.AddComponent(collider);
}

void Minion::Start() {

}

/*
 * 	void Minion::Update(float dt)
 *
 *	- Checa por existência do alien para requisitar deleção;
 *	- Orbita em volta de alien;
 *	- Rotaciona o sprite para ficar alinhado com alien.
 */
void Minion::Update(float dt) {
	if (alienCenter == nullptr) {
		associated.RequestDelete();
		return;
	}
	// orbitar em volta de alien
	Vec2 center = alienCenter->box.GetCenter();
	Vec2 offset;
	offset.Set(MINION_ARC_SIZE,0);
	offset.RotateThis(arc);
	offset += center;
	offset -= *new Vec2(associated.box.w/2, associated.box.h/2);
	associated.box.SetPosition(offset);
	arc += ANG_VELOC;
	if (arc >= 2.0f * M_PI) arc = 0;

	// rotacionar
	Vec2 direction = center - associated.box.GetCenter();
	associated.angleDeg = Rad2Deg(direction.GetAngle());
}

void Minion::Render() {

}

bool Minion::Is(string type) {
	if(type == "Minion") return true;
	return false;
}

/*
 *	void Minion::Shoot(Vec2 target)
 *
 *	Cria instância de Bullet e adiciona à lista de objetos de State.
 */
void Minion::Shoot(Vec2 target) {
	GameObject* bulletGO = new GameObject();
	bulletGO->box.SetPosition(associated.box.GetCenter());
	float angle = (target - associated.box.GetCenter()).GetAngle();
	Component* bullet = new Bullet( *bulletGO,
									angle,
									BULLET_DMG,
									BULLET_MAX_DISTANCE,
									"img/minionbullet2.png",
									3,
									100,
									true );
	bulletGO->AddComponent(bullet);
	Game::GetInstance().GetCurrentState().AddObject(bulletGO);
}

void Minion::NotifyCollision(GameObject& other) {

}
