#include "UIManager.h"

UIManager::UIManager()
{
	font.loadFromFile("c:/windows/fonts/arial.ttf");
	this->pp.healthText[0].setFont(font);
	this->pp.healthText[1].setFont(font);
	this->pp.prophetName.setFont(font);
	this->pp.soulText.setFont(font);
	for (int i = 0; i < ABILITYCAP; i++)
	{
		this->abilityNames[i].setFont(font);
	}
	
	chosenAbility = 0;
	numberOfFollowers = 4;
	
	//followerPortraitStruct *fps;
	//commandStruct* cs;

	this->cs = new commandStruct * [GROUPCAP]{nullptr};
	this->fps = new followerPortraitStruct * [numberOfFollowers] {nullptr};
	for (int i = 0; i < GROUPCAP; i++)
	{
		this->cs[i] = new commandStruct();
		this->cs[i]->currentHighlight = 0;
		for (int a = 0; a < 4; a++)
		{
			
			
				this->cs[i]->commandNames[a].setFont(font);
			

		}
		for (int a = 0; a < 3; a++)
		{
			this->cs[i]->nummberText[a];
			
		}
		this->cs[i]->nummberOfFollowersInGroup = 0;
	
	}
	
	for (int i = 0; i < numberOfFollowers; i++)
	{
		this->fps[i] = new followerPortraitStruct();
		this->fps[i]->followerHealthText.setFont(font);
	}


	currentCommandControll = 0;
	//setUpPp();

}

void UIManager::setUpCS()
{

	for (int i = 0; i < GROUPCAP; i++)
	{
		this->cs[i]->commandNames[0].setString("Follow");
		this->cs[i]->commandNames[1].setString("Lowest Hp");
		this->cs[i]->commandNames[2].setString("Closest");
		this->cs[i]->commandNames[3].setString("Enemy Prophet");



		for (int a = 0; a < 4; a++)
		{
			this->cs[i]->commandRec[a].setSize(sf::Vector2f(360, 50));
			this->cs[i]->commandRec[a].setPosition(1920 - 360, 100+ 50*a +(250*i));
			this->cs[i]->commandRec[a].setOutlineThickness(4);
			this->cs[i]->commandRec[a].setFillColor(sf::Color::Transparent);
			this->cs[i]->commandRec[a].setOutlineColor(sf::Color::White);
			
			this->cs[i]->commandNames[a].setPosition(this->cs[i]->commandRec[a].getPosition().x +10, this->cs[i]->commandRec[a].getPosition().y + this->cs[i]->commandNames[a].getGlobalBounds().height/4);
		}
		

		

			if (currentCommandControll == i)
			{
				for (int a = 0; a < 4; a++)
				{
					cs[i]->commandRec[a].setOutlineColor(sf::Color::Magenta);
				}

			}
			else
			{
				for (int a = 0; a < 4; a++)
				{
					cs[i]->commandRec[a].setOutlineColor(sf::Color::White);
				}
			}
		


	}



}

void UIManager::setUpFps()
{

}

void UIManager::setUpPp(int health)
{
	this->pp.ppRec[0].setSize(sf::Vector2f(1800, 200));
	this->pp.ppRec[0].setPosition(960 - this->pp.ppRec[0].getGlobalBounds().width / 2, 850);

	this->pp.ppRec[1].setSize(sf::Vector2f(360, 200));
	this->pp.ppRec[1].setPosition(this->pp.ppRec[0].getPosition().x, 850);

	this->pp.ppRec[2].setSize(sf::Vector2f(360, 200));
	this->pp.ppRec[2].setPosition(this->pp.ppRec[0].getPosition().x + this->pp.ppRec[2].getGlobalBounds().width + 4, 850);

	this->pp.ppRec[3].setSize(sf::Vector2f(360, 50));
	this->pp.ppRec[3].setPosition(this->pp.ppRec[2].getPosition().x, 850);

	this->pp.ppRec[4].setSize(sf::Vector2f(2.4f * 100, 30));
	this->pp.ppRec[4].setPosition(this->pp.ppRec[3].getPosition().x + this->pp.ppRec[3].getGlobalBounds().width / 2 - this->pp.ppRec[4].getGlobalBounds().width / 2, 850 + this->pp.ppRec[3].getGlobalBounds().height + 50);

	this->healthBar.setSize(sf::Vector2f(240, 30));
	this->healthBar.setPosition(this->pp.ppRec[3].getPosition().x + this->pp.ppRec[3].getGlobalBounds().width / 2 - this->pp.ppRec[4].getGlobalBounds().width / 2, 850 + this->pp.ppRec[3].getGlobalBounds().height + 50);

	healthBar.setFillColor(sf::Color::Red);
	healthBar.setOutlineThickness(2);
	for (int i = 0; i < 6; i++)
	{
		this->pp.ppRec[i].setFillColor(sf::Color::Transparent);
		this->pp.ppRec[i].setOutlineColor(sf::Color::White);
		this->pp.ppRec[i].setOutlineThickness(4);
	}
	this->pp.ppRec[4].setFillColor(sf::Color::Green);
	this->pp.ppRec[4].setOutlineThickness(2);

	this->pp.healthText[0].setString("Health");
	this->pp.healthText[0].setPosition(this->pp.ppRec[3].getPosition().x + this->pp.ppRec[3].getGlobalBounds().width / 2 - this->pp.healthText[0].getGlobalBounds().width / 2, 850 + pp.ppRec[3].getGlobalBounds().height);
	this->pp.healthText[1].setString(std::to_string(100) + "%");
	this->pp.healthText[1].setPosition(this->pp.ppRec[3].getPosition().x + this->pp.ppRec[3].getGlobalBounds().width / 2 - this->pp.healthText[1].getGlobalBounds().width / 2, this->healthBar.getPosition().y - 5);
	this->pp.prophetName.setString("Prophet");
	this->pp.prophetName.setPosition(this->pp.ppRec[3].getPosition().x + this->pp.ppRec[3].getGlobalBounds().width / 2 - this->pp.prophetName.getGlobalBounds().width / 2, 850);

	this->pp.soulText.setString("Souls: " + 0);
	this->pp.soulText.setPosition(this->healthBar.getPosition().x, this->pp.healthText[1].getPosition().y + this->pp.soulText.getGlobalBounds().height * 2);




	this->abilityNames[0].setString(" Bomb			       Cost 50");
	this->abilityNames[1].setString(" Regen				  Cost 70");
	this->abilityNames[2].setString(" Reinforcement	Cost 100");
	for (int i = 0; i < 3; i++)
	{
		this->abilityRec[i].setSize(sf::Vector2f(360, 66));
		this->abilityRec[i].setPosition(this->pp.ppRec[0].getPosition().x, this->pp.ppRec[0].getPosition().y +(this->abilityRec[0].getGlobalBounds().height-7) *i );
		this->abilityRec[i].setFillColor(sf::Color::Transparent);
		this->abilityRec[i].setOutlineColor(sf::Color::White);
		this->abilityRec[i].setOutlineThickness(4);

		this->abilityNames[i].setPosition(this->abilityRec[i].getPosition().x, this->abilityRec[i].getPosition().y + this->abilityNames[i].getGlobalBounds().height/2);
	}

//	std::cout << health << std::endl;

	this->healtProc = health ;
	

}

