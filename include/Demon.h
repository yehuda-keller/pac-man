#pragma once

#include <SFML/Graphics.hpp>
#include "MovingObject.h"

class Demon : public MovingObject
{
public:
	Demon(sf::RectangleShape tile, int wantedTexture);
	~Demon() = default;
	
	//handle collision of the demon via double dispatch
	void handleCollision(GameObject& gameObject) override;
	void handleCollision(Player& gameObject) override;
	void handleCollision(Demon& gameObject) override {}
	void handleCollision(Wall& gameObject) override;
	void handleCollision(Cookie& gameObject) override {}
	void handleCollision(Key& gameObject) override {}
	void handleCollision(Gift& gameObject) override {}
	void handleCollision(Door& gameObject) override;

private:
	sf::Vector2f m_direction;
};

enum Direction_t {Left, Right , Up, Down};//enum for direction