#pragma once
#include "GameState.h"
#include "Prophet.h"
#include "Follower.h"
#include "UIManager.h"
#include "NetworkManager.h"
#include "SoundManager.h"
#include "Menu.h"

class Game :
	public GameState
{
private:
	Prophet* thisProphet;
	Prophet* otherProphet;
	Follower** allFollowers;
	int nrOfTotalFollowers;
	sf::RectangleShape lel;
	int followerCap;
	sf::Clock clock;
	sf::Time timePerFrame;
	sf::Time elapsedTimeSinceLastUpdate;
	bool converting;
public:
	Game();
	virtual ~Game();
	// Inherited via GameState
	virtual void handleEvents() override;
	virtual State update() override;
	virtual void render() override;
};

