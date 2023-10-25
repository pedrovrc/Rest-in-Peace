#ifndef VEC2_H
#define VEC2_H

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;

/*
 * Classe Vec2
 *
 * Implementa um ponto em R2 ou um vetor no mesmo espaço.
 */
class Vec2 {
	Vec2& Vec2Add(Vec2 vector) const;
	Vec2& Vec2MultiplyScalar(float scalar) const;
public:
	float x;
	float y;

	Vec2();
	Vec2(float x, float y);
	Vec2(string unit);
	void Set(float x, float y);
	float GetMagnitude();
	Vec2& GetNormalizedVector();
	float DotProduct(Vec2 vecB);
	float GetDistance(Vec2 point);
	Vec2& GetRotated(float angle);
	void RotateThis(float angle);
	float GetAngle(Vec2 vector);
	float GetAngle();
	void Print();

	Vec2& operator+(Vec2 b) const;
	Vec2& operator-(Vec2 b) const;
	Vec2& operator*(float scalar) const;
	Vec2& operator/(float scalar) const;
	Vec2& operator+=(Vec2 b);
	Vec2& operator-=(Vec2 b);
	Vec2& operator*=(float scalar);
	Vec2& operator/=(float scalar);

	// implementar:
	// - obter inclinacao de um vetor
	// - obter inclinacao da reta dada por dois pontos
};

#endif
