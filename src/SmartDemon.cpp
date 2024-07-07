#include "SmartDemon.h"
#include "GameResources.h"
#include <cmath>
#include "DataBoard.h"
SmartDemon::SmartDemon(sf::RectangleShape tile, Player* player)
	:Demon(tile, SMART), playerPtr(player)
{
}

void SmartDemon::Move(const sf::Time& deltaTime)
{
	if (abs(getObject().getPosition().x - playerPtr->getObject().getPosition().x) >= abs(getObject().getPosition().y - playerPtr->getObject().getPosition().y))
	{
		if (getObject().getPosition().x >= playerPtr->getObject().getPosition().x)
			setUpForMoveDirection(sf::Vector2f(-1, 0), sf::Vector2f(1, 1), 0);
		else if (getObject().getPosition().x < playerPtr->getObject().getPosition().x)
			setUpForMoveDirection(sf::Vector2f(1, 0), sf::Vector2f(-1, 1), 0);

	}
	else
	{
		if (getObject().getPosition().y >= playerPtr->getObject().getPosition().y)
			setDirection(sf::Vector2f(0, -1));
		else if (getObject().getPosition().y < playerPtr->getObject().getPosition().y)
			setDirection(sf::Vector2f(0 , 1));
	}

	setHowMuchToMove(getDirection(), getSpeed() - 15, deltaTime.asSeconds());
	setLastLocation(getObject().getPosition());
	//check if super pacman or not
	if(DataBoard::getDataBoardInstance().getSuperMode())
		getObject().setPosition(getObject().getPosition() - getHowMuchToMove());
	else
		getObject().setPosition(getObject().getPosition() + getHowMuchToMove());
}
