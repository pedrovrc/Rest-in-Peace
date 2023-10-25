#include "Vec2.h"

#define THRESHOLD 0.01

/*
 * Vec2::Vec2()
 *
 * Inicializa objeto com valores zero.
 */
Vec2::Vec2() {
	x = 0;
	y = 0;
}

/*
 * Vec2::Vec2(float x, float y)
 *
 * Inicializa objeto com valores fornecidos.
 */
Vec2::Vec2(float x, float y) {
	this->x = x;
	this->y = y;
}

/*
 *	Vec2::Vec2(string unit)
 *
 *	Inicializa vetor unitário X ou Y se a string fornecida for "unitX" ou "unitY".
 *	Inicializa vetor (0,0) caso contrário.
 */
Vec2::Vec2(string unit) {
	if (unit == "unitX") {
		x = 1;
		y = 0;
	} else if (unit == "unitY") {
		x = 0;
		y = 1;
	} else {
		x = 0;
		y = 0;
	}
}

/*
 *	void Vec2::Set(float x, float y)
 *
 *	Muda valores atuais das coordenadas do objeto.
 */
void Vec2::Set(float x, float y) {
	this->x = x;
	this->y = y;
}

/*
 * Vec2& Vec2::Vec2Add(Vec2 vector)
 *
 * Método privado que implementa a soma de vetores.
 * Para uso em outro escopo, utilizar operador public "+".
 */
Vec2& Vec2::Vec2Add(Vec2 vector) const {
	Vec2* vec = new Vec2(x + vector.x, y + vector.y);
	return *vec;
}

/*
 * Vec2& Vec2::Vec2MultiplyScalar(float scalar)
 *
 * Método privado que implementa a multiplicação por escalar.
 * Para uso em outro escopo, utilizar operador public "*".
 */
Vec2& Vec2::Vec2MultiplyScalar(float scalar) const {
	Vec2* vec = new Vec2(scalar * x, scalar * y);
	return *vec;
}

/*
 * Operadores de operações básicas
 */
Vec2& Vec2::operator+(Vec2 b) const {
	return Vec2Add(b);
}

Vec2& Vec2::operator-(Vec2 b) const {
	b = b.Vec2MultiplyScalar(-1);
	return Vec2Add(b);
}

Vec2& Vec2::operator*(float scalar) const {
	return Vec2MultiplyScalar(scalar);
}

Vec2& Vec2::operator/(float scalar) const {
	if (scalar != 0) {
		scalar = 1/scalar;
	}
	return Vec2MultiplyScalar(scalar);
}

Vec2& Vec2::operator+=(Vec2 b) {
	x += b.x;
	y += b.y;
	return *this;
}

Vec2& Vec2::operator-=(Vec2 b) {
	x -= b.x;
	y -= b.y;
	return *this;
}

Vec2& Vec2::operator*=(float scalar) {
	x *= scalar;
	y *= scalar;
	return *this;
}

Vec2& Vec2::operator/=(float scalar) {
	if (scalar != 0) {
		x /= scalar;
		y /= scalar;
		return *this;
	}
	return *new Vec2(0,0);
}

/*
 * float Vec2::GetMagnitude()
 *
 * Retorna magnitude do vetor representado pelo objeto.
 */
float Vec2::GetMagnitude() {
	return sqrt(pow(x,2) + pow(y,2));
}

/*
 * Vec2& Vec2::GetNormalizedVector()
 *
 * Retorna novo objeto Vec2 cujo vetor aponta na mesma direção, porém tem magnitude 1.
 */
Vec2& Vec2::GetNormalizedVector() {
	float magnit = GetMagnitude();
	if (magnit < THRESHOLD) {
		return *new Vec2(0, 0);
	}
	return *new Vec2(x/magnit, y/magnit);
}

/*
 * float Vec2::DotProduct(Vec2 vecB)
 *
 * Retorna o produto interno entre este vetor e vecB.
 */
float Vec2::DotProduct(Vec2 vecB) {
	return ((x * vecB.x) + (y * vecB.y));
}

/*
 * float Vec2::GetDistance(Vec2 point)
 *
 * Retorna distância entre o ponto representado por este objeto e outro ponto fornecido.
 */
float Vec2::GetDistance(Vec2 point) {
	Vec2 negative = *this * (-1);
	float magnitude = (point + negative).GetMagnitude();
	return magnitude;
}

/*
 * Vec2& Vec2::GetRotated(float angle)
 *
 * Retorna novo objeto Vec2 igual a este rotacionado em um ângulo fornecido (radianos).
 */
Vec2& Vec2::GetRotated(float angle) {
	float x = (this->x * cos(angle)) - (this->y * sin(angle));
	float y = (this->y * cos(angle)) + (this->x * sin(angle));
	return *new Vec2(x, y);
}

/*
 * void Vec2::RotateThis(float angle)
 *
 * Rotaciona esta instância em um ângulo fornecido (radianos).
 */
void Vec2::RotateThis(float angle) {
	float x = (this->x * cos(angle)) - (this->y * sin(angle));
	float y = (this->y * cos(angle)) + (this->x * sin(angle));
	this->Set(x,y);
	return;
}

/*
 * float Vec2::GetAngle(Vec2 vector)
 *
 * Retorna o ângulo que o vetor faz com outro vetor (radianos).
 */
float Vec2::GetAngle(Vec2 vector) {
	return atan2((this->y - vector.y), (this->x - vector.x));;
}

/*
 * float Vec2::GetAngle()
 *
 * Retorna o ângulo que o vetor faz com o eixo horizontal (radianos).
 */
float Vec2::GetAngle() {
	Vec2& unitX = *new Vec2("unitX");
	return this->GetAngle(unitX);
}

/*
 * void Vec2::Print()
 *
 * Imprime no terminal as coordenadas (x,y) do vetor instanciado.
 */
void Vec2::Print() {
	cout << "(" << x << "," << y << ")" << endl;
}
