#include "Key.h"
#include "GameResources.h"
#include "Player.h"

Key::Key( sf::RectangleShape tile)
	:StaticObject(tile, KEY)
{
}

void Key::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}

void Key::handleCollision(Player& gameObject)
{
	gameObject.handleCollision(*this);
}
