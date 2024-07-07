#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class StaticObject;

class MovingObject : public GameObject 
{
public:
	MovingObject(sf::RectangleShape tile, int wantedTexture);
	virtual ~MovingObject() = default;
	virtual void Move(const sf::Time&) = 0;
	void setDirection(sf::Vector2f);//int, int);
	sf::Vector2f getDirection() const;
	float getSpeed() const;
	void setHowMuchToMove(sf::Vector2f, float, float);
	sf::Vector2f getHowMuchToMove() const;
	void setLastLocation(sf::Vector2f location);
	sf::Vector2f getLastLocation() const;
	sf::Vector2f getFirstLocation() const;
	void setFirstLocation(sf::Vector2f location);
	void setUpForMoveDirection(sf::Vector2f direction, sf::Vector2f scale, int rotate);
private:
	sf::Vector2f m_firstLocation;
	sf::Vector2f m_lastLocation;
	sf::Vector2f m_direction;
	float m_speedPerSecond;
	sf::Vector2f m_HowMuchToMove;
};