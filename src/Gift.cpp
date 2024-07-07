#include "Gift.h"
#include "GameResources.h"
#include "Player.h"

Gift::Gift( sf::RectangleShape tile, int wantedTexture)
	:StaticObject(tile, wantedTexture)
{
}

void Gift::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}

void Gift::handleCollision(Player& gameObject)
{
	gameObject.handleCollision(*this);
}

