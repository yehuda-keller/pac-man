#include "Cookie.h"
#include "GameResources.h"
#include "Player.h"

//constructor
Cookie::Cookie(sf::RectangleShape tile)
	:StaticObject(tile, COOKIE)
{
}

void Cookie::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}

void Cookie::handleCollision(Player& gameObject)
{
	gameObject.handleCollision(*this);
}