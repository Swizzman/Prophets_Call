#include "Background.h"

Background::Background()
{
	backgroundTexture.loadFromFile("../images/PCTileMap.png");
	backgroundSprite.setTexture(backgroundTexture);

}

Background::~Background()
{
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->backgroundSprite);
}
