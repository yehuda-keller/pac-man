#include "RandomDemon.h"
#include "GameResources.h"


RandomDemon::RandomDemon(sf::RectangleShape tile)
	:Demon(tile, DEMON), m_numOfSteps(20), m_side(0)
{
}

//set movment for the stiuped demon
void RandomDemon::Move(const sf::Time& deltaTime)
{
	//for every direction there is a limit of 20 "steps"
	if (m_numOfSteps == 20)
		m_side = rand() % 4;
	else if (m_numOfSteps == 0)
		m_numOfSteps = 21;

	//which direction to move
	switch (m_side)
	{
	case Left:
		setUpForMoveDirection(sf::Vector2f(-1, 0), sf::Vector2f(-1, 1),0);
		m_numOfSteps--;
		break;
	case Right:
		setUpForMoveDirection(sf::Vector2f(1, 0), sf::Vector2f(1, 1), 0);
		m_numOfSteps--;
		break;
	case Up:
		setDirection(sf::Vector2f(0, -1));
		m_numOfSteps--;
		break;
	case Down:
		setDirection(sf::Vector2f(0 , 1));
		m_numOfSteps--;
		break;
	}

	setHowMuchToMove(getDirection(), getSpeed(), deltaTime.asSeconds());
	setLastLocation(getObject().getPosition());
	auto newPosition = sf::Vector2f(getObject().getPosition() + getHowMuchToMove());
	getObject().setPosition(newPosition);
}