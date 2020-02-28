#pragma once
#include "GameState.h"
#include "Prophet.h"
#include "Follower.h"
#include "UIManager.h"
#include "NETWORKSTATE.h"
#include "SoundManager.h"
#include "Menu.h"
#include "Server.h"
#include <SFML/System.hpp>
#include <thread>

class GameHost :
	public GameState
{
private:
	Prophet* thisProphet;
	Prophet* otherProphet;
	Follower** allFollowers;
	UIManager uiManager;
	int nrOfTotalFollowers;
	sf::RectangleShape lel;
	int followerCap;
	sf::Clock clock;
	sf::Time timePerFrame;
	sf::Time elapsedTimeSinceLastUpdate;
	bool converting;
	bool abilityplaced;
	bool activeClient;
	Server server;
	sf::Mouse mouse;
	std::thread netWorkThread;
public:
	GameHost();
	void networking();
	virtual ~GameHost();
	// Inherited via GameState
	virtual void handleEvents() override;
	virtual State update() override;
	virtual void render() override;
};

