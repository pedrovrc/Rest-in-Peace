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
    //cout << "Draw!" << endl;
    GameObject* go_card = list.back();
    list.pop_back();
    return go_card;
}
