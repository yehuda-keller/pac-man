#pragma once

#include <SFML/Graphics.hpp>

class Menu;

class helpButton
{
public:
	helpButton();
	void HandleMouseClick(sf::RenderWindow& window, Menu& menu);
	void drawHelpScreen(sf::RenderWindow& window);
private:
	//members
	std::vector < sf::Sprite > m_Sprites;
	bool m_backToMenu;
	//func
	void initSprites();
};