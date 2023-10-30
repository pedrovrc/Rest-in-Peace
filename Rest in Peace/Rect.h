#ifndef RECT_H
#define RECT_H

#include <bits/stdc++.h>
#include <tuple>
using namespace std;

#include "Vec2.h"

/*
 * Classe Rect
 *
 * Implementa um retângulo de dimensões w e h, com seu canto esquerdo superior em (x,y).
 */
class Rect {
public:
	float x;
	float y;
	float w;
	float h;
	float angle;

	Rect();
	Rect(float x, float y, float w, float h, float angle = 0);
	Vec2& GetCenter();
	float GetCenterDist(Rect box);
	Vec2& GetPos();
	Vec2& GetDimensions();
	void MoveThis(Vec2 vector);
	void RotateThis(float angle);
	void ResizeThis(float ratio);
	void SetCenterPosition(Vec2 vector);
	void SetPosition(Vec2 point);
	void SetDimensions(float w, float h);
	Rect& GetScaledCopy(Vec2 scale);
	Rect& GetTranslatedCopy(Vec2 vector);
	bool IsInside(Vec2 point);	// nao considera rotacao

	// implementar:
	// - rotacao em um determinado angulo
};
#endif
