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

    smatch sm;

    regex_search(effect, sm, regex("(\\d) (\\d) (\\w+) (\\d)"));
    cost = stoi(sm[1]);

    sanityCost = stoi(sm[2]);

    quantity = stoi(sm[4]);


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
    if(regex_search(effect,var,regex("(sanity)")))
	{
		this->t = SANITY;
	}
    if(regex_search(effect,var,regex("(congelado)")))
	{
		this->t = CONGELADO;
	}
    if(regex_search(effect,var,regex("(lagrimas)")))
	{
		this->t = LAGRIMAS;
	}
    if(regex_search(effect,var,regex("(truque)")))
	{
		this->t = TRUQUE;
	}
    if(regex_search(effect,var,regex("(diabrura)")))
	{
		this->t = DIABRURA;
	}

    // carrega imagem da carta
    string filename = "img/cards/" + name + ".png";
    Component* image = new Sprite(associated, filename, 1, 0);
    associated.AddComponent(image);
    associated.box.SetDimensions(SMALL_CARD_W, SMALL_CARD_H);
}

Card::~Card()
{
    //dtor
}

void Card::ModifyCost(int val) {
	modCost = val;
}

int Card::GetCost() {
	return cost+modCost;
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
