#include "Bomb.h"

Bomb::Bomb() : Ability("bomb.png", 80)
{
	this->damage = 60;

}

Bomb::~Bomb()
{
}



void Bomb::abilityActive()
{
}

int Bomb::getSpecificVar()
{
	return damage;
}

void Bomb::placeAbility(sf::Vector2f position)
{
	setPosition(position);
}