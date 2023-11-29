#ifndef SCROLLER_H
#define SCROLLER_H

#include "Component.h"
#include "Text.h"

class ScrollerText : public Component {
	Text* text_ref;
	string id;
public:
	ScrollerText(GameObject& associated, Text* text, string identifier);
	~ScrollerText();

	void Update(float dt);
	void Render();
	void Start();

	bool Is(string type);
	string GetID();
	void NotifyCollision(GameObject& other);
};



#endif /* SCROLLER_H_ */
