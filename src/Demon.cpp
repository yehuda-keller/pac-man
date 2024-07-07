#include "Demon.h"
#include "GameResources.h"
#include "Player.h"
#include "TimeManger.h"

Demon::Demon( sf::RectangleShape tile,  int wantedTexture)
	:MovingObject( tile, wantedTexture), m_direction(0, 0)
{}

void Demon::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}

//demon collide with player
void Demon::handleCollision(Player& gameObject)
{
	gameObject.handleCollision(*this);
}

//demon collide with wall
void Demon::handleCollision(Wall& gameObject)
{
	getObject().setPosition(getLastLocation());
}

//demon collide with door
void Demon::handleCollision(Door& gameObject)
{
	getObject().setPosition(getLastLocation());
}
