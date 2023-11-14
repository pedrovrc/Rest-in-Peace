#include "Enemy.h"
#include "Player.h"

Enemy::Enemy() {
	hp = 20;
}

Enemy::~Enemy() {

}

void Enemy::TurnAction() {
	Player::GetInstance()->TakeDamage(5);
}

void Enemy::TakeDamage(int dmg_amount) {
	hp -= dmg_amount;
	if (hp < 0) hp = 0;
	//cout << "inimigo tomou dano" << endl;
}

int Enemy::GetHP() {
	return hp;
}
