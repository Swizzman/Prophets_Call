#pragma once
#include "GameState.h"
#include "Prophet.h"
#include "Follower.h"
#include "UIManager.h"
#include "NETWORKSTATE.h"
#include "SoundManager.h"
#include "Menu.h"
#include "Client.h"
#include <thread>

class GameClient :
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
	Client client;
	sf::Mouse mouse;
	std::thread networkThread;
public:
	GameClient();
	virtual ~GameClient();
	void netWorking();
	// Inherited via GameState
	virtual void handleEvents() override;
	virtual State update() override;
	virtual void render() override;
};


