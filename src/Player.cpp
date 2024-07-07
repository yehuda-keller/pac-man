#include "Player.h"
#include "GameResources.h"
#include "Wall.h"
#include "DataBoard.h"
#include "Cookie.h"
#include "Key.h"
#include "Gift.h"
#include "TimeManger.h"
#include "FreezeGift.h"
#include "SuperGift.h"
#include "TimeGift.h"
#include "LifeGift.h"

//constructor
Player::Player(sf::RectangleShape tile)
	: MovingObject(tile,PACMAN),
	  m_PlayerState(std::make_unique<RegularState>()), m_Score(0)
{
	createLife();
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(getObject());

	for (int i = 0; i < (int)m_Life.size(); i++)//draw life
		window.draw(m_Life[i]);

	window.draw(GameResources::getGameResources().createText(std::to_string(m_Score), sf::Vector2f(1200, 350), sf::Color::White, 1));
}

//handle the movment of the player
void Player::Move(const sf::Time& deltaTime)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		setUpForMoveDirection(sf::Vector2f(-1, 0), sf::Vector2f(-1, 1), 0);
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		setUpForMoveDirection(sf::Vector2f(1, 0), sf::Vector2f(1, 1), 0);
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		setUpForMoveDirection(sf::Vector2f(0,-1), sf::Vector2f(1, 1), -90);
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		setUpForMoveDirection(sf::Vector2f(0, 1), sf::Vector2f(1, 1), 90);
	else
		setDirection(sf::Vector2f(0, 0));

	setHowMuchToMove(getDirection(), (getSpeed() +30), deltaTime.asSeconds());
	setLastLocation(getObject().getPosition());
	auto newPosition = sf::Vector2f(getObject().getPosition() + getHowMuchToMove());
	getObject().setPosition(newPosition);
}

void Player::resetToRegular()
{
	m_PlayerState.reset(new RegularState());
	getObject().setTexture(&GameResources::getGameResources().getObjectTexture(PACMAN), true);
}

void Player::setScore(int addPoints)
{
	m_Score += addPoints;
}

//create the life vector - 3 lifes
void Player::createLife()
{
	auto size = sf::Vector2f(40.f, 40.f);
	auto position = sf::Vector2f(1120, 260);
	for (int i = 0; i < 3; i++)
	{
		m_Life.push_back(createShape(size, position));
		m_Life[i].setFillColor(sf::Color::White);
		m_Life[i].setTexture(&GameResources::getGameResources().getObjectTexture(LIFE));
		position.x += 70;
	}
}

void Player::deacreseLife()
{
	m_Life.pop_back();
}

void Player::increseLife()
{
	int i;
	int amount = getAmountOfLife();
	for (i = 0; i < amount; i++);
	m_Life.push_back(createShape(m_Life[i - 1].getSize(), sf::Vector2f(m_Life[i - 1].getPosition().x + 70, m_Life[i - 1].getPosition().y)));
	m_Life[i].setFillColor(sf::Color::White);
	m_Life[i].setTexture(&GameResources::getGameResources().getObjectTexture(LIFE));
}

int Player::getAmountOfLife()
{
	return (int)m_Life.size();
}

void Player::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}

void Player::handleCollision(Demon& gameObject)
{
	m_PlayerState->handleCollision(gameObject, *this);
}

void Player::handleCollision(Wall& gameObject)
{
	getObject().setPosition(getLastLocation());
	GameResources::getGameResources().Playaffect(WALL_S);
}

void Player::handleCollision(Cookie& gameObject)
{
	gameObject.setToDelete();
	setScore(2);
	DataBoard::getDataBoardInstance().setAmountOfCookie(-1);
	GameResources::getGameResources().Playaffect(EATCOOKIE_S);
}

void Player::handleCollision(Key& gameObject)
{
	gameObject.setToDelete();
	setScore(7);
	GameResources::getGameResources().Playaffect(KEY_S);
}

void Player::handleCollision(Gift& gameObject)
{
	if (typeid(SuperGift) == typeid(gameObject))
	{
		gameObject.setToDelete();
		m_PlayerState.reset(new SuperState());
		setScore(5);
		getObject().setTexture(&GameResources::getGameResources().getObjectTexture(SUPER), true);
		TimeManger::getTimeMangerInstance().getSuperTime().restart();
		DataBoard::getDataBoardInstance().setSuperMode();
		GameResources::getGameResources().Playaffect(SUPER_S);
	}
	else if (typeid(FreezeGift) == typeid(gameObject))
	{
		gameObject.setToDelete();
		DataBoard::getDataBoardInstance().setFreezeMode();
		TimeManger::getTimeMangerInstance().getFreezeTime().restart();
		GameResources::getGameResources().Playaffect(FREEZE_S);
	}
	else if (typeid(TimeGift) == typeid(gameObject))
	{
		gameObject.setToDelete();
		TimeManger::getTimeMangerInstance().setTimeLimitSec(20);
		GameResources::getGameResources().Playaffect(TIME_S);
	}
	else if (typeid(LifeGift) == typeid(gameObject))
	{
		if (getAmountOfLife() < 3)
		{
			gameObject.setToDelete();
			setScore(5);
			increseLife();
			GameResources::getGameResources().Playaffect(LIFE_S);
		}
	}
}

void Player::handleCollision(Door& gameObject)
{
	m_PlayerState->handleCollision(gameObject, *this);
}


sf::RectangleShape Player::createShape(sf::Vector2f size, sf::Vector2f position)
{
	auto result = sf::RectangleShape(size);
	result.setFillColor(sf::Color::Black);
	result.setOrigin(result.getSize().x / 2, result.getSize().y / 2);
	result.setPosition(position);

	return result;
}

void Player::restart()
{
	m_Score = 0;
	resetToRegular();
	m_Life.clear();
	createLife();
}





