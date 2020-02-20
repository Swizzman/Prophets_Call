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
		sf::RectangleShape nummberOfFollowerRec;
		int currentHighlight;
		sf::Text commandNames[4];
		int nummberOfFollowersInGroup;
		sf::Text nummberText[3];
		
	};
private:
	static const int ABILITYCAP = 3;
	static const int GROUPCAP = 3;
	static const int MAXFOLLOWER = 20;
	sf::Font font;
	sf::Text abilityNames[ABILITYCAP];
	sf::RectangleShape abilityRec[3];
	sf::RectangleShape healthBar;
	sf::Text convertingText;
	sf::Texture followerProfileTexture[4];
	std::string followerProfileTextureName[4];
	followerPortraitStruct** fps;
	commandStruct** cs;
	ProphetProperties pp;
	int numberOfFollowers;
	int chosenAbility;
	int currentCommandControll;
	float healtProc;
	bool canDrawPortrait;

public:
	 UIManager();
	 void setUpCS();
	 void setUpFps();
	 void setUpPp(int health);
	void updateCS(int currentCommand);
	void updateFps();
	void addFps(std::string textureName);
	void updatePp(int health, int soul, int currentAbility);
	void changeCS();
	void updateCSNumber(int nrOfFollowers);
	int getNrOfCurrentGroup();
	void drawUI(sf::RenderWindow &window);
};

