#include <chrono>
#include "GameController.h"
#include "Menu.h"
#include "DataBoard.h"
#include "TimeManger.h"
#include <thread>
#include <iostream>

//constructor
GameController::GameController()
    :m_LevelFile("../../../../resources/GameLevelsTxT.txt"), m_amountOfDemons(0),
    m_pacman(std::make_unique<Player>(sf::RectangleShape())), m_backToMenu(false)
{
    initSprite();
}

//run the game function
void GameController::runGame(sf::RenderWindow & window, Menu& menu)
{
     window.setFramerateLimit(60);
     setUpBeforeStart();
     while (window.isOpen() && !m_backToMenu)
     {
         window.clear(sf::Color::Black);
         DrawGame(window);
         window.display();

         //event handle loop
         for (auto event = sf::Event{}; window.pollEvent(event);)
         {
             switch (event.type)
             {
             case sf::Event::Closed:
             {
                 window.close();
                 break;
             }
             case sf::Event::KeyPressed:
             {
                 if (event.key.code == sf::Keyboard::Escape)
                     window.close();
                 break;
             }
             case sf::Event::MouseButtonReleased:
             {
                 auto location = window.mapPixelToCoords(
                     { event.mouseButton.x, event.mouseButton.y });
                 DataBoard::getDataBoardInstance().handleMouseClick(location, menu, *this, window);
             }
             }

         }
         updateGameProcess();
         checkLevelStatus(window);
     }
     restart();
     m_backToMenu = false;
     menu.run();
}

//Making preparations before the start of the game
void GameController::setUpBeforeStart()
{
    restartTimers();
    DataBoard::getDataBoardInstance().createBoard();
    readLevelSize();
    createLevel();
    GameResources::getGameResources().Playaffect(INTRO_S);
}

//create level 
void GameController::createLevel()
{
    m_GameBoard.createBoard();
    readFromFile();
}

//draw game
void GameController::DrawGame(sf::RenderWindow& window)
{
    window.draw(m_background[BACKGROUND]);//draw the game background
    m_GameBoard.DrawBoard(window);//draw game board
    DataBoard::getDataBoardInstance().DrawBoard(window);//draw data board
    m_pacman->draw(window);//draw the player
    //draw the moving object(demons)
    for (int i = 0; i < (int)m_Demons.size(); i++)
        m_Demons[i]->draw(window);
    //draw the static object
    for (int i = 0; i < (int)m_staticObject.size(); i++)
        m_staticObject[i]->draw(window);
}

//get the level size from file
bool GameController::readLevelSize()
{
    if (!m_LevelFile.is_open())
         std::cout << "not open";
    std::string temp;
    std::getline(m_LevelFile, temp);
    if (temp == "")
        return false;
    std::istringstream iss(temp);
    int height, width, time;
    iss >> width;
    iss >> height;
    iss >> time;
    m_GameBoard.setLevelSize(width, height);
    TimeManger::getTimeMangerInstance().setTimeLimitMin(time);
    return true;
}

//read the game map from file
void GameController::readFromFile()
{
    char read;
    auto levelSize = sf::Vector2f(m_GameBoard.getLevelSize());
    for (int row = 0; row < levelSize.y; row++)
    {
        for (int col = 0; col <= levelSize.x; col++)
        {
            read = m_LevelFile.get();
            if (read == '$')
                m_staticObject.push_back(std::make_unique<SuperGift>(m_GameBoard.getTile(row, col)));
            else if (read == '%')
                m_staticObject.push_back(std::make_unique<Key>(m_GameBoard.getTile(row, col)));
            else if (read == '!')
                m_staticObject.push_back(std::make_unique<FreezeGift>(m_GameBoard.getTile(row, col)));
            else if (read == '?')
                m_staticObject.push_back(std::make_unique<TimeGift>(m_GameBoard.getTile(row, col)));
            else if (read == '@')
                m_staticObject.push_back(std::make_unique<LifeGift>(m_GameBoard.getTile(row, col)));
            else if (read == 'a')
            {
                m_pacman->setObject(m_GameBoard.getTile(row, col));
                m_pacman->setFirstLocation(m_GameBoard.getTile(row, col).getPosition());
            }
            else if (read == '&')
            {
                m_amountOfDemons++;
                if(m_amountOfDemons % 2 != 0)
                    m_Demons.push_back(std::make_unique<RandomDemon>(m_GameBoard.getTile(row, col)));
                else
                    m_Demons.push_back(std::make_unique<SmartDemon>(m_GameBoard.getTile(row, col), m_pacman.get()));
            }
            else if (read == '#')
                m_staticObject.push_back(std::make_unique<Wall>(m_GameBoard.getTile(row, col)));
            else if (read == 'D')
                m_staticObject.push_back(std::make_unique<Door>(m_GameBoard.getTile(row, col)));
            else if (read == '*')
            {
                m_staticObject.push_back(std::make_unique<Cookie>(m_GameBoard.getTile(row, col)));
                DataBoard::getDataBoardInstance().setAmountOfCookie(1);
            }
            else if (read == ' ')
                continue;
        }
        read = m_LevelFile.get();
    }
    resize();
}

