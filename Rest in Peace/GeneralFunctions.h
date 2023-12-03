#ifndef GENERALFUNCTIONS_H
#define GENERALFUNCTIONS_H

#include <string>
#include "GameObject.h"
#include "Text.h"
#include "Button.h"

int RandomInt(int lim_lo, int lim_hi);
float RandomFloat(float lim_lo, float lim_hi);
float Deg2Rad (float angleDeg);
float Rad2Deg (float angleRad);
string ReadAllFromFile(string path);
Button* CreateAddButton(GameObject* associated, string type,
						int width, int height, Vec2 centerpos);
Button* CreateAddButton(GameObject* associated, string type,
						int width, int height, Vec2 centerpos,
						string identifier);
Text* CreateAddText(GameObject* associated, string font,
					 int fontSize, string text,
					 int width, int height,
					 SDL_Color color,
					 int blinkTime);
Sprite* CreateAddSprite(GameObject* associated, string filename,
						int frameCount, int frameTime, Vec2 pos,
						int width, int height);
Sprite* CreateAddCenteredSprite(GameObject* associated, string filename,
						int frameCount, int frameTime, Vec2 centerpos,
						int width, int height);

#endif
