
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
	//	delete currentAbility;
	chosenAbility++;
	//cout << chosenAbility << endl;
	if (chosenAbility > 2)
	{
		chosenAbility = 0;
	}
	//chosenAbility = 0;
/*	switch (chosenAbility)
	{
	case 0:
		cout << "Bomb" << endl;
		currentAbility = new Bomb();
		break;
	case 1:
		cout << "Regen" << endl;
		currentAbility = new Regen();
		break;
	case 2:
		currentAbility = new Reinforcement();
		cout << "Reinforce" << endl;
		break;
	default:
		break;
	}*/

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
	currentAbility->turnBoolTrue();
	currentAbility->abilityActive();

	//cout << currentAbility << endl;
}

void AbilityManager::stopAbility()
{

	//currentAbility->abilityLifeTime();
	if (currentAbility->abilityLifeTime() == false)
	{
		currentAbility->resetClock();
		//	currentAbility->setPosition(sf::Vector2f(100000,100000));
		abilityActive = currentAbility->abilityLifeTime();
		if (chosenAbility == 0)
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
						followerGroup[a].followers[i]->takeDamage(currentAbility->getSpecificVar());
						//followerGroup->followers[i]->touchedByAbility(true);
					}

				}


				for (int i = 0; i < enemyProphet->getAllNrOfFollowers(a); i++)
				{
					for (int j = i; j < enemyProphet->getAllNrOfFollowers(a); j++)
					{

						sf::Vector2f dist = currentAbility->getPosition() - enemyProphet->getAllFollowers(a)[j]->getPosition();
						float magni = sqrt(pow(dist.x, 2) + pow(dist.y, 2));

						if (abs(magni) < currentAbility->getRadius())
						{
							enemyProphet->getAllFollowers(a)[i]->takeDamage(currentAbility->getSpecificVar());
							cout << "enemy Follower takes damage" << endl;

							//enemyProphet->getASingleFollower(i).touchedByAbility(true);
						}
					}
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



		for (int a = 0; a < 3; a++)
		{



			for (int i = 0; i < followerGroup[a].nrOfFollowers; i++)
			{

				if (chosenAbility == 1)
					followerGroup[a].followers[i]->touchedByAbility(false);
			}


			/*for (int i = 0; i < enemyProphet->getAllNrOfFollowers(a); i++)
			{

					enemyProphet->getAllFollowers(a)[i].touchedByAbility(false);

			}	*/
		}
		enemyProphet->touchedByAbility(false);

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


			for (int a = 0; a < 3; a++)
			{



				for (int i = 0; i < followerGroup[a].nrOfFollowers; i++)
				{
					cout << "turn down damage" << endl;

					if (chosenAbility == 2 && followerGroup[a].followers[i]->CheckIfEntityCanBeAffectedByAbility() == true)
					{


						followerGroup[a].followers[i]->touchedByAbility(false);
						followerGroup[a].followers[i]->returnDamage();


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
		delete currentAbility;
	}
	if (force == -1)
	{

		switch (chosenAbility)
		{

		case 0:
			currentAbility = new Bomb();
			break;
		case 1:
			currentAbility = new Regen();
			break;
		case 2:
			currentAbility = new Reinforcement();
			break;
		default:
			break;
		}
	}
	else
	{
		switch (force)
		{
		case 0:
			currentAbility = new Bomb();
			break;
		case 1:
			currentAbility = new Regen();
			break;
		case 2:
			currentAbility = new Reinforcement();
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

void AbilityManager::recievePtr(Prophet* enemyPro, group* followerGroup)
{
	enemyProphet = enemyPro;
	this->followerGroup = followerGroup;
}

void AbilityManager::whileAbilityIsActive()
{

	if (chosenAbility != 0)
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
		if (chosenAbility == 1)
		{

			if (currentAbility->abilityEffectPulse())
			{
				for (int a = 0; a < 3; a++)
				{

					for (int i = 0; i < followerGroup[a].nrOfFollowers; i++)
					{
						if (followerGroup[a].followers[i]->CheckIfEntityCanBeAffectedByAbility())
						{

							followerGroup[a].followers[i]->gainHealth(currentAbility->getSpecificVar());
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

Ability* AbilityManager::getCurrentAbility() const
{
	return currentAbility;
}

