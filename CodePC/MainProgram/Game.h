#pragma once
#include "GameState.h"
class Game :
	public GameState
{
private:
	sf::Clock clock;
	sf::Time timePerFrame;
	sf::Time elapsedTimeSinceLastUpdate;
public:
	Game();
	virtual ~Game();
	// Inherited via GameState
	virtual void handleEvents() override;
	virtual State update() override;
	virtual void render() override;
};

