#pragma once
#include "Commands.h"
#include <SFML/Graphics.hpp>
#include "Follow.h"
#include "LowestHP.h"
#include "AttackProphet.h"
#include "Closest.h"
#include <ctime>
class Prophet;
struct group;
class CommandManager
{
private:
	int chosenCommand;
	Prophet *thisProphet;
	Prophet* enemyProphet;
	group* followerGroup;
	Commands** comands;
	int currentGroup;
	sf::Vector2f* followerDest;

public:
	CommandManager();
	virtual ~CommandManager();
	void goToPoint(sf::Vector2f point, int group, int nrOfFollower);
	void switchCommand(int  currentGroup);
	void useCommand();
	void recievePtr(Prophet* enemyPro, group *folGroup , Prophet* thisProhet);//not done
	void attackEnemy(int thisFollowerGroup,int thisFollowerInt);
	bool checkDistance();

};

