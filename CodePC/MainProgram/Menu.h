#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"

#include <iostream>
class Menu : public GameState 
{

private:
	
	sf::Font font;
	sf::Text playText;
	sf::Text mainMenuText;
	sf::Text CloseText;
	sf::Text ConnectingText;
	sf::Mouse mouse;
	

	sf::Clock clock;
	sf::Time timePerFrame;
	sf::Time elapsedTimeSinceLastUpdate;

	int currentHighlightedButton;

public:
	Menu();
	virtual ~Menu();

	sf::Text renderText();


	


	// Inherited via GameState
	virtual void handleEvents() override;

	virtual State update() override;

	virtual void render() override;

};

