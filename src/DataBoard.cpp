#include "DataBoard.h"
#include "Menu.h"
#include "TimeManger.h"

DataBoard::DataBoard()
    :m_Level(1), m_amountCookies(0), m_superMode(false), m_freeze(false)
{}

DataBoard& DataBoard::getDataBoardInstance()
{
    static DataBoard dataBoard;
    return dataBoard;
}

//set amount of coockies
void DataBoard::setAmountOfCookie(int value)
{
    m_amountCookies+=value;
}

//get amount of coockies
int DataBoard::getAmountOfCookies()
{
    return m_amountCookies;
}

//create the data board
void DataBoard::createBoard()
{
    //if its the first timme create the data board
    //security way because its singelton
    static int times = 0;
    times++;
    if (times == 1)
    {
        createBoradBase();
        createButtuns();
        createData();
    }
}

//create the data board frame
void DataBoard::createBoradBase()
{
    auto size = sf::Vector2f(300, 700);
    auto position = sf::Vector2f(1200, 400);//the center of the area for the data board
    m_dataBaseBoard = createShape(size, position,10);
}

//draw data board
void DataBoard::DrawBoard(sf::RenderWindow& window)
{
    window.draw(m_dataBaseBoard);//draw frame

    for (int i = 0; i < 3; i++)//draw buttuns
         window.draw(m_dataButtons[i]);

    for (int i = 0; i < 4; i++)//draw the text(e.g Score)
        window.draw(m_data[i]);

    //draw the level number
    window.draw(GameResources::getGameResources().createText(std::to_string(m_Level), sf::Vector2f(1200, 150), sf::Color::White,1));
    drawTimers(window);
}

//draw the timers of the game on the data board 
void DataBoard::drawTimers(sf::RenderWindow& window)
{
    //draw the time limit for the game
    window.draw(GameResources::getGameResources().createText(std::to_string(TimeManger::getTimeMangerInstance().getMinute()),
        sf::Vector2f(1165, 450), sf::Color::White, 1));//minuts
    window.draw(GameResources::getGameResources().createText(":", sf::Vector2f(1195, 445), sf::Color::White, 1));
    window.draw(GameResources::getGameResources().createText(std::to_string((int)TimeManger::getTimeMangerInstance().getSeconds()),
        sf::Vector2f(1240, 450), sf::Color::White, 1));//seconds

    if (m_superMode)//timer for the time limit of the super state
    {
        window.draw(GameResources::getGameResources().createText("Super Mode:", sf::Vector2f(1200, 500), sf::Color::Yellow, 1));
        window.draw(GameResources::getGameResources().createText(std::to_string((int)TimeManger::getTimeMangerInstance().getRemainingTimeForSuper()), 
                    sf::Vector2f(1200, 530), sf::Color::White, 1));
    }
    if (m_freeze)//timer for the time limit of the freeze
    {
        window.draw(GameResources::getGameResources().createText("Freeze Time:", sf::Vector2f(1200, 600), sf::Color::Yellow, 1));
        window.draw(GameResources::getGameResources().createText(std::to_string((int)TimeManger::getTimeMangerInstance().getRemainingTimeForFreeze()),
                    sf::Vector2f(1200, 630), sf::Color::White, 1));
    }
}

//create the buttuns on the data board
void DataBoard::createButtuns()
{
    auto size = sf::Vector2f(60.f, 60.f);
    auto position = sf::Vector2f(1100,700);
    for (int i = 0; i < 3; i++)
    {
        m_dataButtons.push_back(createShape(size, position, 0));
        m_dataButtons[i].setFillColor(sf::Color::White);
        m_dataButtons[i].setTexture(&GameResources::getGameResources().getDataButtuns(i));
        position.x += 100;
    }
}

//create the data strings
void DataBoard::createData()
{
    char dataNames[4][20] = { "Level: ", "Life: ","Score: ", "Time Left: " };
    auto position = sf::Vector2f(1200, 100);
    for (int i = 0; i < 4; i++)
    {
        m_data.push_back(GameResources::getGameResources().createText(dataNames[i], position, sf::Color(180, 100, 100, 255),1));
        position.y += 100;
    }
}

//reset the data in case of restart or finish the game
void DataBoard::restartData()
{
    if (getSuperMode())
        setSuperMode();
    if (getFreezeMode())
        setFreezeMode();
    m_amountCookies = 0;
    m_Level = 1;
}

//set up of the data board for the next level
void DataBoard::nextLevel()
{
    m_amountCookies = 0;
    m_Level++;
    m_superMode = false;
    m_freeze = false;
}

//change the current state of this member
void DataBoard::setSuperMode()
{
    m_superMode = !m_superMode;
}

//get the status of this member
bool DataBoard::getSuperMode() const
{
    return m_superMode;
}

//change the current state of this member
void DataBoard::setFreezeMode()
{
    m_freeze = !m_freeze;
}

//get the status of this member
bool DataBoard::getFreezeMode() const
{
    return m_freeze;
}

//handle click when there is mouse click on some data buttun 
void DataBoard::handleMouseClick(sf::Vector2f position, Menu& menu, GameController& controller, 
                                 sf::RenderWindow& window)
{
    //if its back to menu buttun
    if (m_dataButtons[BACK].getGlobalBounds().contains(position))
        controller.setBackToMenu();
    //if its restart game buttun
    if(m_dataButtons[RESTART].getGlobalBounds().contains(position))
    {
        controller.restart();
        controller.readLevelSize();
        controller.createLevel();
    }
    //if its exit from game buttun
    if (m_dataButtons[EXIT].getGlobalBounds().contains(position))
        window.close();
}
