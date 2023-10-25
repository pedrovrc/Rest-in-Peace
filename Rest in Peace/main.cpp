#include "Game.h"
#include "TitleState.h"

/*
 * 	main()
 * 	Função principal, responsável por dar início à execução do jogo.
 */
int main(int argc, char** argv) {
	Game& game = game.GetInstance();
	State* state = (State*) new TitleState();
	game.Push(state);
	game.Run();
	return 0;
}
