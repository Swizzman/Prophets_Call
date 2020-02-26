#pragma once
#include "Commands.h"
#include <SFML/Graphics.hpp>
#include "Follow.h"
#include "LowestHP.h"
#include "AttackProphet.h"
#include "Closest.h"
class Prophet;
struct group;
class CommandManager
{
private:
	int chosenCommand;
	Prophet *thisProphet;
	Prophet* enemyProphet;
	group* followerGroup;
	Commands* comands;
	int currentGroup;

public:
	CommandManager();
	~CommandManager();
	void goToPoint(sf::Vector2f point);
	int switchCommand(int currentGroup);
	void useCommand();
	int getCurrentCommand();
	void recievePtr(Prophet* enemyPro, group *folGroup , Prophet* thisProhet);//not done
	bool checkDistance();

};

