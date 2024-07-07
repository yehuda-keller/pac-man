#pragma once

#include "Board.h"
#include <SFML/Graphics.hpp>

class GameBoard: public Board
{
public:
	GameBoard();
	~GameBoard() = default;
	void createBoard() override;
	void createBoradBase() override;
	void createGrid();
	void DrawBoard(sf::RenderWindow&) override;
	void setLevelSize(int, int);
	sf::Vector2i getLevelSize() const;
	sf::RectangleShape getTile(int, int);
	void restart();
private:
	sf::RectangleShape m_gameBaseBoard;
	sf::Vector2i m_LevelSize;
	std::vector < std::vector <sf::RectangleShape> > m_board;
	sf::Vector2f m_BoardTileSize;
};