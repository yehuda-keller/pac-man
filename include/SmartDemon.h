#pragma once
#include <SFML/Graphics.hpp>
#include "Demon.h"
#include "Player.h"
class SmartDemon : public Demon
{
public:
	SmartDemon( sf::RectangleShape tile, Player*);
	~SmartDemon() = default;
	void Move(const sf::Time&);
private:
	Player* playerPtr;
};