#ifndef DECK_H
#define DECK_H

#include "Card.h"

class Deck {
	vector<GameObject*> list;

public:
	Deck();
	virtual ~Deck();
	GameObject* Draw();

};



#endif /* DECK_H_ */
