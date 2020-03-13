
#pragma once
#include "Ability.h"
class Reinforcement :
	public Ability
{
private:
	int damageIncrease;
	bool activateSound;
public:
	Reinforcement(bool dummy);
	virtual ~Reinforcement();

	// Inherited via Ability
	virtual void abilityActive() override;

	virtual int getSpecificVar() override;

	virtual void placeAbility(sf::Vector2f position) override;


	// Inherited via Ability
	virtual bool makeSound() override;


	// Inherited via Ability
	virtual void changeSoundBool(bool soundBool) override;

};