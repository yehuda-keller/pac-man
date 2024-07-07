#pragma once

#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "GameResources.h"

class LifeGift : public Gift
{
public:
	LifeGift(sf::RectangleShape tile)
		:Gift(tile, LIFE)
	{}
	~LifeGift() = default;
};