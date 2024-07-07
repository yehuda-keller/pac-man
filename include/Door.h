#pragma once

#include <SFML/Graphics.hpp>
#include "StaticObject.h"

class Door : public StaticObject
{
public:
	Door(sf::RectangleShape tile);
	~Door() = default;
	
	//handle the collisions with the door via double dispatch
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