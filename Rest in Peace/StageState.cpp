#include "StageState.h"
#include "Vec2.h"
#include "Collision.cpp"
#include "GeneralFunctions.h"
#include "Collider.h"
#include "Sprite.h"
#include "EndState.h"
#include "Game.h"

StageState::StageState() {
	quitRequested = false;
	started = false;
}

StageState::~StageState() {
	while (objectArray.empty() == false) {
		objectArray.erase(objectArray.end() - 1);
	}
	objectArray.clear();
}

/*
 * StageState::LoadAssets()
 *
 * Responsável por carregar os assets iniciais de StageState.
 */
void StageState::LoadAssets() {
	// cria GO ambient, atribui ele a Sprite do BG e ao CameraFollower
	GameObject* ambient = new GameObject;
	Component* bg = new Sprite(*ambient, "img/ocean.jpg", 1, 0);
	ambient->AddComponent(bg);
	ambient->box.MoveThis(*new Vec2(0,0));
	AddObject(ambient);

	// abre musica
	backgroundMusic.Open("audio/stageState.ogg");

	// Adiciona Alien
	//AddAlien(*new Vec2(512,300));
	//AddAlien(*new Vec2(900,50));
//	AddAlien(*new Vec2(512,800));
//	AddAlien(*new Vec2(700,1000));

	// Adiciona Pinguim
//	AddPlayer(*new Vec2(704,640));

}

/*
 * 	void StageState::Start()
 *
 *
 */
void StageState::Start() {
	// carrega assets
	LoadAssets();

	// Chama start de todos os GOs existentes
	StartArray();

	// procura GO do player
	int i = 0;
	GameObject* go;
	Component* cpt = nullptr;
	GameObject* penguin = nullptr;
	while (objectArray.begin() + i != objectArray.end()) {
		go = (GameObject*)objectArray[i].get();
		cpt = go->GetComponent("PenguinBody");
		if (cpt != nullptr) {
			penguin = go;
			break;
		}
		i++;
	}

	// faz camera seguir player caso encontre-o
	if (penguin != nullptr) {
	//	Camera::Follow(penguin);
	} else {
		cout << "Erro ao encontrar GameObject do Player" << endl;
	}

	// toca musica do estagio (descomentar quando quiser)
	backgroundMusic.Play();
	started = true;
}

/*
 * void StageState::Update(float dt)
 *
 * Chamado em todo frame, é responsável por atualizar todos os GameObjects gerenciados ou excluir objetos mortos.
 * Também é responsável por incluir face (inimigo) ao pressionar espaço.
 * Também cuida de atualizar o Input e a Câmera.
 */
void StageState::Update(float dt) {
	// atualiza input/quit
	InputManager* input = &(InputManager::GetInstance());
	quitRequested = input->QuitRequested();

	int size = objectArray.size(), i = 0;
	GameObject* go;
	Component* cpt = nullptr;
	GameObject* penguin = nullptr;
	// MUDAR
	// USAR GETPLAYERGO
	while (objectArray.begin() + i != objectArray.end()) {
		go = (GameObject*)objectArray[i].get();
		cpt = go->GetComponent("PenguinBody");
		if (cpt != nullptr) {
			penguin = go;
			break;
		}
		i++;
	}

	// atualiza camera
	if (input->KeyPress(Y_KEY)) {
		//if (Camera::following) Camera::Unfollow();
		//else Camera::Follow(penguin);
	}

	//Camera::Update(dt);

	// atualiza GameObjects
	UpdateArray(dt);

	// deteccao de colisao
	int j;
	cpt = nullptr;
	Component* cpt2 = nullptr;
	GameObject* go2;
	Collider* coll1;
	Collider* coll2;
	i = 0;

	// para cada GO com componente collider
	while (i < size) {
		go = (GameObject*)objectArray[i].get();
		cpt = go->GetComponent("Collider");
		if (cpt != nullptr) {
			j = i+1;

			// procura todos os outros GOs seguintes na lista com collider
			while (j < size) {
				go2 = (GameObject*)objectArray[j].get();
				cpt2 = go2->GetComponent("Collider");

				// checa se ambos estão colidindo, se estiverem, notifica-os
				if (cpt2 != nullptr && cpt2 != cpt) {
					coll1 = (Collider*)cpt;
					coll2 = (Collider*)cpt2;
					if (Collision::IsColliding(coll1->box, coll2->box, Deg2Rad(go->angleDeg), Deg2Rad(go2->angleDeg))) {
						go->NotifyCollision(*go2);
						go2->NotifyCollision(*go);
					}
				}
				cpt2 = nullptr;
				j++;
			}
		}
		cpt = nullptr;
		i++;
	}

	// deleta GameObjects mortos
	i = 0;
	while (i < size) {
		go = (GameObject*)objectArray[i].get();
		if (go->IsDead()) {
			//if (go->GetComponent("PenguinBody") != nullptr) Camera::Unfollow();
			DeleteObject(go);
			size--;
		}
		i++;
	}

	// condicao de vitoria/derrota
	bool enemiesDead = true;
	i = 0;
	while (objectArray.begin() + i != objectArray.end()) {
		go = (GameObject*)objectArray[i].get();
		cpt = go->GetComponent("Alien");
		if (cpt != nullptr) {
			enemiesDead = false;
			break;
		}
		i++;
	}

	if (penguin->IsDead()) {
		// derrota
		Game::GetInstance().gameData.playerVictory = false;
		popRequested = true;
		State* newState = (State*) new EndState();
		Game::GetInstance().Push(newState);
	}
	if (enemiesDead) {
		// vitoria
		Game::GetInstance().gameData.playerVictory = true;
		popRequested = true;
		State* newState = (State*) new EndState();
		Game::GetInstance().Push(newState);
	}
}

/*
 * void StageState::Render()
 *
 * Responsável por renderizar todos os GameObjects gerenciados.
 */
void StageState::Render() {
	RenderArray();

	// chamada extra de TileMap->Render para renderizar camadas acima
	int i = 0;
	GameObject* go;
	while (objectArray.begin() + i != objectArray.end()) {
		go = (GameObject*)objectArray[i].get();
		if (go->GetComponent("TileMap") != nullptr) {
			go->Render();
		}
		i++;
	}
}

void StageState::Pause() {

}

void StageState::Resume() {

}