#ifndef TEXT_H
#define TEXT_H

#include "Component.h"
#include "Timer.h"

#define INCLUDE_SDL_TTF
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

class Text : public Component {
public:
	enum TextStyle { SOLID, SHADED, BLENDED };

	Text( GameObject& associated,
		  string fontFile,
		  int fontSize,
		  TextStyle style,
		  string text,
		  SDL_Color color,
		  float blinkTime);
	~Text();

	void Update(float dt);
	void Render();
	bool Is(string type);

	void Start();
	void Pause();
	void Resume();
	void NotifyCollision(GameObject& other);

	void SetText(string text);
	void SetColor(SDL_Color color);
	void SetStyle(TextStyle style);
	void SetFontFile(string fontFile);
	void SetFontSize(int fontSize);

private:
	TTF_Font* font;
	SDL_Texture* texture;

	string text;
	TextStyle style;
	string fontFile;
	int fontSize;
	SDL_Color color;

	Timer blinkTimer;
	float blinkTime;

	bool showText;

	void RemakeTexture();
};

#endif
