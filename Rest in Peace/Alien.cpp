#include "Alien.h"
#include "Sprite.h"
#include "Camera.h"
#include "Game.h"
#include "GeneralFunctions.h"
#include "Collider.h"
#include "Bullet.h"
#include "Sound.h"

int Alien::alienCount;

Alien::Alien(GameObject& associated, int nMinions, int currentCount, float timeOffset) : Component(associated) {
	speed.Set(0,0);
	destination.Set(0,0);
	hp = MAX_HP;
	state = RESTING;
	Alien::alienCount = currentCount + 1;
	this->timeOffset = timeOffset;

	Component* img = new Sprite(associated, "img/alien.png", 1, 0);
	associated.AddComponent(img);

	Component* collider = new Collider(associated);
	associated.AddComponent(collider);
}

Alien::~Alien() {

}

/*
 * void Alien::Start()
 *
 * Popula o vetor de minions.
 */
void Alien::Start() {
	State& state = Game::GetInstance().GetCurrentState();

	// cria minions
	for(int i = 0; i < MINION_COUNT; i++) {
		GameObject* minionGO = new GameObject;
		Component* minion = new Minion( *minionGO,
										state.GetObjectPtr(&associated),
										(i*(360/MINION_COUNT)),
										RandomFloat(MIN_SIZE, MAX_SIZE) );
		minionGO->AddComponent(minion);
		minionArray.emplace_back(state.AddObject(minionGO));
	}
}

/*
 * void Alien::Update(float dt)
 *
 * - Checa se alien ainda está vivo;
 * - Rotaciona sprite do alien;
 * - Impede ações caso player esteja morto;
 * - Implementa ações do alien como inimigo do player.
 */
void Alien::Update(float dt) {
	// checar se esta vivo
	if (hp <= 0) {
		Alien::alienCount--;
		if (alienCount == 0) {
			// condicao de vitoria
		}

		associated.RequestDelete();
		int i = 0;
		while (i < (int)minionArray.size()) {
			minionArray[i].lock().get()->RequestDelete();
			i++;
		}
		PlayDeathAnimation();
		return;
	}

	// rotacionar sprite
	associated.angleDeg -= ROTATION_SPEED;
	if (associated.angleDeg < 0) associated.angleDeg -= 360;

	// se player estiver morto, nao faz nada
	if (Game::GetInstance().GetCurrentState().GetPlayerGO().expired() == false) {
		if (Game::GetInstance().GetCurrentState().GetPlayerGO().lock().get()->IsDead()) return;
	} else {
		return;
	}

	// comportamentos
	if (state == RESTING) {
		// atualiza timer de descanso
		restTimer.Update(dt);

		// se timer excedeu o cooldown
		if (restTimer.Get() > REST_COOLDOWN + timeOffset) {
			// obtem proximo destino
			destination = Game::GetInstance().GetCurrentState().GetPlayerGO().lock().get()->box.GetCenter();
			// muda estado para movendo
			state = MOVING;
		}
	} else if (state == MOVING) {
			// se destino estiver longe, move-se na direcao dele
		if (destination.GetDistance(associated.box.GetCenter()) >= MAX_SPEED) {
			Vec2 direction = destination - associated.box.GetCenter();
			speed = direction.GetNormalizedVector() * MAX_SPEED;
			associated.box.MoveThis(speed);
		} else {
			// se destino estiver dentro do alcance do movimento de um unico frame, assume a posicao
			Vec2 offset;
			offset.Set(associated.box.w/2, associated.box.h/2);
			associated.box.SetPosition(destination - offset);
			speed.Set(0,0);

			// obtem posicao atual do player
			Vec2 playerPos = Game::GetInstance().GetCurrentState().GetPlayerGO().lock().get()->box.GetCenter();

			// atira em direcao ao player
			Minion* minion = GetClosestMinion(playerPos);
			minion->Shoot(playerPos);

			// modifica estado para descanso
			state = RESTING;
		}
	} else {
		cout << "Erro em Alien::state" << endl;
	}
}

void Alien::Render() {

}

bool Alien::Is(string type) {
	if (type == "Alien") return true;
	return false;
}

/*
 * 	void Alien::NotifyCollision(GameObject& other)
 *
 * 	Recebe notificações de colisão com objetos;
 * 	Implementa comportamento (perda de HP) na colisão com objeto Bullet.
 */
void Alien::NotifyCollision(GameObject& other) {
	Component* cpt;

	// Colisao com Bullet
	cpt = other.GetComponent("Bullet");
	if (cpt != nullptr) {
		Bullet* bull = (Bullet*) cpt;
		if (bull->targetsPlayer == false) hp -= bull->GetDamage();
		//cout << "Alien HP = " << hp << endl;
	}
}

/*
 *	Minion* Alien::GetClosestMinion(Vec2 target)
 *
 *	Retorna ponteiro para o minion mais próximo ao ponto fornecido.
 */
Minion* Alien::GetClosestMinion(Vec2 target) {
	float smallest_dist;
	int closest;
	GameObject* minionGO;
	for (int i = 0; i < MINION_COUNT; i++) {
		minionGO = minionArray[i].lock().get();
		if (i == 0 || minionGO->box.GetCenter().GetDistance(target) < smallest_dist) {
			closest = i;
			smallest_dist = minionGO->box.GetCenter().GetDistance(target);
		}
	}
	minionGO = minionArray[closest].lock().get();
	return (Minion*)minionGO->GetComponent("Minion");
}

/*
 * 	void Alien::PlayDeathAnimation()
 *
 * 	Executa animação de morte do alien.
 */
void Alien::PlayDeathAnimation() {
	State* state = &Game::GetInstance().GetCurrentState();
	GameObject* explosionGO = new GameObject();

	Sprite* explosion = new Sprite(*explosionGO, "img/aliendeath.png", 4, 250, 1);
	explosionGO->AddComponent((Component*)explosion);

	explosionGO->box.SetCenterPosition(associated.box.GetCenter());

	Sound* boom = new Sound(*explosionGO, "audio/boom.wav");
	boom->Play(1);
	explosionGO->AddComponent((Component*)boom);

	state->AddObject(explosionGO);
}
