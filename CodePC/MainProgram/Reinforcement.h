
#pragma once
#include "Ability.h"
class Reinforcement :
	public Ability
{
private:
	int damageIncrease;
public:
	Reinforcement();
	virtual ~Reinforcement();

	// Inherited via Ability
	virtual void abilityActive() override;

	virtual int getSpecificVar() override;

	virtual void placeAbility(sf::Vector2f position) override;

};