#ifndef CARD_H
#define CARD_H

#include "Component.h"

enum classification {DAMAGE, HEALING, ARMOR};

class Card : public Component {
public:
	Card(GameObject& associated, string str);
	~Card();
	int cost;
	string name;
	string flavor;
	classification t;
	int quantity;

	void Update(float dt);
	void Render();
	void Start();
	bool Is(string type);
	void NotifyCollision(GameObject& other);
};



#endif /* CARD_H_ */
