#pragma once

#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "GameResources.h"

class SuperGift : public Gift
{
public:
	SuperGift(sf::RectangleShape tile)
		:Gift(tile, GIFT)
	{}
	~SuperGift() = default;
};