#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Board.h"
#include "MovingObject.h"
#include "StaticObject.h"
#include "Player.h"
#include "Demon.h"
#include "GameResources.h"
#include "Key.h"
#include "Door.h"
#include "Cookie.h"
#include "Gift.h"
#include "Wall.h"
#include "GameBoard.h"
#include "FreezeGift.h"
#include "SuperGift.h"
#include "TimeGift.h"
#include "LifeGift.h"
#include "RandomDemon.h"
#include "SmartDemon.h"
#include <iostream>
#include <fstream>
#include <sstream>

class Menu;

class GameController
{
public:
	explicit GameController();
	void runGame(sf::RenderWindow& window, Menu& menu);
	void setUpBeforeStart();
	void createLevel();
	bool readLevelSize();
	void readFromFile();
	void DrawGame(sf::RenderWindow& window);
	void updateGameProcess();
	void MoveAndCollideHandler(sf::Time);
	void GameEventHandler();
	void handleCollisions(GameObject& gameObject);
	void restart();
	void resize();
	void syncBetweenDoorToKey();
	void checkGiftMode();
	void checkLevelStatus(sf::RenderWindow& window);
	void setUpForNextLevel();
	void setUpForTransitionScreens(sf::RenderWindow& window, int affectNumber, int screenNumber, int sleepTime);
	void restartTimers();
	void setBackToMenu();
private:
	//members
	std::ifstream m_LevelFile;
	GameBoard m_GameBoard;
	std::vector <std::unique_ptr<Demon>> m_Demons;
	std::vector <std::unique_ptr<StaticObject>> m_staticObject;
    std::vector< sf::Sprite> m_background;
	int m_amountOfDemons;
	std::unique_ptr<Player> m_pacman;
	bool m_backToMenu;
	//func
	void initSprite();
};