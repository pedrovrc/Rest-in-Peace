#include "Deck.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>

Deck::Deck()
{

}

Deck::~Deck()
{
    //dtor
}

GameObject* Deck::DrawOne()
{
    GameObject* go_card = list.back();
    list.pop_back();
    return go_card;
}

GameObject* Deck::DrawThis(int val) {
	GameObject* go_card = list[val];
	list.erase(list.begin()+val);
	return go_card;
}
