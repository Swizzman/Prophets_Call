#pragma once
#include "STATE.h"
#include <SFML/Graphics.hpp>
class GameState
{
protected:
	const int WIDTH = 1920;
	const int HEIGHT = 1080;
	sf::RenderWindow window;
public:
	GameState();
	virtual void handleEvents() = 0;
	virtual State update() = 0;
	virtual void render() = 0;
	virtual ~GameState();
};

