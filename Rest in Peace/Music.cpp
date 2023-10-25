#include "Music.h"
#include "Resources.h"

/*
 * Music::Music()
 *
 * Inicializa objeto sem um arquivo de áudio aberto.
 */
Music::Music() {
	music = nullptr;
}

/*
 * Music::Music(string file)
 *
 * Inicializa objeto e abre um arquivo de áudio fornecido.
 */
Music::Music(string file) {
	music = nullptr;
	Open(file);
}

Music::~Music() {
	Stop();
}

/*
 * void Music::Open(string file)
 *
 * Utiliza a classe Resources para abrir um arquivo de áudio.
 */
void Music::Open(string file) {
	music = Resources::GetMusic(file);
}

/*
 * void Music::Play(int times)
 *
 * Executa o arquivo de áudio armazenado uma quantidade fornecida de vezes.
 */
void Music::Play(int times) {
	if (this->IsOpen() == false) {
		cout << "Erro ao executar audio - Musica nao foi carregada" << endl;
		cout << SDL_GetError() << endl;
		return;
	}
	if (Mix_PlayMusic(music, times) == -1) {
		cout << "Erro ao executar audio" << endl;
		cout << SDL_GetError() << endl;
		return;
	}
}

/*
 * void Music::Stop(int msToStop)
 *
 * Para a execução de áudio com um fade out.
 */
void Music::Stop(int msToStop) {
	if (Mix_FadeOutMusic(msToStop) == 0) {
		cout << "Erro em Fade Out" << endl;
		cout << SDL_GetError() << endl;
		return;
	}
}

bool Music::IsOpen() {
	if (music == nullptr) {
		return false;
	} else {
		return true;
	}
}
