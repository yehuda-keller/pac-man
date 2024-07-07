#include "GameObject.h"
#include "GameResources.h"

//constructor
GameObject::GameObject( sf::RectangleShape tile, int wantedTexture)
	:m_object(tile)
{
	setObjectTexture(wantedTexture);
}

//set object texture calls from the cunstructor
void GameObject::setObjectTexture(int wantedTexture)
{
	m_object.setFillColor(sf::Color::White);
	m_object.setTexture(&GameResources::getGameResources().getObjectTexture(wantedTexture));
}

void GameObject::setObject(sf::RectangleShape player)
{
	m_object.setOrigin(player.getOrigin());
	m_object.setPosition(player.getPosition());
	m_object.setSize(player.getSize());
}

//check for collision between the current object and the receiving object
bool GameObject::checkCollision(GameObject& other) const
{
	if (&other == this) return false;
	return m_object.getGlobalBounds().intersects(other.getObject().getGlobalBounds());
}

//get the object(for the rectangle features)
sf::RectangleShape& GameObject::getObject()
{
	return m_object;
}

//draw object
void GameObject::draw(sf::RenderWindow& window)
{
	window.draw(m_object);
}

//resize the object after reading from the level file
//(So that there is no difficulty in moving between objects because of a difference of a single pixel)
void GameObject::setSize(int decrease)
{
	auto temp = sf::Vector2f(getObject().getSize());
	temp.y -= decrease;
	temp.x -= decrease;

	getObject().setSize(temp);
	getObject().setOrigin((temp.x / 2), (temp.y / 2));
}