//responsible on the game process
void GameController::updateGameProcess()
{
    const auto deltaTime = TimeManger::getTimeMangerInstance().getTimeMovment().restart();
    TimeManger::getTimeMangerInstance().countDownTimer();
    MoveAndCollideHandler(deltaTime);
    GameEventHandler();
   std::erase_if(m_staticObject, [](const auto& staticObject)
   {
       return staticObject -> getToDelete();
   });

}

//perform the moving objects methods(move, collide)
void GameController::MoveAndCollideHandler(sf::Time deltaTime)
{
    m_pacman->Move(deltaTime);
    handleCollisions(*m_pacman);
    for (auto& movable : m_Demons)
    {
        movable->Move(deltaTime);
        handleCollisions(*movable);
    }
}

//Responsible for making updates of events that happen during the game
void GameController::GameEventHandler()
{
    if (DataBoard::getDataBoardInstance().getSuperMode())
        TimeManger::getTimeMangerInstance().countDownforSuper();
    if (DataBoard::getDataBoardInstance().getFreezeMode())
        TimeManger::getTimeMangerInstance().countDownforFreeze();
    syncBetweenDoorToKey();//check if key need to open door
    checkGiftMode();
}

//handle collision between objects
void GameController::handleCollisions(GameObject& gameObject)
{
    for (auto& unmovable : m_staticObject)
    {
        if (gameObject.checkCollision(*unmovable))
        {
            gameObject.handleCollision(*unmovable);
        }
    }

    for (auto& movable : m_Demons)
    {
        if (gameObject.checkCollision(*movable))
        {
            gameObject.handleCollision(*movable);
        }
    }
}



//when we do restart or finish the game
//we need to erase every data member before we read the new data
void GameController::restart()
{
    m_pacman->restart();
    m_LevelFile.seekg(0);
    m_GameBoard.restart();
    m_Demons.clear();
    m_staticObject.clear();
    DataBoard::getDataBoardInstance().restartData();
    restartTimers();
    TimeManger::getTimeMangerInstance().restart();
    m_amountOfDemons = 0;
}

//resize the objects size
void GameController::resize()
{
    m_pacman->setSize(4);
    for (auto& movable : m_Demons)
        movable->setSize(4);
    for (auto& unmovable : m_staticObject)
        unmovable->setSize(2);
}

//init the textures for the Transition Screens
void GameController::initSprite()
{
    for (int i = 0; i < 4; i++)
    {
        auto temp = sf::Sprite(GameResources::getGameResources().getTransitionScreens(i));
        temp.setPosition(sf::Vector2f(700, 400));
        temp.setOrigin(sf::Vector2f(GameResources::getGameResources().getTransitionScreens(i).getSize() / 2u));
        m_background.push_back(temp);
    }
   m_background[BACKGROUND].setScale(0.75, 1);
   
}

//this function responsible to check if the player lost the game/move to the next level/finish the game
//and makes the required updates for each situation
void GameController::checkLevelStatus(sf::RenderWindow& window)
{
    if (DataBoard::getDataBoardInstance().getAmountOfCookies() == 0)//next level
    {
        setUpForNextLevel();
        if (readLevelSize())//next level
        {
            setUpForTransitionScreens(window, NEXTLEVEL_S, NEXTLEVEL, 2);
            createLevel();
            restartTimers();
        }
        else//end game
        {
            setUpForTransitionScreens(window, NEXTLEVEL_S, ENDGAME, 5);
            DataBoard::getDataBoardInstance().restartData();
            m_backToMenu = true;
        }
    }
    if (TimeManger::getTimeMangerInstance().gameOver() || m_pacman->getAmountOfLife() == 0)//game over
    {
        setUpForTransitionScreens(window, GAMEOVER_S, GAMEOVER, 3);
        DataBoard::getDataBoardInstance().restartData();
        m_backToMenu = true;
    }
}

//Making preparations before the next level
void GameController::setUpForNextLevel()
{
    m_pacman->resetToRegular();
    m_GameBoard.restart();
    m_Demons.clear();
    m_staticObject.clear();
    restartTimers();
    TimeManger::getTimeMangerInstance().restart();
    m_pacman->setScore(50 + (2 * m_amountOfDemons));
    DataBoard::getDataBoardInstance().nextLevel();
    m_amountOfDemons = 0;
}

//perform the display of the transition screens
void GameController::setUpForTransitionScreens(sf::RenderWindow& window, int affectNumber, int screenNumber, int sleepTime)
{
    GameResources::getGameResources().Playaffect(affectNumber);
    window.clear();
    window.draw(m_background[screenNumber]);
    window.display();
    std::this_thread::sleep_for(std::chrono::seconds(sleepTime));
}

//reset timers
void GameController::restartTimers()
{
    TimeManger::getTimeMangerInstance().getLevelTime().restart();
    TimeManger::getTimeMangerInstance().getTimeMovment().restart();
}

void GameController::setBackToMenu()
{
    m_backToMenu = !m_backToMenu;
}





