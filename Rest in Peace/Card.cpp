#include "Card.h"
#include <regex>
#include <iostream>

Card::Card(GameObject& associated, string str) : Component(associated)
{
    //ctor
    smatch var;
    name = regex_replace(str, regex("\\{.*\\}|\\<.*\\>|\\[|\\]"), "$2");

    flavor = regex_replace(str, regex("\\[.*\\]|\\<.*\\>|\\{|\\}"), "$2");

    string effect;
    effect = regex_replace(str, regex("\\[.*\\]|\\{.*\\}|\\<|\\>"), "$2");

    //cout << "effect:" << effect << endl;
    smatch sm;
    regex_search(effect, sm, regex("(\\d+)"));

    cost = stoi(sm[0]);
    regex_search(effect, sm, regex("(\\d+)$"));

    quantity = stoi(sm[0]);
    if(regex_search(effect,var,regex("(damage)")))
    {
        this->t = DAMAGE;
    }
    if(regex_search(effect,var,regex("(heal)")))
    {
        this->t = HEALING;
    }
    if(regex_search(effect,var,regex("(armor)")))
    {
        this->t = ARMOR;
    }
    //cout << name << '\t' << flavor << '\t' << cost << '\t' << t << '\t' << quantity << endl;
}

Card::~Card()
{
    //dtor
}

void Card::Update(float dt) {

}

void Card::Render() {

}

void Card::Start() {

}

bool Card::Is(string type) {
	if (type == "Card") return true;
	else return false;
}

void Card::NotifyCollision(GameObject& other) {

}
