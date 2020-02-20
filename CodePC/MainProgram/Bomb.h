#pragma once
#include "Ability.h"
class Bomb :
	public Ability
{
private:
	int damage;
public:
	Bomb();
	virtual ~Bomb();
	// Inherited via Ability
	virtual void abilityActive() override;
	virtual int getSpecificVar() override;
	virtual void placeAbility(sf::Vector2f position) override;
};

