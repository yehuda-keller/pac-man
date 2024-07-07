#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/audio.hpp>
#include "MovingObject.h"
#include "PacmanState.h"
#include "RegularState.h"
#include "SuperState.h"
#include <memory>

class Player : public MovingObject
{
public:
	Player(sf::RectangleShape tile);
	~Player() = default;
	void draw(sf::RenderWindow&);
	void Move(const sf::Time&);
	void resetToRegular();
	void setScore(int);
	void createLife();
	void deacreseLife();
	int getAmountOfLife();
	void increseLife();
	sf::RectangleShape createShape(sf::Vector2f size, sf::Vector2f position);
	void restart();

	//handle collision with double dispatch
	void handleCollision(GameObject& gameObject) override;
	void handleCollision(Player& gameObject) override {}
	void handleCollision(Demon& gameObject) override;
	void handleCollision(Wall& gameObject) override;
	void handleCollision(Cookie& gameObject) override;
	void handleCollision(Key& gameObject) override;
	void handleCollision(Gift& gameObject) override;
	void handleCollision(Door& gameObject) override;
	
private:
	std::unique_ptr<PacmanState> m_PlayerState;
	int m_Score;
	std::vector<sf::RectangleShape> m_Life;
};