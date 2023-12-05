#ifndef DECK_H
#define DECK_H

#include "Card.h"

/*
 * Classe Deck
 *
 * Classe que representa um conjunto (deck) de cartas do Player.
 */

class Deck {
public:
	vector<GameObject*> list;

	Deck();
	virtual ~Deck();
	GameObject* DrawOne();
	GameObject* DrawThis(int val);
	void AddCard();
	void RemoveCard();
};



#endif /* DECK_H_ */
