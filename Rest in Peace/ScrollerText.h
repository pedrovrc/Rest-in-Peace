#ifndef SCROLLER_H
#define SCROLLER_H

#include "Component.h"
#include "Text.h"

enum movement_dir {UP, DOWN};

class ScrollerText : public Component {
	Text* text_ref;
	string id;
	bool canGoUp;
	bool canGoDown;
	GameObject* upArrow;
	Vec2 upArrowPos;
	movement_dir upArrowMovement;
	GameObject* downArrow;
	Vec2 downArrowPos;
	movement_dir downArrowMovement;

	void AnimateArrow(string type);

public:
	ScrollerText(GameObject& associated, Text* text, string identifier);
	~ScrollerText();

	void Update(float dt);
	void Render();
	void Start();

	bool Is(string type);
	string GetID();
};



#endif /* SCROLLER_H_ */
