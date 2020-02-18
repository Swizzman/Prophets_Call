#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class UIManager 
{
private:
	struct followerPortraitStruct 
	{
		sf::Text followerHealthText;
		sf::RectangleShape followerHealthBar;
		sf::Sprite followerImage;
	};
	struct ProphetProperties
	{
		sf::Text prophetName;
		sf::Text healthText[2];
		sf::Text soulText;
		sf::RectangleShape ppRec[6];
	};
	struct commandStruct
	{
		sf::RectangleShape commandRec[4];
		int currentHighlight;
		sf::Text commandNames[4];
	};
private:
	static const int ABILITYCAP = 3;
	static const int GROUPCAP = 3;
	sf::Font font;
	sf::Text abilityNames[ABILITYCAP];
	sf::RectangleShape abilityRec[3];
	sf::RectangleShape healthBar;
	sf::Text convertingText;
	followerPortraitStruct** fps;
	commandStruct** cs;
	ProphetProperties pp;
	int numberOfFollowers;
	int chosenAbility;
	float healtProc;

public:
	 UIManager();
	 void setUpCS();
	 void setUpFps();
	 void setUpPp(int health);
	void updateCS();
	void updateFps();
	void updatePp(int health, int soul, int currentAbility);
	void drawUI(sf::RenderWindow &window);
};

