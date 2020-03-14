#pragma once
#include "GameState.h"
class GameLostMode :
	public GameState
{
private:
	bool done;
	sf::Text gameLostText;
	sf::Font font;
public:
	GameLostMode();
	virtual ~GameLostMode();
	// Inherited via GameState
	virtual void handleEvents() override;
	virtual State update() override;
	virtual void render() override;
};

