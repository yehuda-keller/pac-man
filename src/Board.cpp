#include "Board.h"

Board::Board()
{}

//create the shape - rectangle 
//using this func when we create the grid, the boards bases(game board and data board)
sf::RectangleShape Board::createShape(sf::Vector2f size, sf::Vector2f position ,float thicnes)
{
    auto result = sf::RectangleShape(size);
    result.setFillColor(sf::Color::Black);
    result.setOutlineColor(sf::Color(180,100, 100, 255));
    result.setOutlineThickness(thicnes);
    result.setOrigin(result.getSize().x / 2, result.getSize().y / 2);
    result.setPosition(position);

    return result;
}
