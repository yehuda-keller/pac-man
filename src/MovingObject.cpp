#include "MovingObject.h"


MovingObject::MovingObject(sf::RectangleShape tile, int wantedTexture)
	:m_firstLocation(tile.getPosition()),m_lastLocation(0,0), m_direction(0, 0), m_speedPerSecond(50.f),
	 GameObject(tile, wantedTexture)
{}

//update the direction
void MovingObject::setDirection(sf::Vector2f direction)
{
	m_direction = direction;
}

//get which direction to turn
sf::Vector2f MovingObject::getDirection() const
{
	return  m_direction;
}

//get the speed of the object
float MovingObject::getSpeed() const
{
	return m_speedPerSecond;
}

void MovingObject::setHowMuchToMove(sf::Vector2f direction, float speedperpixel, float speedperseconds)
{
	m_HowMuchToMove = direction * speedperpixel * speedperseconds;
}

sf::Vector2f MovingObject::getHowMuchToMove() const
{
	return m_HowMuchToMove;
}
void MovingObject::setLastLocation(sf::Vector2f location)
{
	m_lastLocation = location;
}

sf::Vector2f MovingObject::getLastLocation() const
{
	return m_lastLocation;
}

sf::Vector2f MovingObject::getFirstLocation() const
{
	return m_firstLocation;
}

void MovingObject::setFirstLocation(sf::Vector2f location)
{
	m_firstLocation = location;
}

void MovingObject::setUpForMoveDirection(sf::Vector2f direction, sf::Vector2f scale, int rotate)
{
	getObject().setScale(scale.x, scale.y);
	setDirection(direction);
	getObject().setRotation(rotate);
}




