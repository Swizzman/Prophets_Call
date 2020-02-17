#pragma once
#include <SFML/Graphics.hpp>
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
		sf::Text healthText;
		sf::Text soulText;
	};
	struct commandStruct
	{
		sf::RectangleShape commandRec[4];
		int currentHighlight;
	};
private:
	static const int ABILITYCAP = 3;
	sf::Font font;
	sf::Text abilityNames[ABILITYCAP];
	sf::RectangleShape healthBar;
	sf::Text convertingText;
	followerPortraitStruct** fps;
	commandStruct** cs;
	ProphetProperties pp;

public:
	void updateCS();
	void updateFps();
	void updatePp();
	void drawUI();
};

