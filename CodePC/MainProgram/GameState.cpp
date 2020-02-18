#include "GameState.h"

GameState::GameState(): window(sf::VideoMode(WIDTH, HEIGHT), "Prophets Call", sf::Style::Fullscreen)
{ 
	
	screenState = 0;
}

void GameState::changeFullscreenMode()
{
	screenState++;
	if (screenState >= 2)
	{
		screenState = 0;
	}
	if (screenState == 0)
	{
		window.create(sf::VideoMode(WIDTH, HEIGHT), "Prophets Call", sf::Style::Fullscreen);
		
	}
	else
	{
		window.create(sf::VideoMode(WIDTH, HEIGHT), "Prophets Call");
	}

}

GameState::~GameState()
{
}
