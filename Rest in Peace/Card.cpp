#include "Card.h"
#include "GeneralFunctions.h"
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
    if(regex_search(effect,var,regex("(risada)")))
	{
		this->t = RISADA;
	}
    if(regex_search(effect,var,regex("(espreitar)")))
	{
		this->t = ESPREITAR;
	}
    if(regex_search(effect,var,regex("(devorar)")))
	{
		this->t = DEVORAR;
	}

    // carrega imagem da carta
	string filename = "img/cards/" + name + ".png";
	Component* image = new Sprite(associated, filename, 1, 0);
	associated.AddComponent(image);
	associated.box.SetDimensions(SMALL_CARD_W, SMALL_CARD_H);

	// carrega som da carta
	filename = "audio/cards/" + name + ".mp3";
	Component* sound = new Sound(associated, filename);
	associated.AddComponent(sound);

    // carrega modificadores de custo
    modCostPlus = new GameObject;
    CreateAddSprite(modCostPlus, "img/resources/plusOne.png", 1, 0, *new Vec2(0, 0), -1, -1);

    modCostMinus = new GameObject;
    CreateAddSprite(modCostMinus, "img/resources/minusOne.png", 1, 0, *new Vec2(0, 0), -1, -1);
}

Card::~Card()
{
    //dtor
}

void Card::ModifyCost(int val) {
	if(cost+val > 3) return;
	modCost = val;
}

int Card::GetCost() {
	return cost+modCost;
}

void Card::Update(float dt) {

}

void Card::Render() {
	if (modCost == 1) {
		modCostPlus->box.SetPosition(associated.box.GetPos() + *new Vec2(40, -5));
		modCostPlus->Render();
	} else if (modCost == -1) {
		modCostMinus->box.SetPosition(associated.box.GetPos() + *new Vec2(40, -5));
		modCostMinus->Render();
	}
}

void Card::Start() {

}

bool Card::Is(string type) {
	if (type == "Card") return true;
	else return false;
}
