#include "Deck.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>

Deck::Deck()
{

    ifstream decklist;
    //cout << "opening deck..." << endl;
    decklist.open("card_info/deck.txt", ifstream::in);
    if(decklist.is_open())
    {
        cout << "deck opened!" << endl;
        GameObject* go_card;
        while (!(decklist.eof()))
        {
            string effect;
            getline(decklist, effect);

            go_card = new GameObject();
			Component* card = (Component*) new Card(*go_card, effect);
			go_card->AddComponent(card);

            list.emplace_back(go_card);
        }
        decklist.close();
    }
    //else
        //cout << "erro" << endl;
    //cout << "Deck size is: " << list.size() << endl;

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(list.begin(), list.end(), default_random_engine(seed));
}

Deck::~Deck()
{
    //dtor
}

GameObject* Deck::Draw()
{
    cout << "Draw!" << endl;
    GameObject* go_card = list.back();
    list.pop_back();
    return go_card;
}
