#include "Button.h"

Button::Button(GameObject& associated) : Component(associated){

}

void Button::Update(float dt) {

}

void Button::Render() {

}

void Button::Start() {

}

bool Button::Is(string type) {
	if (type == "Button") return true;
	return false;
}

void Button::NotifyCollision(GameObject& other) {

}
