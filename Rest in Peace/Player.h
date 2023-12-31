#ifndef PLAYER_H_
#define PLAYER_H_

#include <bits/stdc++.h>
using namespace std;

#include "Deck.h"
#include "Item.h"
#include "Buff.h"
#include "Button.h"

#define PLAYER_MAX_HP 20
#define PLAYER_MAX_AP 3
#define PLAYER_MAX_SP 10
#define PLAYER_HAND_SIZE 4

/*
 * Classe Player
 *
 * Implementa as funcionalidades e armazena os dados do jogador.
 */

class Player {
	int hp;		// pontos de vida
	int ap;		// pontos de acao
	int sp;		// pontos de sanidade
	int armor;	// pontos de armadura
	Deck deck;
	Deck discard;
	vector<GameObject*> hand;
	vector<Item> itemList;
	vector<Buff> buffList;
	bool dmgTaken;

	static Player* instance;

public:
	Player();
	~Player();
	static Player* GetInstance();

	bool TookDamage();
	int GetDeckSize();

	Card * GetCardFromHand(int val);
	void DeleteCardFromHand(int val);
	GameObject * GetDeadCard(int val);
	void DeleteCard(GameObject * go);
	int GetHandSize();
	void DiscardHand();
	Button * GetButtonFromHand(int val);

	void SoundCardFromHand(int val);

	int GetHP();
	void TakeDamage(int dmg_amount);
	void Heal(int heal_amount);

	int GetAP();
	bool SpendAP(int quantity);
	void ResetAP();

	int GetSP();
	void LoseSP(int quantity);
	void GainSP(int quantity);

	int GetArmor();
	void GainArmor(int quantity);
	void LoseArmor(int quantity);

	void DrawHand(int quantity);
	void DrawRequired();
	void RenderHand();

	void Update(float dt);

	// metodos de deck

	// metodos de itens

	// metodos de buffs
};



#endif /* PLAYER_H_ */
