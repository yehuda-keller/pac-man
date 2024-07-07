#pragma once

#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "GameResources.h"

class FreezeGift : public Gift
{
public:
	FreezeGift(sf::RectangleShape tile)
		:Gift(tile, FREEZE)
	{}
	~FreezeGift() = default;
};