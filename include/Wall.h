#pragma once

#include <SFML/Graphics.hpp>
#include "StaticObject.h"

class Wall : public StaticObject
{
public:
	Wall(sf::RectangleShape tile);
	~Wall() = default;
	
	//double dispatch to handle collision
	void handleCollision(GameObject& gameObject) override;
	void handleCollision(Player& gameObject) override;
	void handleCollision(Demon& gameObject) override;
	void handleCollision(Wall& gameObject) override {}
	void handleCollision(Cookie& gameObject) override {}
	void handleCollision(Key& gameObject) override {}
	void handleCollision(Gift& gameObject) override {}
	void handleCollision(Door& gameObject) override {}
private:
};