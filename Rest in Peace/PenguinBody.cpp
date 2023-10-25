#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "Game.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Collider.h"
#include "Alien.h"
#include "Bullet.h"
#include "Sound.h"

PenguinBody* PenguinBody::player;

PenguinBody::PenguinBody (GameObject& associated) : Component(associated) {
	player = this;
	speed.Set(0, 0);
	linearSpeed = 0;
	angle = 0;
	hp = HP_MAX;
	Sprite* sprbody = new Sprite(associated, "img/penguin.png");
	associated.AddComponent((Component*)sprbody);

	Component* collider = new Collider(associated);
	associated.AddComponent(collider);
}

PenguinBody::~PenguinBody () {
	player = nullptr;
}

/*
 * 	void PenguinBody::Start()
 *
 * 	Cria objeto PenguinCannon.
 */
void PenguinBody::Start() {
	State* state = &Game::GetInstance().GetCurrentState();
	GameObject* cannonGO = new GameObject();
	PenguinCannon* cannon = new PenguinCannon(*cannonGO, state->GetObjectPtr(&associated));
	cannonGO->AddComponent((Component*)cannon);
	pcannon = state->AddObject(cannonGO);
}

/*
 * 	void PenguinBody::Update(float dt)
 *
 * 	- Checa se player está morto;
 * 	- Recebe input de W e S para acelerar ou desacelerar;
 * 	- Recebe input de A e D para mudar direção de movimento;
 * 	- Aplica mudanças em movimento a todo frame.
 */
void PenguinBody::Update(float dt) {
	if (hp <= 0) {
		// condicao de derrota

		associated.RequestDelete();
		pcannon.lock().get()->RequestDelete();
		PlayDeathAnimation();
		return;
	}

	InputManager* input = &InputManager::GetInstance();

	// teclas W ou S -> acelera ou desacelera
	if ((input->KeyPress(W_KEY) || input->IsKeyDown(W_KEY)) && linearSpeed <= VEL_MAX)
		linearSpeed += ACCELERATION;
	if ((input->KeyPress(S_KEY) || input->IsKeyDown(S_KEY)) && linearSpeed >= VEL_MIN)
		linearSpeed -= ACCELERATION;

	// teclas A ou D -> muda angulo
	if (input->KeyPress(A_KEY) || input->IsKeyDown(A_KEY))
		angle -= ANGLE_CHANGE;
	if (input->KeyPress(D_KEY) || input->IsKeyDown(D_KEY))
		angle += ANGLE_CHANGE;

	if (linearSpeed > 0) linearSpeed -= FRICTION;
	if (linearSpeed < 0) linearSpeed += FRICTION;

	speed.Set(linearSpeed, 0);
	speed.RotateThis(angle * M_PI/180);
	associated.box.MoveThis(speed);
	associated.angleDeg = angle;

	if (associated.box.x + associated.box.w >= 1480) associated.box.x = 1480 - associated.box.w;
	else if (associated.box.x < 0) associated.box.x = 0;

	if (associated.box.y + associated.box.h >= 1280) associated.box.y = 1280 - associated.box.h;
	else if (associated.box.y < 0) associated.box.y = 0;
}

void PenguinBody::Render() {

}

bool PenguinBody::Is(string type) {
	if (type == "PenguinBody") return true;
	return false;
}

/*
 * 	void PenguinBody::NotifyCollision(GameObject& other)
 *
 * 	Implementa comportamento em caso de colisão com bala (perde HP);
 */
void PenguinBody::NotifyCollision(GameObject& other) {
	//int old_hp = hp;
	Component* cpt;

	// Colisao com Bullet
	cpt = other.GetComponent("Bullet");
	if (cpt != nullptr) {
		Bullet* bull = (Bullet*) cpt;
		if (bull->targetsPlayer) hp -= bull->GetDamage();
	}

	// Colisao com Minion
//	cpt = other.GetComponent("Minion");
//	if (cpt != nullptr) hp -= MINION_DMG;

	// Colisao com Alien
//	cpt = other.GetComponent("Alien");
//	if (cpt != nullptr) hp -= ALIEN_DMG;

	//if (old_hp != hp) cout << "Penguin HP = " << hp << endl;
}

/*
 * 	void PenguinBody::PlayDeathAnimation()
 *
 * 	Mostra animação de morte do player.
 */
void PenguinBody::PlayDeathAnimation() {
	State* state = &Game::GetInstance().GetCurrentState();
	GameObject* explosionGO = new GameObject();

	Sprite* explosion = new Sprite(*explosionGO, "img/penguindeath.png", 5, 200, 1);
	explosionGO->AddComponent((Component*)explosion);

	explosionGO->box.SetCenterPosition(associated.box.GetCenter());

	Sound* boom = new Sound(*explosionGO, "audio/boom.wav");
	boom->Play(1);
	explosionGO->AddComponent((Component*)boom);

	state->AddObject(explosionGO);
}
