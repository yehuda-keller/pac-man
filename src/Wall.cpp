#include "Wall.h"
#include "GameResources.h"
#include "Player.h"
#include "Demon.h"

Wall::Wall(sf::RectangleShape tile)
	:StaticObject(tile, WALL)
{
}

void Wall::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}

void Wall::handleCollision(Player& gameObject)
{
	gameObject.handleCollision(*this);
}

void Wall::handleCollision(Demon& gameObject)
{
	gameObject.handleCollision(*this);
}


