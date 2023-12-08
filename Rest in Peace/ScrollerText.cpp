#include "ScrollerText.h"
#include "InputManager.h"
#include "GeneralFunctions.h"


ScrollerText::ScrollerText(GameObject& associated, Text* text, string identifier) : Component(associated) {
	text_ref = text;
	id = identifier;

	upArrow = new GameObject;
	upArrowPos = associated.box.GetPos() + (*new Vec2(associated.box.w - 30, 30));
	CreateAddCenteredSprite(upArrow, "img/resources/up arrow.png", 1, 0, upArrowPos, 20, 20);
	upArrowMovement = UP;

	downArrow = new GameObject;
	downArrowPos = associated.box.GetPos() + (*new Vec2(associated.box.w - 30, associated.box.h - 30));
	CreateAddCenteredSprite(downArrow, "img/resources/down arrow.png", 1, 0, downArrowPos, 20, 20);
	downArrowMovement = DOWN;

	canGoUp = false;
	canGoDown = false;
}

ScrollerText::~ScrollerText() {

}

void ScrollerText::Update(float dt) {
	InputManager* input = &(InputManager::GetInstance());

	// scroll do texto
	if ((input->IsKeyDown(UP_ARROW_KEY) || input->IsKeyDown(DOWN_ARROW_KEY))) {	// detecta seta

		int y_offset = 0;
		if (input->IsKeyDown(DOWN_ARROW_KEY)) y_offset = 20;
		if (input->IsKeyDown(UP_ARROW_KEY)) y_offset = -20;

		text_ref->RollScope(y_offset);
	}

	// presença e animação da seta para cima
	if (text_ref->ScopeUpLimit()) canGoUp = false;
	else {
		if (canGoUp == false) {		// detecta momento da mudança
			canGoUp = true;
			upArrow->box.SetPosition(upArrowPos);	// reseta posição
		} else {
			AnimateArrow("upArrow");
		}

	}

	// presença e animação da seta para baixo
	if (text_ref->ScopeDownLimit()) canGoDown = false;
	else {
		if (canGoDown == false) {		// detecta momento da mudança
			canGoDown = true;
			downArrow->box.SetPosition(downArrowPos);	// reseta posição
		} else {
			AnimateArrow("downArrow");
		}
	}
}

void ScrollerText::AnimateArrow(string type) {
	if (type == "upArrow") {
		if (upArrowMovement == UP && (upArrow->box.GetPos() - upArrowPos).GetMagnitude() < 15) {
			// subindo, ainda nao chegou ao limite
			upArrow->box.MoveThis(*new Vec2(0, -1));	// translada para cima
		} else if (upArrowMovement == UP && (upArrow->box.GetPos() - upArrowPos).GetMagnitude() >= 15) {
			// subindo, chegou ao limite
			upArrowMovement = DOWN;		// muda direção
		} else if (upArrowMovement == DOWN && (upArrow->box.GetPos() - upArrowPos).GetMagnitude() > 0) {
			// descendo, não chegou ao limite
			upArrow->box.MoveThis(*new Vec2(0, 1));		// translada para baixo
		} else if (upArrowMovement == DOWN && (upArrow->box.GetPos() - upArrowPos).GetMagnitude() <= 0) {
			// descendo, chegou ao limite
			upArrowMovement = UP;		// muda direção
		}
	} else if (type == "downArrow") {
		if (downArrowMovement == UP && (downArrowPos - downArrow->box.GetPos()).GetMagnitude() < 15) {
			// subindo, ainda nao chegou ao limite
			downArrow->box.MoveThis(*new Vec2(0, -1));	// translada para cima
		} else if (downArrowMovement == UP && (downArrowPos - downArrow->box.GetPos()).GetMagnitude() >= 15) {
			// subindo, chegou ao limite
			downArrowMovement = DOWN;		// muda direção
		} else if (downArrowMovement == DOWN && (downArrowPos - downArrow->box.GetPos()).GetMagnitude() > 0) {
			// descendo, não chegou ao limite
			downArrow->box.MoveThis(*new Vec2(0, 1));		// translada para baixo
		} else if (downArrowMovement == DOWN && (downArrowPos - downArrow->box.GetPos()).GetMagnitude() <= 0) {
			// descendo, chegou ao limite
			downArrowMovement = UP;		// muda direção
		}
	}
}

void ScrollerText::Render() {
	if (canGoUp) upArrow->Render();
	if (canGoDown) downArrow->Render();
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
