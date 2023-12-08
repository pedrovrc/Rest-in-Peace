#include "Player.h"
#include "Button.h"

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
	decklist.open("card_info/deck.txt", ifstream::in);

	if(decklist.is_open())
	{
		GameObject* go_card;
		while (!(decklist.eof()))
		{
			string effect;
			getline(decklist, effect);

			go_card = new GameObject();

			Component* card = (Component*) new Card(*go_card, effect);
			go_card->AddComponent(card);

			Component* button = (Component*) new Button(*go_card, "card");
			go_card->AddComponent(button);

			deck.list.emplace_back(go_card);
		}
		decklist.close();
	}

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
	for (int i = 0; i < (int)hand.size(); i++) {
		if (i == 0) hand[i]->box.SetPosition(*new Vec2(610, 110));
		if (i == 1) hand[i]->box.SetPosition(*new Vec2(920, 110));
		if (i == 2) hand[i]->box.SetPosition(*new Vec2(610, 350));
		if (i == 3) hand[i]->box.SetPosition(*new Vec2(920, 350));
		hand[i]->Render();
	}
}

void Player::Update(float dt) {
	for (int i = 0; i < (int)hand.size(); i++) {
		hand[i]->Update(dt);
	}
}

Card * Player::GetCardFromHand(int val) {
	return (Card*) hand[val]->GetComponent("Card");
}

void Player::DeleteCardFromHand(int val) {
	hand[val]->RequestDelete();
}

void Player::DeleteCard(GameObject * go) {
	int size = hand.size(), i = 0;
	while (i < size) {
		if (go == hand[i]) {
			hand.erase(hand.begin() + i);
			//delete go;
			return;
		}
	i++;
	}
}

GameObject * Player::GetDeadCard(int val) {
	if(val < (int)hand.size()) {
		GameObject * go;
		if(hand[val]->IsDead()) {
			go = hand[val];
			return go;
		}
	}
	return nullptr;
}

int Player::GetHandSize() {
	return (int)hand.size();
}

Button * Player::GetButtonFromHand(int val) {
	return (Button*) hand[val]->GetComponent("Button");
}

void Player::DiscardHand() {
	while(GetHandSize() > 0) {
		GameObject * go = hand[0];
		DeleteCard(go);
	}
}

void Player::DrawRequired() {
	for (int i = 0; i < (int)deck.list.size(); i++) {
		Card * c =(Card*) deck.list[i]->GetComponent("Card");
		if(c->name == "revelação") {
			hand.push_back(deck.DrawThis(i));
			return;
		}
	}
}
