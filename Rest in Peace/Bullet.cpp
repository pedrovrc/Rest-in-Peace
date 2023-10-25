#include "Bullet.h"
#include "Sprite.h"
#include "GeneralFunctions.h"
#include "Collider.h"

Bullet::Bullet( GameObject& associated,
				float angle,
				int damage,
				float maxDistance,
				string sprite,
				int frameCount,
				int frameTime,
				bool targetsPlayer) : Component(associated) {
	this->targetsPlayer = targetsPlayer;

	Component* img = new Sprite(associated, sprite, frameCount, frameTime);
	associated.AddComponent(img);

	Sprite* spritecpt = (Sprite*)img;
	associated.box.MoveThis(*new Vec2(-spritecpt->GetWidth()/2, -spritecpt->GetHeight()/2));

	this->damage = damage;
	distanceLeft = maxDistance;
	speed.Set(BULLET_SPEED, 0);
	speed.RotateThis(angle);
	associated.angleDeg = Rad2Deg(angle);

	Component* collider = new Collider(associated);
	associated.AddComponent(collider);
}

/*
 * 	void Bullet::Update(float dt)
 *
 * 	Move o projétil na direção setada com a velocidade setada.
 * 	Requisita deleção caso distância máxima percorrida seja alcançada.
 */
void Bullet::Update(float dt) {
	Vec2 velocity = speed * (dt * 10);
	associated.box.MoveThis(velocity);
	distanceLeft -= velocity.GetMagnitude();
	if (distanceLeft <= 0) {
		associated.RequestDelete();
	}
	return;
}

void Bullet::Render() {

}

bool Bullet::Is(string type) {
	if (type == "Bullet") return true;
	return false;
}

int Bullet::GetDamage() {
	return damage;
}

void Bullet::Start() {
}

/*
 * 	bool Bullet::PlayerHit(GameObject& go)
 *
 * 	Retorna true se a bala for destinada ao player e o GameObject fornecido for de um player.
 */
bool Bullet::PlayerHit(GameObject& go) {
	if (targetsPlayer && go.GetComponent("PenguinBody")) return true;
	else return false;
}

/*
 * 	bool Bullet::AlienHit(GameObject& go)
 *
 * 	Retorna true se a bala for destinada a um alien e o GameObject fornecido for de um alien.
 */
bool Bullet::AlienHit(GameObject& go) {
	if ((!targetsPlayer) && go.GetComponent("Alien")) return true;
	else return false;
}

/*
 * 	void Bullet::NotifyCollision(GameObject& other)
 *
 * 	Implementa comportamento no caso de colisão adequada (deleta GameObject da Bullet).
 */
void Bullet::NotifyCollision(GameObject& other) {
	if (PlayerHit(other) || AlienHit(other)) {
		associated.RequestDelete();
	}
}
