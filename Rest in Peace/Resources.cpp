#include "Resources.h"
#include "Game.h"

unordered_map<string, shared_ptr<SDL_Texture>> Resources::imageTable;
unordered_map<string, Mix_Music*> Resources::musicTable;
unordered_map<string, Mix_Chunk*> Resources::soundTable;
unordered_map<string, TTF_Font*> Resources::fontTable;

/*
 * SDL_Texture* Resources::GetImage(string file)
 *
 * Retorna uma referência para a SDL_Texture com a imagem requisitada.
 */
shared_ptr<SDL_Texture> Resources::GetImage(string file) {
	auto it = imageTable.find(file);

	// se encontrar imagem na tabela
	if (it != imageTable.end()) {
		return it->second;
	} else {
		Game& game = game.GetInstance();
		SDL_Texture* reference = IMG_LoadTexture(game.GetRenderer(), file.c_str());
		if (reference == nullptr) {
			cout << "Erro 1 ao abrir imagem" << endl;
			cout << SDL_GetError() << endl;
			return nullptr;
		}

		shared_ptr<SDL_Texture> shared_reference (reference, [](SDL_Texture* tex){SDL_DestroyTexture(tex);});
		imageTable.emplace(file, shared_reference);
		return shared_reference;
	}
}

/*
 * Mix_Music* Resources::GetMusic(string file)
 *
 * Retorna uma referência para a Mix_Music com o áudio requisitado.
 */
Mix_Music* Resources::GetMusic(string file) {
	auto it = musicTable.find(file);
	if (it != musicTable.end()) {
		return it->second;
	} else {
		Mix_Music* reference = Mix_LoadMUS(file.c_str());
		if (reference == nullptr) {
			cout << "Erro ao carregar musica" << endl;
			cout << SDL_GetError() << endl;
			return nullptr;
		}
		musicTable.emplace(file, reference);
		return reference;
	}
}

/*
 * Mix_Chunk* Resources::GetSound(string file)
 *
 * Retorna uma referência para o Mix_Chunk com o áudio requisitado.
 */
Mix_Chunk* Resources::GetSound(string file) {
	auto it = soundTable.find(file);
	if (it != soundTable.end()) {
		return it->second;
	} else {
		Mix_Chunk* reference = Mix_LoadWAV(file.c_str());
		if (reference == nullptr) {
			cout << "Erro ao carregar musica" << endl;
			cout << SDL_GetError() << endl;
			return nullptr;
		}
		soundTable.emplace(file, reference);
		return reference;
	}
}

TTF_Font* Resources::GetFont(string file, int size) {
	string file_num = file + to_string(size);
	auto it = fontTable.find(file_num);
	if (it != fontTable.end()) {
		return it->second;
	} else {
		TTF_Font* reference = TTF_OpenFont(file.c_str(), size);
		if (reference == nullptr) {
			cout << "Erro ao carregar fonte" << endl;
			cout << SDL_GetError() << endl;
			return nullptr;
		}
		fontTable.emplace(file_num, reference);
		return reference;
	}
}

/*
 * void Resources::ClearImages()
 *
 * Libera tabela de imagens.
 */
void Resources::ClearImages() {
	SDL_Texture* pointer;
	for (auto& it : imageTable) {
		if (it.second.unique()) {
			pointer = it.second.get();
			SDL_DestroyTexture(pointer);
		}
	}
	imageTable.clear();
}

/*
 * void Resources::ClearMusics()
 *
 * Libera tabela de músicas.
 */
void Resources::ClearMusics() {
	Mix_Music* pointer;
	for (auto& it : musicTable) {
		pointer = it.second;
		Mix_FreeMusic(pointer);
	}
	musicTable.clear();
}

/*
 * void Resources::ClearSounds()
 *
 * Libera tabela de sons.
 */
void Resources::ClearSounds() {
	Mix_Chunk* pointer;
	for (auto& it : soundTable) {
		pointer = it.second;
		Mix_FreeChunk(pointer);
	}
	soundTable.clear();
}

void Resources::ClearFonts() {
	TTF_Font* pointer;
	for (auto& it : fontTable) {
		pointer = it.second;
		TTF_CloseFont(pointer);
	}
	fontTable.clear();
}
