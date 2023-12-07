#ifndef EVENT_H
#define EVENT_H

#include "ExploreState.h"
class ExploreState;

class Event {
	ExploreState* motherState;
	int currentStage;
	bool choiceActive;
	vector<int> choiceArray;
	bool started;
	bool ended;

public:
	Event(string type, ExploreState* state);
	~Event();

	int GetStage();
	bool IsChoiceActive();
	int GetChoiceResult(int choiceID);
	Button* GetButton(int index);
	bool Started();
	bool Ended();

	void Update(float dt);

	void LoadAssets();
	void LoadText(string id);
	void LoadButton(string id, string position);
};

#endif /* EVENT_H */
