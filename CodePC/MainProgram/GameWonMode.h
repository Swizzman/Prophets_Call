#pragma once
#include "GameState.h"
class GameWonMode :
	public GameState
{
private:
	bool done;
	sf::Text gameWonText;
	sf::Font font;
public:
	GameWonMode();
	virtual ~GameWonMode();
	// Inherited via GameState
	virtual void handleEvents() override;
	virtual State update() override;
	virtual void render() override;
};

