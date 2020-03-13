
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
	thisProphet = nullptr;
}

AbilityManager::~AbilityManager()
{
	if (abilityActive)
	{
		delete currentAbility;
	}
	//currentAbility =  nullptr;



}

int AbilityManager::switchAbility()
{
	chosenAbility++;
	//cout << chosenAbility << endl;
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
	/*if (abilityActive == false)
	{
		currentAbility->changeSoundBool(true);
		abilityActive = true;
	}
	if (abilityActive == true && currentAbility->makeSound())
	{
		abilityActive = false;
	}*/


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
						//currentAbility->getPosition() - followerGroup->followers[i]->getPosition()
						sf::Vector2f dist = currentAbility->getPosition() - followerGroup[a].followers[i]->getPosition();
						float magni = sqrt(pow(dist.x, 2) + pow(dist.y, 2));

						if (abs(magni) < currentAbility->getRadius())
						{
							followerGroup[a].followers[i]->takeDamage(currentAbility->getSpecificVar());
							//followerGroup->followers[i]->touchedByAbility(true);
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

							//enemyProphet->getASingleFollower(i).touchedByAbility(true);

						}
					}

					sf::Vector2f dist = currentAbility->getPosition() - enemyProphet->getPosition();
					float magni = sqrt(pow(dist.x, 2) + pow(dist.y, 2));
					if (abs(magni) < currentAbility->getRadius())
					{
						enemyProphet->takeDamage(currentAbility->getSpecificVar());
						cout << "enemy Prophet takes damage" << endl;
						//enemyProphet->touchedByAbility(true);
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
						cout << "turn down damage" << endl;

						if (chosenAbility == 2 && followerGroup[a].followers[i]->CheckIfEntityCanBeAffectedByAbility() == true)
						{
							//currentAbility->changeSoundBool(true);
							//makeASoundBool = currentAbility->makeSound();

							followerGroup[a].followers[i]->touchedByAbility(false);
							followerGroup[a].followers[i]->returnDamage();


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
	if (force == -1)
	{

		switch (chosenAbility)
		{

		case 0:
			cost = 100;
			if (thisProphet->getSouls() > cost)
			{
				currentAbility = new Bomb(false);
			}
			break;
		case 1:
			cost = 70;
			if (thisProphet->getSouls() > cost)
			{
				currentAbility = new Regen(false);
				
			}
			break;
		case 2:
			cost = 30;
			if (thisProphet->getSouls() > cost)
			{

				currentAbility = new Reinforcement(false);
			}
			break;
		default:
			break;
		}
		thisProphet->decreaseSouls(cost);
		cost = 0;
	}
	else
	{
		switch (force)
		{
		case 0:
			currentAbility = new Bomb(true);
			break;
		case 1:
			currentAbility = new Regen(true);
			break;
		case 2:
			currentAbility = new Reinforcement(true);
			break;
		default:
			break;

		}
	}
	if (currentAbility != nullptr)
	{

		startAbility();
		currentAbility->placeAbility(position);
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

					//currentAbility->getPosition() - followerGroup->followers[i]->getPosition()
					sf::Vector2f dist = currentAbility->getPosition() - followerGroup[a].followers[i]->getPosition();
					float magni = sqrt(pow(dist.x, 2) + pow(dist.y, 2));

					if (abs(magni) < currentAbility->getRadius())
					{

						if (chosenAbility == 2 && followerGroup[a].followers[i]->CheckIfEntityCanBeAffectedByAbility() == false)
						{
							reinforcementIsOn = true;
							followerGroup[a].followers[i]->increaseDamageDone(15);
						}
						followerGroup[a].followers[i]->touchedByAbility(true);

						//followerGroup[a].followers[i]->touchedByAbility(true);



					//followerGroup->followers[i]->touchedByAbility(true);
					}
					else if (chosenAbility == 2 && followerGroup[a].followers[i]->CheckIfEntityCanBeAffectedByAbility() == true && abs(magni) > currentAbility->getRadius())
					{
						cout << "should not start" << endl;
						if (currentAbility->abilityEffectPulse())
						{


							followerGroup[a].followers[i]->touchedByAbility(false);
							followerGroup[a].followers[i]->returnDamage();
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
							if (followerGroup[a].followers[i]->CheckIfEntityCanBeAffectedByAbility())
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
	
	/*if (makeASoundBool == true)
	{

		stopSoundFunction = true;
		return currentAbility->makeSound();
	}
	else
	{
		return false;
	}*/

	if (makeASoundBool == true)
	{
		soundCounter++;
	}
	if (soundCounter > 1)
	{
		makeASoundBool = false;
		soundCounter = 0;
	}
	//cout << "regenSound" << endl;
	return makeASoundBool;
	//cout << "aaaaa" << endl;
}

Ability* AbilityManager::getCurrentAbility() const
{
	return currentAbility;
}

