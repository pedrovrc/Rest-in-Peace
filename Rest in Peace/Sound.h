#ifndef SOUND_H
#define SOUND_H

#include <bits/stdc++.h>
using namespace std;

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#include "Component.h"

/*
 * Classe Sound
 *
 * Responsável por conter um Mix_Chunk para tocar sons no jogo.
 */
class Sound : public Component{
	Mix_Chunk* chunk;
	int channel;
public:
	Sound(GameObject& associated);
	Sound(GameObject& associated, string file);
	~Sound();
	void Play(int times = 1);
	void Stop();
	void Open(string file);
	bool IsOpen();
	void Update(float dt);
	void Render();
	void Start();
	bool Is(string type);
	int GetChannel();
};

#endif
