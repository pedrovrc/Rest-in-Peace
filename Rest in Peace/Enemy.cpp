#include "Enemy.h"
#include "Player.h"

Enemy::Enemy() {
	hp = 20;
	freezeAmount = 0;
	weaknessAmount = 0;
	weaknessAmountPerma = 0;
}

Enemy::~Enemy() {

}

void Enemy::TurnAction() {
	int dmg = 5 - weaknessAmount;
	if (dmg < 0) dmg = 0;
	Player::GetInstance()->TakeDamage(dmg);
	weaknessAmount = 0;
	freezeAmount--;
	if (freezeAmount < 0) freezeAmount = 0;
}

void Enemy::TakeDamage(int dmg_amount) {
	hp -= dmg_amount + freezeAmount;
	if (hp < 0) hp = 0;
}

int Enemy::GetHP() {
	return hp;
}

int Enemy::GetFreeze() {
	return freezeAmount;
}

int Enemy::GetWeakness() {
	return weaknessAmount + weaknessAmountPerma;
}

void Enemy::ApplyFreeze(int val) {
	freezeAmount += val;
}

void Enemy::ApplyWeakness(int val) {
	weaknessAmount += val;
}

void Enemy::ApplPermayWeakness(int val) {
	weaknessAmountPerma += val;
}
