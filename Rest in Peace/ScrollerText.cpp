#include "ScrollerText.h"
#include "InputManager.h"

ScrollerText::ScrollerText(GameObject& associated, Text* text, string identifier) : Component(associated) {
	text_ref = text;
	id = identifier;
}

ScrollerText::~ScrollerText() {

}

void ScrollerText::Update(float dt) {
	InputManager* input = &(InputManager::GetInstance());

	// scroll do texto
	if ((input->WheelRoll("down") || input->WheelRoll("up")
		|| input->KeyPress(UP_ARROW_KEY) || input->KeyPress(DOWN_ARROW_KEY))) {	// detecta scroll ou seta

		int y_offset = 0;
		if (input->WheelRoll("down") || input->KeyPress(DOWN_ARROW_KEY)) y_offset = 50;
		if (input->WheelRoll("up") || input->KeyPress(UP_ARROW_KEY)) y_offset = -50;

		text_ref->RollScope(y_offset);
	}
}

void ScrollerText::Render() {

}

void ScrollerText::Start() {

}

bool ScrollerText::Is(string type) {
	if (type == "ScrollerText") return true;
	else return false;
}

string ScrollerText::GetID() {
	return id;
}

void ScrollerText::NotifyCollision(GameObject& other) {

}
