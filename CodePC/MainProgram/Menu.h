#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include <fstream>
class Menu : public GameState 
{

private:
	
	sf::Font font;
	sf::Text playText;
	sf::Text mainMenuText;
	sf::Text closeText;
	sf::Text connectingText;
	sf::Text iPText;
	sf::Mouse mouse;
	std::string input;
	sf::Text inputText;
	sf::Clock clock;
	sf::Time timePerFrame;
	sf::Time elapsedTimeSinceLastUpdate;
	std::ofstream iPOut;
	int currentHighlightedButton;
	bool iPMode;
	bool inputDone;
public:
	Menu();
	virtual ~Menu();
	// Inherited via GameState
	virtual void handleEvents() override;

	virtual State update() override;

	virtual void render() override;

};

