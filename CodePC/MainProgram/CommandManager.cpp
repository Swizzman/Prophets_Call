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

bool CommandManager::checkDistance()
{
	return false;
}
