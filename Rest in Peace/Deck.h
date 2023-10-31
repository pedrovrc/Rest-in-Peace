#ifndef DECK_H
#define DECK_H

#include "Card.h"

class Deck {
public:
	vector<GameObject*> list;

	Deck();
	virtual ~Deck();
	GameObject* DrawOne();
	void AddCard();
	void RemoveCard();
};



#endif /* DECK_H_ */
