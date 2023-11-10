#ifndef INVENTORYSTATE_H_
#define INVENTORYSTATE_H_

#include "State.h"

/*
 * Classe InventoryState
 *
 * Implementa as telas de inventário (Deck, Itens e Buffs)
 */

class InventoryState : public State {
public:
	InventoryState();
	~InventoryState();

	void LoadAssets();
	void Update(float dt);
	void Render();

	void Start();
	void Pause();
	void Resume();
};

#endif /* INVENTORYSTATE_H_ */
