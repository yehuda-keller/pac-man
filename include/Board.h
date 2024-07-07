#pragma once

#include <fstream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>

class Board
{
public:
	explicit Board();
	virtual ~Board() = default;
	virtual void createBoard() = 0;
	virtual void createBoradBase() = 0;
	virtual void DrawBoard(sf::RenderWindow &) = 0;
	sf::RectangleShape createShape(sf::Vector2f size, sf::Vector2f position, float);//board
private:
};