#include "State.h"

State::State() {
	popRequested = false;
	quitRequested = false;
	started = false;
}


State::~State() {
	while (objectArray.empty() == false) {
		objectArray.erase(objectArray.end() - 1);
	}
	objectArray.clear();
}


weak_ptr<GameObject> State::AddObject(GameObject* go) {
	shared_ptr<GameObject> pointer(go);
	objectArray.emplace_back(pointer);
	if(started) pointer->Start();
	return weak_ptr<GameObject>(pointer);
}

void State::DeleteObject(GameObject* go) {
	int size = objectArray.size(), i = 0;
	while (i < size) {
		if (go == (GameObject*)objectArray[i].get()) {
			objectArray.erase(objectArray.begin() + i);
			return;
		}
		i++;
	}
}


weak_ptr<GameObject> State::GetObjectPtr(GameObject* go) {
	int i = 0;
	while (objectArray.begin() + i != objectArray.end()) {
		if (objectArray[i].get() == go) return weak_ptr<GameObject>(objectArray[i]);
		i++;
	}
	return weak_ptr<GameObject>();
}


bool State::PopRequested() {
	return popRequested;
}


bool State::QuitRequested() {
	return quitRequested;
}

void State::StartArray() {
	// inicia GameObjects
	int i = 0, size = objectArray.size();
	GameObject* go;
	while (i < size) {
		go = (GameObject*)objectArray[i].get();
		go->Start();
		i++;
	}
}

void State::UpdateArray(float dt) {
	// atualiza GameObjects
	int i = 0, size = objectArray.size();
	GameObject* go;
	while (i < size) {
		go = (GameObject*)objectArray[i].get();
		go->Update(dt);
		i++;
	}
}

void State::RenderArray() {
	// renderiza GameObjects
	int i = 0, size = objectArray.size();
	GameObject* go;
	while (i < size) {
		go = (GameObject*)objectArray[i].get();
		go->Render();
		i++;
	}
}
