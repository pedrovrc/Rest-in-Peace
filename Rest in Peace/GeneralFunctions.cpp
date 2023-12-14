#include "GeneralFunctions.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>

/*
 * 	int RandomInt(int lim_lo, int lim_hi)
 *
 * 	Retorna inteiro aleatório entre um valor mínimo e um máximo.
 */
int RandomInt(int lim_lo, int lim_hi) {
	int random = ((int) rand()) / (int) RAND_MAX;
	int diff = lim_hi - lim_lo;
	int r = random * diff;
	return lim_lo + r;
}

/*
 * 	float RandomFloat(float lim_lo, float lim_hi)
 *
 * 	Retorna float aleatório entre um valor mínimo e um máximo.
 */
float RandomFloat(float lim_lo, float lim_hi) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = lim_hi - lim_lo;
    float r = random * diff;
    return lim_lo + r;
}

/*
 * 	float Deg2Rad (float angleDeg)
 *
 * 	Recebe ângulo em graus e retorna valor desse ângulo em radianos.
 */
float Deg2Rad (float angleDeg) {
	return angleDeg * M_PI/180;
}

/*
 * 	float Rad2Deg (float angleRad)
 *
 * 	Recebe ângulo em radianos e retorna valor desse ângulo em graus.
 */
float Rad2Deg (float angleRad) {
	return angleRad * 180/M_PI;
}

string ReadAllFromFile(string path) {
	ifstream file(path);
	string text;

	if (file) {	// checa arquivo não nulo
		ostringstream stream;
		stream << file.rdbuf();
		text = stream.str();
	}

	return text;
}

Text* CreateAddText(GameObject* associated, string font,
								 int fontSize, string text,
								 int width, int height,
								 SDL_Color color,
								 int blinkTime) {
	string fontpath = "font/" + font;
	Component* newText = new Text(*associated,
									fontpath, fontSize,
									Text::TextStyle::BLENDED,
									text,
									color, blinkTime);
	associated->AddComponent(newText);
	if (width > 0 && width <= ((Text*)newText)->GetSurfaceWidth()) {
		associated->box.w = width;
	} else {
		associated->box.w = ((Text*)newText)->GetSurfaceWidth();
	}
	if (height > 0 && height <= ((Text*)newText)->GetSurfaceHeight()) {
		associated->box.h = height;
	} else {
		associated->box.h = ((Text*)newText)->GetSurfaceHeight();
	}
	((Text*)newText)->SetScope(0, 0, associated->box.w, associated->box.h);

	return (Text*)newText;
}

Button* CreateAddButton(GameObject* associated, string type,
						int width, int height, Vec2 centerpos) {
	Component* newButton = new Button(*associated, type);
	associated->box.SetDimensions(width, height);
	associated->box.SetCenterPosition(centerpos);
	associated->AddComponent(newButton);
	return (Button*)newButton;
}

Button* CreateAddButton(GameObject* associated, string type,
						int width, int height, Vec2 centerpos, string identifier) {
	Component* newButton = new Button(*associated, type, identifier);
	associated->box.SetDimensions(width, height);
	associated->box.SetCenterPosition(centerpos);
	associated->AddComponent(newButton);
	return (Button*)newButton;
}

Sprite* CreateAddSprite(GameObject* associated, string filename,
						int frameCount, int frameTime, Vec2 pos,
						int width, int height) {
	Component* newSprite = new Sprite(*associated, filename, frameCount, frameTime);
	associated->AddComponent(newSprite);
	if (width >= 0 && height >= 0) associated->box.SetDimensions(width, height);
	associated->box.SetPosition(pos);
	return (Sprite*)newSprite;
}

Sprite* CreateAddCenteredSprite(GameObject* associated, string filename,
						int frameCount, int frameTime, Vec2 centerpos,
						int width, int height) {
	Component* newSprite = new Sprite(*associated, filename, frameCount, frameTime);
	associated->AddComponent(newSprite);
	if (width >= 0 && height >= 0) associated->box.SetDimensions(width, height);
	associated->box.SetCenterPosition(centerpos);
	return (Sprite*)newSprite;
}

string GetTimeFromTable(int offset) {
	if (offset > 24) return "";

	ifstream timeTable;
	timeTable.open("text/timeTable.txt", ifstream::in);
	string line;
	for (int i = 0; i <= offset; i++) {
		getline(timeTable, line);
	}
	return line;
}
