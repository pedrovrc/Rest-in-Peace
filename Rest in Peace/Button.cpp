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

	id = "No ID";
}

Button::Button(GameObject& associated, string type, string identifier) : Component(associated){
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

	id = identifier;
}

void Button::Update(float dt) {
	InputManager* input = &(InputManager::GetInstance());
	if (associated.box.Contains(input->GetMousePoint())) {
		isHovered = true;
	} else {
		isHovered = false;
	}
}

void Button::Render() {
	// renderiza overlay caso botao esteja sob o mouse
	if (isHovered) {
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

bool Button::IsHovered() {
	return isHovered;
}

string Button::GetID() {
	return id;
}
