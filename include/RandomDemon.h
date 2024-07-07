#pragma once

#include <SFML/Graphics.hpp>
#include "Demon.h"

class RandomDemon : public Demon
{
public:
	RandomDemon(sf::RectangleShape tile);
	~RandomDemon() = default;
	void Move(const sf::Time&);

private:
	sf::Vector2f m_direction;
	int m_numOfSteps;
	int m_side;
};