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

	// carrega deck inicial
	ifstream decklist;
	//cout << "opening deck..." << endl;
	decklist.open("card_info/deck.txt", ifstream::in);

	bool flag = true; // GAMBIARRA PARA FAZER UMA CARTA MAIOR

	if(decklist.is_open())
	{
		cout << "deck opened!" << endl;
		GameObject* go_card;
		while (!(decklist.eof()))
		{
			string effect;
			getline(decklist, effect);

			go_card = new GameObject();
			Component* card = (Component*) new Card(*go_card, effect);
			go_card->AddComponent(card);

			// GAMBIARRA PARA FAZER UMA CARTA MAIOR
			if (flag) {
				flag = false;
				go_card->box.ResizeThis(1.3);
			}

			deck.list.emplace_back(go_card);
		}
		decklist.close();
	}
	//else
		//cout << "erro" << endl;
	//cout << "Deck size is: " << list.size() << endl;

	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	shuffle(deck.list.begin(), deck.list.end(), default_random_engine(seed));
}

Player::~Player() {

}

Player* Player::GetInstance() {
	if (instance == nullptr) {
		instance = new Player();
	}
		return instance;
}

int Player::GetHP() {
	return hp;
}

void Player::TakeDamage(int dmg_amount) {
	int dmg = dmg_amount - armor;
	if (dmg <= 0) {
		dmg = 0;
	}
	if (armor > 0) {
		LoseArmor(dmg_amount);
	}
	hp -= dmg;
	if (hp < 0) hp = 0;
	// CHECAR POR MORTE DO PLAYER
}

void Player::Heal(int heal_amount) {
	hp += heal_amount;
	if (hp > 20) hp = 20;
}

int Player::GetAP() {
	return ap;
}

bool Player::SpendAP(int quantity) {
	if (ap - quantity < 0) return false;
	else ap -= quantity;
	return true;
}

void Player::ResetAP() {
	ap = PLAYER_MAX_AP;
}

int Player::GetSP() {
	return sp;
}

void Player::LoseSP(int quantity) {
	sp -= quantity;
	if (sp < 0) sp = 0;
}

void Player::GainSP(int quantity) {
	sp += quantity;
	if (sp > 10) sp = 10;
}

int Player::GetArmor() {
	return armor;
}

void Player::GainArmor(int quantity) {
	armor += quantity;
}

void Player::LoseArmor(int quantity) {
	armor -= quantity;
	if (armor < 0) armor = 0;
}

void Player::DrawHand(int quantity) {
	for (int i = 0; i < quantity; i++) {
		hand.push_back(deck.DrawOne());
	}
}

void Player::RenderHand() {
	for (int i = 0; i < hand.size(); i++) {
		hand[i]->box.SetPosition(*new Vec2((600 + i * 150),350));
		hand[i]->Render();
	}
}
