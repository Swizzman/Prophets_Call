#include "CommandManager.h"
#include "Prophet.h"

CommandManager::CommandManager()
{
	chosenCommand = 0;
	//this->comands = new Follow();
	this->followerGroup = nullptr;
	this->enemyProphet = nullptr;
	this->thisProphet = nullptr;
	this->comands = nullptr;

}

CommandManager::~CommandManager()
{
}

void CommandManager::goToPoint(sf::Vector2f point)
{
}

int CommandManager::switchCommand(int currentGroup)
{
	delete comands;
	chosenCommand++;
	this->currentGroup = currentGroup;
		if (chosenCommand >= 3)
		{
			chosenCommand = 0;
			switch (chosenCommand)
			{
			case 0:
				followerGroup[currentGroup].currentCommand = chosenCommand;
				comands = new Follow();
				break;
			case 1:
				followerGroup[currentGroup].currentCommand = chosenCommand;
				comands = new LowestHP();
				break;
			case 2:
				followerGroup[currentGroup].currentCommand = chosenCommand;
				comands = new AttackProphet();
				break;
			case 3:
				followerGroup[currentGroup].currentCommand = chosenCommand;
				comands = new Closest();
				break;
				default:
					break;
			}
		}
		return chosenCommand;

	

}

void CommandManager::useCommand()
{
}

int CommandManager::getCurrentCommand()
{
	return 0;
}

void CommandManager::recievePtr(Prophet* enemyPro, group* folGroup, Prophet* thisProphet)
{
	enemyProphet = enemyPro;
	thisProphet = thisProphet;
	this->followerGroup = folGroup;
	
}

bool CommandManager::checkDistance()
{
	return false;
}
