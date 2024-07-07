#include "Door.h"
#include "GameResources.h"
#include "Player.h"
#include "Demon.h"

Door::Door( sf::RectangleShape tile)
	:StaticObject(tile,DOOR)
{}

void Door::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}

void Door::handleCollision(Player& gameObject)
{
	gameObject.handleCollision(*this);
}

void Door::handleCollision(Demon& gameObject)
{
	gameObject.handleCollision(*this);
}