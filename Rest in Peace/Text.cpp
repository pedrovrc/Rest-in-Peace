#include "Text.h"
#include "Resources.h"
#include "Game.h"

Text::Text( GameObject& associated,
		  	string fontFile,
		    int fontSize,
		    TextStyle style,
		    string text,
		    SDL_Color color,
			float blinkTime ) : Component(associated) {

	texture = nullptr;
	this->text = text;
	this->style = style;
	this->fontFile = fontFile;
	this->fontSize = fontSize;
	this->color = color;
	this->font = Resources::GetFont(fontFile, fontSize);

	blinkTimer = Timer();
	this->blinkTime = blinkTime;

	showText = true;

	RemakeTexture();
}

Text::~Text() {
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
	}
}

void Text::Update(float dt) {
	if (blinkTime > 0) {
		blinkTimer.Update(dt);
		if (blinkTimer.Get() > blinkTime) {
			showText = !showText;
			blinkTimer.Restart();
		}
	}
}

void Text::Render() {
	if (texture != nullptr) {
		SDL_Rect dstRect;
		dstRect.x = associated.box.x;
		dstRect.y = associated.box.y;
		dstRect.w = associated.box.w;
		dstRect.h = associated.box.h;

		SDL_Rect clipRect;
		clipRect.x = scope.x;
		clipRect.y = scope.y;
		clipRect.w = scope.w;
		clipRect.h = scope.h;

		Game& game = game.GetInstance();

		if (showText) {
			if (SDL_RenderCopyEx( game.GetRenderer(),
								  texture,
								  &clipRect,
								  &dstRect,
								  associated.angleDeg,
								  nullptr,
								  SDL_FLIP_NONE ) != 0 ) {
				cout << "Erro ao renderizar texto" << endl;
				cout << SDL_GetError() << endl;
				return;
			}
		}
	}
}

void Text::SetScope(int x, int y, int w, int h) {
	scope.x = x;
	scope.y = y;
	scope.w = w;
	scope.h = h;

	int width = GetSurfaceWidth();
	int height = GetSurfaceHeight();

	if (scope.x < 0) scope.x = 0;
	if (scope.x > width) scope.x = width;
	if (scope.y < 0) scope.y = 0;
	if (scope.y > height) scope.y = height;

	RemakeTexture();
}

void Text::RollScope(int y_offset) {
	scope.y += y_offset;
	if (ScopeUpLimit()) scope.y = 0;
	if (ScopeDownLimit()) scope.y = GetSurfaceHeight() - scope.h;
}

bool Text::ScopeUpLimit() {
	if (scope.y <= 0) return true;
	else return false;
}

bool Text::ScopeDownLimit() {
	if (scope.y + scope.h >= GetSurfaceHeight()) return true;
	else return false;
}

int Text::GetSurfaceHeight() {
	return realSize.h;
}

int Text::GetSurfaceWidth() {
	return realSize.w;
}

void Text::Start() {

}

void Text::Pause() {

}

void Text::Resume() {

}

bool Text::Is(string type) {
	if (type == "Text") return true;
	return false;
}

void Text::SetText(string text) {
	this->text = text;
	RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
	this->color = color;
	RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
	this->style = style;
	RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
	this->fontSize = fontSize;
	RemakeTexture();
}

void Text::RemakeTexture() {
	if (texture != nullptr) SDL_DestroyTexture(texture);

	SDL_Surface* surface;

	if (style == SOLID) {
		surface = TTF_RenderText_Solid(font, text.c_str(), color);

	} else if (style == SHADED) {
		SDL_Color bg_color;
		bg_color.r = 0;
		bg_color.g = 0;
		bg_color.b = 0;
		bg_color.a = 255;
		surface = TTF_RenderText_Shaded(font, text.c_str(), color, bg_color);

	} else if (style == BLENDED) {
		surface = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), color, 650);
	}

	Game& game = game.GetInstance();
	texture = SDL_CreateTextureFromSurface(game.GetRenderer(), surface);
	SDL_FreeSurface(surface);

	int w, h;
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
	realSize.w = w;
	realSize.h = h;
}
