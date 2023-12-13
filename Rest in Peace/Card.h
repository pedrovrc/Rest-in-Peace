#ifndef CARD_H
#define CARD_H

#include "Component.h"
#include "Sprite.h"

enum classification {DAMAGE,
					 HEALING,
					 ARMOR,
					 SANITY,
					 CONGELADO,
					 LAGRIMAS,
					 TRUQUE,
					 DIABRURA,
					 RISADA,
					 ESPREITAR,
					 DEVORAR};

#define ORIGINAL_CARD_W 900
#define ORIGINAL_CARD_H 811
#define BIG_CARD_W 291
#define BIG_CARD_H 323
#define SMALL_CARD_W 250
#define SMALL_CARD_H 226

/*
 * Classe Card
 *
 * Classe que implementa a representação de uma carta do baralho do player.
 * Utiliza regex para sua inicialização com base em um arquivo txt.
 */

class Card : public Component {
	GameObject* modCostPlus;
	GameObject* modCostMinus;

public:
	Card(GameObject& associated, string str);
	~Card();
	int cost;
	int modCost = 0;
	int sanityCost;
	string name;
	string flavor;
	classification t;
	int quantity;

	void Update(float dt);
	void Render();
	void Start();
	bool Is(string type);
	void ModifyCost(int val);
	int GetCost();
};



#endif /* CARD_H_ */
