#pragma once

#include <string>
#include "vector"
#include <SFML/Graphics.hpp>
#include "helpButton.h"
#include "GameController.h" 

class Menu
{
public:
	//consructor
	explicit Menu();
	~Menu() = default;

	//methods
	void drawMenu();
	void run();
	void handleClick(sf::Vector2f);
private:
	sf::RenderWindow m_window;
	std::vector < sf::Sprite > m_menuButtons;
	helpButton m_helpScreen;
	GameController m_game;
	sf::Music m_menuMusic;
	//func
	void initSprites();

};