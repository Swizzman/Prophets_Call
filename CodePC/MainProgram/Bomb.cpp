#include "Bomb.h"

Bomb::Bomb(bool dummy) : Ability("bomb.png", 80, 0.5f,0, dummy)
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