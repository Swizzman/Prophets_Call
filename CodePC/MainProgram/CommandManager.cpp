#include "CommandManager.h"
#include "Prophet.h"

CommandManager::CommandManager()
{

	chosenCommand = 0;
	//this->comands = new Follow();
	this->followerGroup = nullptr;
	this->enemyProphet = nullptr;
	this->thisProphet = nullptr;
	this->comands = new Commands*[3]{nullptr};
	currentGroup = 0;
	//this->followerDest = new sf::Vector2f*[3]{nullptr};
	this->followerDest = new sf::Vector2f;

	for (int i = 0; i < 3; i++)
	{
		//this->followerDest[i] = new sf::Vector2f();
		this->comands[i] = new Follow();
	}

}

CommandManager::~CommandManager()
{
	delete[] followerDest;

	for (int i = 0; i < 3; i++)
	{
		
				
			//	delete followerDest[i];
				delete comands[i];
		

	}

	delete[] comands;
	
	
//	delete followerDest;

}

void CommandManager::goToPoint(sf::Vector2f point, int group, int nrOfFollower)
{
	
	followerGroup[group].followers[nrOfFollower]->moveTowardsDest(point, chosenCommand);
	
}

void CommandManager::switchCommand(int currentGroup)
{
	delete comands[currentGroup];
	this->currentGroup = currentGroup;
	chosenCommand = followerGroup[currentGroup].currentCommand;
	chosenCommand++;

		if (chosenCommand > 3)
		{
			chosenCommand = 0;
		}

			switch (chosenCommand)
			{
			case 0:

				comands[currentGroup] = new Follow();
				break;
			case 1:
				
				comands[currentGroup] = new LowestHP();
				break;
			case 2:
				
				comands[currentGroup] = new Closest();
				break;
			case 3:
			
				comands[currentGroup] = new AttackProphet();
				break;
				default:
					break;
				
			}
			followerGroup[currentGroup].currentCommand = chosenCommand;
		

		

	

}

void CommandManager::useCommand()
{
	for (int i = 0; i < 3; i++)
	{
		for (int a = 0; a < (followerGroup[i].nrOfFollowers); a++)
		{
			//std::cout << followerGroup[i].followers[a]->getPosition().x << std::endl;
			
			//sf::Vector2f route = comands->calculateRoute(thisProphet, enemyProphet, followerGroup[i].followers[a]);
			
				*followerDest = comands[i]->calculateRoute(thisProphet, enemyProphet, followerGroup[i].followers[a]);
			
			//sf::Vector2f thisDest = followerDest[i][a];

			//float width = followerGroup[i].followers[a]->getBounds().width;
			//float height = followerGroup[i].followers[a]->getBounds().height;
			//for (int b = 0; b < 3; b++)
			//{
			//	for (int c = 0; c < followerGroup[b].nrOfFollowers; c++)
			//	{
			//		/*if (i == b && a == c)
			//		{
			//			if (followerGroup[b].nrOfFollowers > c)
			//			{
			//				c++;
			//			}
			//			
			//		}*/
			//			//while (followerDest[i][a] == followerDest[b][c] )
			//			//{

			//			//	std::cout << "same" << std::endl;
			//			////	followerDest[i][a] = comands->calculateRoute(thisProphet, enemyProphet, followerGroup[i].followers[a] ) + sf::Vector2f(rand() % 20-10, rand() % 20-10);
			//			////	thisDest = followerDest[i][a];
			//			//}
			//		
			//		

			//	}
			//}
				// thisProphet->getAllFollowers(i)[a];
				if (chosenCommand == 0)
				{

                 //attackEnemy(i,a);
				}

				

			goToPoint(*followerDest, i, a);
			

		/*	sf::Vector2f dest = comands->calculateRoute(thisProphet, enemyProphet, followerGroup[i].followers[a]);
			goToPoint(dest,i, a);*/

		//	goToPoint(comands->calculateRoute( thisProphet,enemyProphet, followerGroup[i].followers[a]), i,a);
			
		}
	}


}

int CommandManager::getCurrentCommand()
{
	return 0;
}

void CommandManager::recievePtr(Prophet* enemyPro, group* folGroup, Prophet* thisProphet)
{
	enemyProphet = enemyPro;
	this->thisProphet = thisProphet;
	this->followerGroup = folGroup;
	
	
}

