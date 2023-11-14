#include "Game.h"
#include "Resources.h"

Game* Game::instance;

/*
 * Game::Game(string title, int width, int height)
 *
 * Responsável por iniciar a classe e as diversas partes necessárias da biblioteca SDL.
 */
Game::Game(string title, int width, int height) {
	if (instance != nullptr) {
		cout << "ERRO: Jogo ja esta em execucao" << endl;
		return;
	}
	instance = this;

	int error = 0;
	error = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
	if (error != 0) {
		cout << "Erro na inicializacao do SDL" << endl;
		cout << SDL_GetError() << endl;
		return;
	}

	error = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	if (error != (IMG_INIT_JPG | IMG_INIT_PNG)) {
		cout << "Erro na inicializacao do SDL_Image" << endl;
		cout << SDL_GetError() << endl;
		return;
	}

	error = Mix_Init(MIX_INIT_OGG);
	if (error != MIX_INIT_OGG) {
		cout << "Erro na inicializacao do SDL_Mixer" << endl;
		cout << SDL_GetError() << endl;
		return;
	}

	error = TTF_Init();
	if (error == -1) {
		cout << "Erro na inicializacao do SDL_TTF" << endl;
		cout << SDL_GetError() << endl;
		return;
	}

	error = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	if (error != 0) {
		cout << "Erro na inicializacao do SDL_Mixer (OpenAudio)" << endl;
		cout << SDL_GetError() << endl;
		return;
	}

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	if (window == nullptr) {
		cout << "Erro na inicializacao da janela (SDL_CreateWindow)" << endl;
		cout << SDL_GetError() << endl;
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) {
		cout << "Erro na inicializacao do renderizador (SDL_CreateRenderer)" << endl;
		cout << SDL_GetError() << endl;
		return;
	}
	storedState = nullptr;
	frameStart = 0;
	dt = 0;
	player = Player::GetInstance();
}

Game::~Game() {
	if (storedState != nullptr) free(storedState);

	while (stateStack.empty() == false) {
		stateStack.pop();
	}

	Resources::ClearImages();
	Resources::ClearMusics();
	Resources::ClearSounds();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Mix_CloseAudio();
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

/*
 * Game& Game::GetInstance()
 *
 * Garante o padrão singleton nessa classe.
 */
Game& Game::GetInstance() {
	if (instance == nullptr) {
		instance = new Game(
			GAME_TITLE,
			WINDOW_WIDTH, WINDOW_HEIGHT
			);
	}
		return *instance;
}

/*
 * Game::CalculateDeltaTime()
 *
 * Responsável por consultar a biblioteca SDL e calcular o tempo entre frames (ms).
 */
void Game::CalculateDeltaTime() {
	int oldFrame = frameStart;
	frameStart = SDL_GetTicks();

	dt = 0.001*(frameStart - oldFrame);
}

/*
 * Game::Run()
 *
 * Responsável por executar o main game loop.
 */
void Game::Run() {
	if (storedState == nullptr) {
		cout << "Erro ao carregar estado inicial do jogo" << endl;
		return;
	} else {
		unique_ptr<State> uniqueState (storedState);
		stateStack.push(move(uniqueState));
		stateStack.top().get()->Start();
		storedState = nullptr;
	}

	State* currentState;

	while(stateStack.empty() == false) {
		// checa por quit requisitado por player
		if (stateStack.top().get()->QuitRequested()) break;

		if (stateStack.top().get()->PopRequested()) {
			stateStack.pop();
			if (stateStack.empty() == false) stateStack.top().get()->Resume();
			else break;
		}

		if (storedState != nullptr) {
			stateStack.top().get()->Pause();
			unique_ptr<State> uniqueState (storedState);
			stateStack.push(move(uniqueState));
			stateStack.top().get()->Start();
			storedState = nullptr;
		}

		currentState = stateStack.top().get();

		CalculateDeltaTime();
		InputManager::GetInstance().Update();
		currentState->Update(dt);
		currentState->Render();
		SDL_RenderPresent(renderer);
		SDL_Delay(33);
	}

	Resources::ClearImages();
	Resources::ClearMusics();
	Resources::ClearSounds();
}

void Game::Push(State* state) {
	storedState = state;
}

State& Game::GetCurrentState() {
	return *stateStack.top().get();
}

SDL_Renderer* Game::GetRenderer() {
	return renderer;
}

float Game::GetDeltaTime() {
	return dt;
}
