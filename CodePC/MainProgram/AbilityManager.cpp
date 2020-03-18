
#include "AbilityManager.h"

#include "Prophet.h"



AbilityManager::AbilityManager()
{
	this->currentAbility = nullptr;
	this->enemyProphet = nullptr;
	this->followerGroup = nullptr;
	this->chosenAbility = 0;
	this->abilityActive = false;
	reinforcementIsOn = false;
	this->makeASoundBool = false;
	this->soundCounter = 0;
	this->cost = 0;
	this->hasPlacedAbility = false;
	thisProphet = nullptr;
}

AbilityManager::~AbilityManager()
{
	if (abilityActive)
	{
		delete currentAbility;
	}

}

int AbilityManager::switchAbility()
{
	chosenAbility++;
	if (chosenAbility > 2)
	{
		chosenAbility = 0;
	}


	return chosenAbility;

}

int AbilityManager::getCurrentAbility()
{
	return chosenAbility;
}

int AbilityManager::getCurrentRadius()
{
	return currentAbility->getRadius();
}

bool AbilityManager::getAbilityActive() const
{
	return abilityActive;
}

void AbilityManager::startAbility()
{
	abilityActive = true;

}

void AbilityManager::stopAbility()
{

	
	abilityActive = currentAbility->abilityLifeTime();

	if (abilityActive == false)
	{

		currentAbility->resetClock();
		if (currentAbility->getDummy())
		{
			
			if (chosenAbility == 0)
			{
				soundCounter = 0;
				currentAbility->changeSoundBool(true);
				makeASoundBool = currentAbility->makeSound();
			}
		}
		if (!currentAbility->getDummy())
		{
			if (chosenAbility == 0)
			{
				soundCounter = 0;
				currentAbility->changeSoundBool(true);
				makeASoundBool = currentAbility->makeSound();
				
				
				for (int a = 0; a < 3; a++)
				{

					for (int i = 0; i < followerGroup[a].nrOfFollowers; i++)
					{
						sf::Vector2f dist = currentAbility->getPosition() - followerGroup[a].followers[i]->getPosition();
						float magni = sqrt(pow(dist.x, 2) + pow(dist.y, 2));

						if (abs(magni) < currentAbility->getRadius())
						{
							followerGroup[a].followers[i]->takeDamage(currentAbility->getSpecificVar());
						}

					}


					for (int i = 0; i < enemyProphet->getAllNrOfFollowers(a); i++)
					{


						sf::Vector2f dist = currentAbility->getPosition() - enemyProphet->getAllFollowers(a)[i]->getPosition();
						float magni = sqrt(pow(dist.x, 2) + pow(dist.y, 2));

						if (abs(magni) < currentAbility->getRadius())
						{
							enemyProphet->getAllFollowers(a)[i]->takeDamage(currentAbility->getSpecificVar());
							cout << "enemy Follower takes damage" << endl;

						}
					}

					sf::Vector2f dist = currentAbility->getPosition() - enemyProphet->getPosition();
					float magni = sqrt(pow(dist.x, 2) + pow(dist.y, 2));
					if (abs(magni) < currentAbility->getRadius())
					{
						enemyProphet->takeDamage(currentAbility->getSpecificVar());
						cout << "enemy Prophet takes damage" << endl;
					}
				}
				
			}




			for (int a = 0; a < 3; a++)
			{



				for (int i = 0; i < followerGroup[a].nrOfFollowers; i++)
				{

					if (chosenAbility == 1)
						followerGroup[a].followers[i]->touchedByAbility(false);
				}

			}
			enemyProphet->touchedByAbility(false);

		}
		if (chosenAbility != 2)
		{
			delete currentAbility;
		}

	}

}

void AbilityManager::stopReinforceAbility()
{
	if (reinforcementIsOn == true && abilityActive == false)
	{
		if (currentAbility->abilityEffectPulse())
		{
			
			if (!currentAbility->getDummy())
			{

				for (int a = 0; a < 3; a++)
				{



					for (int i = 0; i < followerGroup[a].nrOfFollowers; i++)
					{

						if (chosenAbility == 2 && followerGroup[a].followers[i]->checkIfEntityCanBeAffectedByAbility() == true)
						{
							followerGroup[a].followers[i]->touchedByAbility(false);
							followerGroup[a].followers[i]->resetDamage();


						}

					}
				}
			}
			delete currentAbility;
			reinforcementIsOn = false;
		}

	}
}

