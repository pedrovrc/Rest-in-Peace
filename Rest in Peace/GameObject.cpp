#include "GameObject.h"

GameObject::GameObject() {
	isDead = false;
	started = false;
	angleDeg = 0;
}

GameObject::~GameObject() {
	while (components.empty() == false) {
		components.erase(components.end() - 1);
	}
	components.clear();
}

/*
 * void GameObject::Update(float dt)
 *
 * Responsável por atualizar todos os componentes contidos neste objeto.
 */
void GameObject::Update(float dt) {
	int i = 0;
	Component* cpt;
	while (components.begin() + i != components.end()) {
		cpt = (Component*) components[i].get();
		cpt->Update(dt);
		i++;
	}
}

/*
 * void GameObject::Render()
 *
 * Responsável por renderizar todos os componentes contidos neste objeto.
 */
void GameObject::Render() {
	int i = 0;
	Component* cpt;
	while (components.begin() + i != components.end()) {
		cpt = (Component*) components[i].get();
		cpt->Render();
		i++;
	}
}

/*
 * void GameObject::AddComponent(Component* cpt)
 *
 * Adiciona objeto Component na lista de componentes.
 */
void GameObject::AddComponent(Component* cpt) {
	if (started) cpt->Start();
	unique_ptr<Component> cpt_ptr(cpt);
	components.push_back(move(cpt_ptr));
}

/*
 * void GameObject::RemoveComponent(Component* cpt)
 *
 * Remove objeto Component na lista de componentes.
 */
void GameObject::RemoveComponent(Component* cpt) {
	int size = components.size(), i = 0;
	while (i < size) {
		if (cpt == (Component*) components[i].get()) {
			components.erase(components.begin() + i);
			return;
		}
		i++;
	}
}

/*
 * Component* GameObject::GetComponent(string type)
 *
 * Retorna referência para componente contido neste objeto. Caso não encontre, retorna nullptr.
 */
Component* GameObject::GetComponent(string type) {
	int size = components.size(), i = 0;
	Component* cpt;
	while (i < size) {
		cpt = (Component*) components[i].get();
		if (cpt->Is(type)) {
			return cpt;
		}
		i++;
	}
	return nullptr;
}

/*
 * 	void GameObject::Start()
 *
 * 	Chama o método start de todos os componentes desse GO.
 */
void GameObject::Start() {
	int i = 0;
	Component* cpt;
	while (components.begin() + i != components.end()) {
		cpt = (Component*) components[i].get();
		cpt->Start();
		i++;
	}
	started = true;
}

bool GameObject::IsDead() {
	return isDead;
}

void GameObject::RequestDelete() {
	isDead = true;
}
