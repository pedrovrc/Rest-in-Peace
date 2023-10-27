#include "Player.h"

Player* Player::instance;

Player::Player() {
	if (instance != nullptr) {
		return;
	}
	instance = this;
	hp = PLAYER_MAX_HP;
	ap = PLAYER_MAX_AP;
	sp = PLAYER_MAX_SP;
	armor = 0;
}

Player::~Player() {

}

Player& Player::GetInstance() {
	if (instance == nullptr) {
		instance = new Player();
	}
		return *instance;
}

int Player::GetHP() {

}

void Player::TakeDamage(int dmg_amount) {

}

void Player::Heal(int heal_amount) {

}

int Player::GetAP() {

}

bool Player::SpendAP(int quantity) {

}

void Player::ResetAP() {

}

int Player::GetSP() {

}

void Player::LoseSP(int quantity) {

}
void Player::GainSP(int quantity) {

}

int Player::GetArmor() {

}

void Player::GainArmor(int quantity) {

}

void LoseArmor(int quantity) {

}
