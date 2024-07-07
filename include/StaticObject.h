#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"

class MovingObject;

class StaticObject : public GameObject
{
public:
	StaticObject( sf::RectangleShape tile, int wantedTexture)
		:m_toDelete(false), GameObject(tile, wantedTexture)
	{}
	virtual ~StaticObject() = default;
	void setToDelete() { m_toDelete = !m_toDelete; }
	bool getToDelete() const { return m_toDelete; }
	virtual void handleCollision(GameObject& gameObject) override {}
	virtual void handleCollision(Player& gameObject) override {}
	virtual void handleCollision(Demon& gameObject) override {}
	virtual void handleCollision(Wall& gameObject) override {}
	virtual void handleCollision(Cookie& gameObject) override {}
	virtual void handleCollision(Key& gameObject) override {}
	virtual void handleCollision(Gift& gameObject) override {}
	virtual void handleCollision(Door& gameObject) override {}

private:
	bool m_toDelete;

};