void CommandManager::attackEnemy(int thisFollowerGroup, int thisFollowerInt)
{

	thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt];

				sf::Vector2f temp(0, 0);
				float magniTemp = 1000000;
				GameEntity* tempEntity;
				Follower enemyfol;
				bool followerIsClosest = false;
	if (chosenCommand == 0 && enemyProphet->getAllNrOfFollowers(0) != 0 && enemyProphet->getAllNrOfFollowers(1) != 0 && enemyProphet->getAllNrOfFollowers(2) != 0 )
		for (int a = 0; a < 3; a++)
		{
			for (int i = 0; i < enemyProphet->getAllNrOfFollowers(a); i++)
			{

					
						if (magniTemp > sqrt(pow((enemyProphet->getAllFollowers(a)[i].getPosition().x + enemyProphet->getAllFollowers(a)[i].getBounds().width / 2) - (thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].getPosition().x + thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].getBounds().width / 2), 2) +
							pow((enemyProphet->getAllFollowers(a)[i].getPosition().x + enemyProphet->getAllFollowers(a)[i].getBounds().height / 2) - (thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].getPosition().y + thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].getBounds().height / 2), 2)))
						{

							cout << "should not check here" << endl;
							/*temp = enemyProphet->getAllFollowers(a)[i].getPosition() + sf::Vector2f(enemyProphet->getAllFollowers(a)[i].getBounds().width / 2, enemyProphet->getAllFollowers(a)[i].getBounds().height / 2)-
								thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].getPosition() +
								sf::Vector2f(thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].getBounds().width / 2, thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].getBounds().height / 2);*/

							magniTemp = sqrt(pow((enemyProphet->getAllFollowers(a)[i].getPosition().x + enemyProphet->getAllFollowers(a)[i].getBounds().width / 2) - (thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].getPosition().x + thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].getBounds().width / 2), 2) +
								pow((enemyProphet->getAllFollowers(a)[i].getPosition().x + enemyProphet->getAllFollowers(a)[i].getBounds().height / 2) - (thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].getPosition().y + thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].getBounds().height / 2), 2));
							enemyfol = enemyProphet->getAllFollowers(a)[i];


							followerIsClosest = true;
						}




				
			}

		}
				if (magniTemp > sqrt(pow((enemyProphet->getPosition().x+ enemyProphet->getBounds().width/2) - (thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].getPosition().x + thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].getBounds().width/2), 2) +
					pow((enemyProphet->getPosition().y + enemyProphet->getBounds().height / 2) - (thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].getPosition().y + thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].getBounds().height/2), 2)))
				{
							//cout << "entering function" << endl;
					/*temp = enemyProphet->getPosition() + sf::Vector2f(enemyProphet->getBounds().width / 2 , enemyProphet->getBounds().height / 2) - 
						thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].getPosition() + 
						sf::Vector2f(thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].getBounds().width / 2 , thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].getBounds().height / 2);*/

					magniTemp = sqrt(pow((enemyProphet->getPosition().x + enemyProphet->getBounds().width / 2) - (thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].getPosition().x + thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].getBounds().width / 2), 2) +
						pow((enemyProphet->getPosition().y + enemyProphet->getBounds().height / 2) - (thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].getPosition().y + thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].getBounds().height / 2), 2));
				//	tempEntity = enemyProphet;
					followerIsClosest = false;
				}
	
			//	sf::Vector2f dist = temp;
				float magni = magniTemp;
				
				

				if (thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].getFollowerRange() > magni && thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].getAttackCooldown() && thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].getFollowerRange() < 500)
				{
					
					//thisFollower.attack(tempEntity->takeDamage(10), 10);
					if (followerIsClosest)
					{
						enemyfol.takeDamage(thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].inflictDamage());
						cout << "choosing follower" << endl;
					}
					else
					{
						cout << "Distance: " << magni << endl;
						cout << "Range : " << thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].getFollowerRange() << endl;
						enemyProphet->takeDamage(thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].inflictDamage());
					cout << "choosing prophet" << endl;
					}
				}
				if (thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].getAttackCooldown() == false)
				{
					
					thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].attackCooldown();
				}
				else
				{
					thisProphet->getAllFollowers(thisFollowerGroup)[thisFollowerInt].resetAttackClock();
				}



	
}


bool CommandManager::checkDistance()
{
	return false;
}
