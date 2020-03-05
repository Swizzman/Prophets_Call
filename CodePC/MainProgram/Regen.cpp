#include "Regen.h"

Regen::Regen() :Ability("Regen.png", 100,1, 0.2f)
{
	this->health = 10;

}

Regen::~Regen()
{
}

void Regen::abilityActive()
{
	/*if (abilityEffectPulse(0.2f))
	{
		cout << "asdasd" << endl;
		
	}*/
}

int Regen::getSpecificVar()
{
	
		return health;
	
}

void Regen::placeAbility(sf::Vector2f position)
{
	setPosition(position);
}


