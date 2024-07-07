#pragma once

#include <SFML/Graphics.hpp>

class Player;
class Demon;
class Wall;
class Cookie;
class Key;
class Gift;
class Door;

class GameObject 
{
public:
	GameObject(sf::RectangleShape tile, int wantedTexture);
	virtual ~GameObject() = default;
	virtual void draw(sf::RenderWindow &);
	void setObjectTexture(int wantedTexture);
	void setObject(sf::RectangleShape);
    bool checkCollision(GameObject& other) const;
    sf::RectangleShape& getObject();
	void setSize(int decrease);
	
	virtual void handleCollision(GameObject& gameObject) = 0;
	virtual void handleCollision(Player& gameObject) = 0;
	virtual void handleCollision(Demon& gameObject) = 0;
	virtual void handleCollision(Wall& gameObject) = 0;
	virtual void handleCollision(Cookie& gameObject) = 0;
	virtual void handleCollision(Key& gameObject) = 0;
	virtual void handleCollision(Gift& gameObject) = 0;
	virtual void handleCollision(Door& gameObject) = 0;

private:
	sf::RectangleShape m_object;
	
};