bool AbilityManager::returnReinforcementBool()
{
	return reinforcementIsOn;
}


void AbilityManager::updateAbility(sf::Vector2f placement)
{
	currentAbility->setPosition(placement);

}

void AbilityManager::placeCurrentAbility(sf::Vector2f position, int force)
{
	if (abilityActive)
	{
		abilityActive = false;
		delete currentAbility;
	}
	if (currentAbility != nullptr)
	{
		currentAbility = nullptr;
	}
	if (force == -1)
	{

		switch (chosenAbility)
		{

		case 0:
			cost = 100;
			
			if (thisProphet->getSouls() >= cost)
			{
				
				hasPlacedAbility = true;
				currentAbility = new Bomb(false);
			}
			break;
		case 1:
			cost = 70;
			if (thisProphet->getSouls() >= cost)
			{
				hasPlacedAbility = true;
				currentAbility = new Regen(false);
				
			}
			break;
		case 2:
			cost = 30;
			if (thisProphet->getSouls() >= cost)
			{
				hasPlacedAbility = true;
				currentAbility = new Reinforcement(false);
			}
			break;
		default:
			currentAbility = new Bomb(false);

			break;
		}
		if (thisProphet->getSouls() >= cost)
		{
			
			thisProphet->decreaseSouls(cost);
		}
		cost = 0;
	}
	else
	{
		switch (force)
		{
		case 0:
			hasPlacedAbility = true;
			
			currentAbility = new Bomb(true);
			break;
		case 1:
			hasPlacedAbility = true;
		
			currentAbility = new Regen(true);
			break;
		case 2:
			hasPlacedAbility = true;
		
			currentAbility = new Reinforcement(true);
			break;
		default:
			break;

		}
	}
	
	if (currentAbility != nullptr && hasPlacedAbility == true)
	{
	
		startAbility();
		currentAbility->placeAbility(position);
		hasPlacedAbility = false;
	}
}

void AbilityManager::recievePtr(Prophet* enemyPro, Prophet* thisProphet, group* followerGroup)
{
	enemyProphet = enemyPro;
	this->followerGroup = followerGroup;
	this->thisProphet = thisProphet;
}

void AbilityManager::whileAbilityIsActive()
{

	if (chosenAbility != 0)
	{
		if (!currentAbility->getDummy())
		{

			for (int a = 0; a < 3; a++)
			{

				for (int i = 0; i < followerGroup[a].nrOfFollowers; i++)
				{

					sf::Vector2f dist = currentAbility->getPosition() - followerGroup[a].followers[i]->getPosition();
					float magni = sqrt(pow(dist.x, 2) + pow(dist.y, 2));

					if (abs(magni) < currentAbility->getRadius())
					{

						if (chosenAbility == 2 && followerGroup[a].followers[i]->checkIfEntityCanBeAffectedByAbility() == false)
						{
							reinforcementIsOn = true;
							followerGroup[a].followers[i]->increaseDamageDone(15);
						}
						followerGroup[a].followers[i]->touchedByAbility(true);

					}
					else if (chosenAbility == 2 && followerGroup[a].followers[i]->checkIfEntityCanBeAffectedByAbility() == true && abs(magni) > currentAbility->getRadius())
					{
						if (currentAbility->abilityEffectPulse())
						{
							followerGroup[a].followers[i]->touchedByAbility(false);
							followerGroup[a].followers[i]->resetDamage();
						}

					}



				}
			}
		}
		if (chosenAbility == 1)
		{
			
			if (!currentAbility->getDummy())
			{
				if (currentAbility->abilityEffectPulse())
				{
					for (int a = 0; a < 3; a++)
					{
						for (int i = 0; i < followerGroup[a].nrOfFollowers; i++)
						{
								currentAbility->changeSoundBool(true);
								makeASoundBool = currentAbility->makeSound();
							if (followerGroup[a].followers[i]->checkIfEntityCanBeAffectedByAbility())
							{
								followerGroup[a].followers[i]->gainHealth(currentAbility->getSpecificVar());
							}
						}
					}
				}
			}
		}
		else
		{
			currentAbility->resetClock();
		}


	}

}

bool AbilityManager::getActivateSoundBool()
{

	if (makeASoundBool == true)
	{
		soundCounter++;
	}
	if (soundCounter > 1)
	{
		makeASoundBool = false;
		soundCounter = 0;
	}
	return makeASoundBool;
}

Ability* AbilityManager::getCurrentAbility() const
{
	return currentAbility;
}

