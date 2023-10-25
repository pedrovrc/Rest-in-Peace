#ifndef SPRITE_H
#define SPRITE_H

#include <bits/stdc++.h>
using namespace std;

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

#include "Rect.h"
#include "Component.h"
#include "Timer.h"

/*
 * Classe Sprite
 *
 * Responsável por conter uma SDL_Texture e permitir renderização de imagens.
 */
class Sprite : public Component{
	shared_ptr<SDL_Texture> texture;
	int width;
	int height;
	int frameWidth;
	int frameCount;
	int currentFrame;
	float timeElapsed;
	float frameTime;
	float secondsToSelfDestruct;
	Timer selfDestructCount;
	SDL_Rect clipRect;
	Vec2 scale;
public:
	Sprite( GameObject& associated );
	Sprite(	GameObject& associated,
			string file,
			int frameCount = 1,
			int frameTime = 0,
			float secondsToSelfDestruct = 0 );
	~Sprite();
	void Open(string file);
	void SetClip(int x, int y, int w, int h);
	void SetScale(float scaleX, float scaleY);
	void Render();
	void Render(float x, float y, float w, float h);
	void Start();
	void SetFrame(int frame);
	void SetFrameCount(int frameCount);
	void SetFrameTime(float frameTime);
	int GetWidth();
	int GetHeight();
	Vec2 GetScale();
	bool IsOpen();
	void Update(float dt);
	bool Is(string type);
	void NotifyCollision(GameObject& other);
};

#endif
