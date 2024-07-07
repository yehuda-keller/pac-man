#pragma once

#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "GameResources.h"

class TimeGift : public Gift
{
public:
	TimeGift(sf::RectangleShape tile)
		:Gift(tile,TIME)
	{}
	~TimeGift() = default;
};