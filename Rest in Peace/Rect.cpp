#include "Rect.h"

/*
 * Rect::Rect()
 *
 * Inicializa objeto com dimensões zero e posição (0,0)
 */
Rect::Rect() {
	x = 0;
	y = 0;
	w = 0;
	h = 0;
	this->angle = 0;
}

/*
 * Rect::Rect(float x, float y, float w, float h)
 *
 * Inicializa objeto com os parâmetros fornecidos.
 */
Rect::Rect(float x, float y, float w, float h, float angle) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->angle = angle;
}

/*
 * Vec2& Rect::GetPos()
 *
 * Retorna objeto Vec2 com coordenadas do retângulo.
 */
Vec2& Rect::GetPos() {
	return *new Vec2(x, y);
}

/*
 * Vec2& Rect::GetCenter()
 *
 * Retorna objeto Vec2 com coordenadas de centro do retângulo.
 */
Vec2& Rect::GetCenter() {
	Vec2* center = new Vec2(x + (w/2), y + (h/2));
	center->RotateThis(angle);
	return *center;
}

/*
 * float Rect::GetCenterDist(Rect box)
 *
 * Retorna a distância entre o centro deste objeto Rect e outro fornecido.
 */
float Rect::GetCenterDist(Rect box) {
	Vec2 center1 = this->GetCenter();
	Vec2 center2 = box.GetCenter();
	return center1.GetDistance(center2);
}

/*
 * Vec2& Rect::GetDimensions()
 *
 * Retorna objeto Vec2 com as dimensões do retângulo (w, h).
 */
Vec2& Rect::GetDimensions() {
	return *new Vec2(w, h);
}

/*
 * void Rect::MoveThis(Vec2 vector)
 *
 * Modifica os valores x e y para transladar o retângulo de acordo com o vetor fornecido.
 */
void Rect::MoveThis(Vec2 vector) {
	x += vector.x;
	y += vector.y;
}

/*
 * void Rect::RotateThis(float angle)
 *
 * Modifica o valor de angle.
 */
void Rect::RotateThis(float angle) {
	this->angle = angle;
}

void Rect::ResizeThis(float ratio) {
	this->w = this->w * ratio;
	this->h = this->h * ratio;
}

/*
 * void Rect::SetCenterPosition(Vec2 vector)
 *
 * Seta posição do retângulo para que centro esteja no ponto fornecido.
 */
void Rect::SetCenterPosition(Vec2 vector) {
	Vec2* offset = new Vec2(w/2, h/2);
	offset->RotateThis(angle);
	SetPosition(vector - *offset);
}

/*
 * void Rect::SetPosition(Vec2 vector)
 *
 * Modifica os valores x e y para colocar o retângulo no ponto fornecido.
 */
void Rect::SetPosition(Vec2 vector) {
	x = vector.x;
	y = vector.y;
}

/*
 * void Rect::SetDimensions(float w, float h)
 *
 * Modifica os valores w e h para os fornecidos.
 */
void Rect::SetDimensions(float w, float h) {
	this->w = w;
	this->h = h;
}

/*
 * void Rect::GetScaledCopy(Vec2 scale, string alignment)
 *
 * Retorna novo objeto Rect com tamanho de acordo com escala fornecida.
 * O objeto estará alinhado com o originário em seu centro por padrão.
 */
Rect& Rect::GetScaledCopy(Vec2 scale) {
	Rect* newBox = new Rect(x, y, w*scale.x, h*scale.y);
	newBox->SetCenterPosition(this->GetCenter());
	return *newBox;
}

/*
 * Rect& Rect::GetTranslatedRect(Vec2 vector)
 *
 * Retorna novo objeto Rect de mesmas dimensões mas transladado por vetor fornecido.
 */
Rect& Rect::GetTranslatedCopy(Vec2 vector) {
	return *new Rect(x + vector.x, y + vector.y, this->w, this->h);
}

/*
 * bool Rect::Contains(Vec2 point)
 *
 * Checa se ponto fornecido está dentro do objeto Rect. Não considera rotações.
 */
bool Rect::Contains(Vec2 point) {
	float limit_lo_x = x;
	float limit_hi_x = x + w;
	float limit_lo_y = y;
	float limit_hi_y = y + h;
	if (point.x < limit_hi_x && point.x > limit_lo_x
		&& point.y < limit_hi_y && point.y > limit_lo_y) {
		return true;
	}
	return false;
}


