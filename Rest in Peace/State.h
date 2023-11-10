#ifndef STATE_H
#define STATE_H

#include <bits/stdc++.h>
using namespace std;

#include "GameObject.h"

class State {
public:
	State();
	virtual ~State();

	virtual void LoadAssets() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

	virtual void Start() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual weak_ptr<GameObject> AddObject(GameObject* go);
	virtual void DeleteObject(GameObject* go);
	virtual weak_ptr<GameObject> GetObjectPtr(GameObject* go);

	bool PopRequested();
	bool QuitRequested();
protected:
	bool popRequested;
	bool quitRequested;
	bool started;
	vector<shared_ptr<GameObject>> objectArray;

	void StartArray();
	virtual void UpdateArray(float dt);
	virtual void RenderArray();
};

#endif
