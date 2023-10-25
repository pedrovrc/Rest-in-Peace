#include "Sound.h"
#include "Resources.h"

/*
 * Sound(GameObject& associated)
 *
 * Inicializa objeto sem um arquivo de áudio aberto.
 */
Sound::Sound(GameObject& associated) : Component(associated) {
	chunk = nullptr;
	channel = 0;
}

/*
 * Sound(GameObject& associated)
 *
 * Inicializa objeto e abre um arquivo de áudio fornecido.
 */
Sound::Sound(GameObject& associated, string file) : Sound(associated) {
	Open(file);
}

Sound::~Sound() {
	if (IsOpen() == false) return;
	Mix_HaltChannel(channel);
}

/*
 * void Sound::Open(string file)
 *
 * Utiliza a classe Resources para abrir o arquivo de áudio requisitado.
 */
void Sound::Open(string file) {
	chunk = Resources::GetSound(file);
}

/*
 * void Sound::Play(int times)
 *
 * Executa o arquivo de áudio armazenado no Mix_Chunk uma determinada quantidade de vezes.
 */
void Sound::Play(int times) {
	channel = Mix_PlayChannel(-1, chunk, times-1);
}

/*
 * void Sound::Stop()
 *
 * Para a execução do áudio armazenado no Mix_Chunk.
 */
void Sound::Stop() {
	if (IsOpen() == false) return;
	Mix_HaltChannel(channel);
}

bool Sound::IsOpen() {
	if (chunk == nullptr) return false;
	return true;
}

void Sound::Start() {
	Play();
}

void Sound::Update(float dt) {

}

void Sound::Render() {

}

bool Sound::Is(string type) {
	if (type == "Sound") return true;
	return false;
}

int Sound::GetChannel() {
	return channel;
}

void Sound::NotifyCollision(GameObject& other) {

}
