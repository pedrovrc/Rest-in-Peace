#ifndef INVENTORYSTATE_H_
#define INVENTORYSTATE_H_

#include "State.h"

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
	weak_ptr<GameObject> GetPlayerGO();
};

#endif /* INVENTORYSTATE_H_ */
