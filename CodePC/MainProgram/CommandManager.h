#pragma once
#include "Commands.h"
#include "Prophet.h"
#include <SFML/Graphics.hpp>
class CommandManager
{
private:
	int chosenCommand;
	Prophet *thisProphet;
	Prophet* enemyProphet;	

public:
	CommandManager();
	~CommandManager();
	void goToPoint(sf::Vector2f point);
	void switchCommand();
	void useCommand();
	int getCurrentCommand();
	void recievePtr(Prophet* enemyPro);//not done
	bool checkDistance();

};