void UIManager::updateCS(int currentCommand)
{
		
	
	for (int i = 0; i < GROUPCAP; i++)
	{
		if (currentCommandControll == i)
		{
			std::cout << currentCommand << std::endl;
			for (int a = 0; a < 4; a++)
			{
				if (currentCommand == a)
				{
					cs[i]->commandRec[a].setFillColor(sf::Color::Magenta);

				}
				else
				{
					cs[i]->commandRec[a].setFillColor(sf::Color::Transparent);
				}


			}

		}
	}



}

void UIManager::updateFps()
{

	
}

void UIManager::updatePp(int health, int soul ,int currentAbility)
{
	this->chosenAbility = currentAbility;

	//std::cout << healtProc << std::endl;
	if (health <= 0)
	{
		health = 0;
	}
	this->pp.healthText[1].setString(std::to_string( (int)(100* (health/healtProc))) + "%");
	this->pp.healthText[1].setPosition(this->pp.ppRec[3].getPosition().x + this->pp.ppRec[3].getGlobalBounds().width / 2 - this->pp.healthText[1].getGlobalBounds().width / 2, this->healthBar.getPosition().y -5 );

	
	this->pp.soulText.setString("Souls: " +std::to_string(soul));
	this->pp.soulText.setPosition(this->healthBar.getPosition().x, this->pp.healthText[1].getPosition().y+ this->pp.soulText.getGlobalBounds().height*2 );


	this->pp.ppRec[4].setSize(sf::Vector2f(2.4f * (100 * ( health/healtProc)), 30));
	//this->pp.ppRec[4].setPosition(this->pp.ppRec[3].getPosition().x + this->pp.ppRec[3].getGlobalBounds().width / 2 - this->pp.ppRec[4].getGlobalBounds().width / 2, 850 + this->pp.ppRec[3].getGlobalBounds().height + 50);

	for (int i = 0; i < ABILITYCAP; i++)
	{
		if (i==chosenAbility)
		{
			abilityRec[i].setFillColor(sf::Color::Magenta);
		}
		else
		{
			abilityRec[i].setFillColor(sf::Color::Transparent);
		}
	}


}

void UIManager::changeCS()
{
	currentCommandControll++;
	if (currentCommandControll > GROUPCAP - 1)
	{
		currentCommandControll = 0;
	}

	for (int i = 0; i < GROUPCAP; i++)
	{
		if (currentCommandControll == i)
		{
			for (int a = 0; a < 4; a++)
			{
				cs[i]->commandRec[a].setOutlineColor(sf::Color::Magenta);
			}
			
		}
		else
		{
			for (int a = 0; a < 4; a++)
			{
				cs[i]->commandRec[a].setOutlineColor(sf::Color::White);
			}
		}
	}
}

void UIManager::drawUI(sf::RenderWindow &window)
{



	window.draw(pp.soulText);
	window.draw(pp.prophetName);
	window.draw(healthBar);

	for (int i = 0; i < 5; i++)
	{
		window.draw(pp.ppRec[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		window.draw(abilityRec[i]);
	}
	window.draw(pp.healthText[0]);
	window.draw(pp.healthText[1]);
	for (int i = 0; i < ABILITYCAP; i++)
	{
		window.draw(abilityNames[i]);
	}

	for (int i = 0; i < GROUPCAP; i++)
	{


		for (int a = 0; a < 4; a++)
		{
		
			window.draw(this->cs[i]->commandRec[a]);
			window.draw(this->cs[i]->commandNames[a]);
		}

	}
	
}
