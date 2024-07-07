#pragma once

#include "Board.h"
#include <SFML/Graphics.hpp>
#include "GameResources.h"

class Menu;
class GameController;

class DataBoard : public Board
{
public:
	static DataBoard& getDataBoardInstance();
	DataBoard(const DataBoard&) = delete;//disable copy constructor
	DataBoard operator=(const DataBoard&) = delete;//disable assimenget operator
	void setAmountOfCookie(int value);
	int getAmountOfCookies();
	void createBoard() override;
	void createBoradBase() override;
	void DrawBoard(sf::RenderWindow&) override;
	void drawTimers(sf::RenderWindow&);
	void createButtuns();
	void createData();
	void restartData();
	void nextLevel();
	//------------for super----------------
	void setSuperMode();
	bool getSuperMode() const;
	//-----------for freeze-------------------
	void setFreezeMode();
	bool getFreezeMode() const;
	void handleMouseClick(sf::Vector2f position, Menu& menu, GameController& controller, sf::RenderWindow& window);

private:
	//constructor/ distructor
	DataBoard();
	
	//members
	sf::RectangleShape m_dataBaseBoard;
	std::vector <sf::RectangleShape> m_dataButtons;
	std::vector <sf::Text> m_data;
	int m_amountCookies;
	int m_Level;
	bool m_superMode;
	bool m_freeze;
};