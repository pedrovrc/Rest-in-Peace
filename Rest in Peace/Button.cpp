#include "Button.h"
#include "InputManager.h"

Button::Button(GameObject& associated, string type) : Component(associated){
	isHovered = false;

	// seleciona sprite correto para o tipo
	if (type == "main menu") {
		overlay = new Sprite(associated, "img/resources/selection overlay main menu.png", 1, 0);
	}
	if (type == "card") {
		// carregar overlay de selecao de carta
		overlay = new Sprite(associated, "img/resources/selection overlay card.png", 1, 0);
	}
	overlaybox.SetDimensions(overlay->GetWidth(), overlay->GetHeight());
}

void Button::Update(float dt) {
	InputManager* input = &(InputManager::GetInstance());
	cout << "box.x.y = " << associated.box.x << " " << associated.box.y << endl;
	cout << "box.w.h = " << associated.box.w << " " << associated.box.h << endl;
	if (associated.box.Contains(input->GetMousePoint())) {
		isHovered = true;
	} else {
		isHovered = false;
	}
}

void Button::Render() {
	if (isHovered) {
		cout << "overlay render:" << endl;
		cout << "x = " << overlaybox.x << endl;
		cout << "y = " << overlaybox.y << endl;
		cout << "w = " << overlaybox.w << endl;
		cout << "h = " << overlaybox.h << endl << endl;
		overlaybox.SetCenterPosition(associated.box.GetCenter());
		overlay->Render(overlaybox.x, overlaybox.y, overlaybox.w, overlaybox.h);
	}
}

void Button::Start() {

}

bool Button::Is(string type) {
	if (type == "Button") return true;
	return false;
}

void Button::NotifyCollision(GameObject& other) {

}

bool Button::IsHovered() {
	return isHovered;
}
