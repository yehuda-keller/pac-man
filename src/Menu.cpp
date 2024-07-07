#include "Menu.h"
#include "GameResources.h"

//constructor
Menu::Menu()
	:m_window(sf::VideoMode(1400,800),"packman")
{
    initSprites();
    m_menuMusic.openFromFile("../../../../resources/menuBackground.wav");
    m_menuMusic.setLoop(true);
}

//run the program as long as the window is open  
void Menu::run()
{
    m_menuMusic.play();
    while (m_window.isOpen())
    {
        m_window.clear(sf::Color::Black);
        drawMenu();
        m_window.display();

        if (auto event = sf::Event{}; m_window.waitEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_window.close();
                break;

            case sf::Event::MouseButtonReleased:
            {
                auto location = m_window.mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });
                handleClick(location);
                break;
            }
            }
        }
    }
}

//define which operation to execute when there is a mouse click on the buttuns
void Menu::handleClick(sf::Vector2f location)
{
    //play buttun
    if (m_menuButtons[2].getGlobalBounds().contains(location))
    {
        m_menuMusic.stop();
        m_game.runGame(this ->m_window, *this);
    }
    //help buttun
    else if ((m_menuButtons[3].getGlobalBounds().contains(location)))
    {
         m_helpScreen.HandleMouseClick(this->m_window, *this);
    }
    //exit buttun
    else if ((m_menuButtons[4].getGlobalBounds().contains(location)))
    {
        m_menuMusic.stop();
        m_window.close();
    }
    else if ((m_menuButtons[5].getGlobalBounds().contains(location)))
    {
        if (m_menuMusic.getStatus() == sf::Music::Paused)
            m_menuMusic.play();
        else if (m_menuMusic.getStatus() == sf::Music::Playing)
            m_menuMusic.pause();
    }
       
}

//this function responsible to create the vector which holds the sprites for the menu page.
void Menu::initSprites()
{
    for (int i = 0; i < 6; i++)
    {
        auto result = sf::Sprite(GameResources::getGameResources().getMenuTexture(i));
        result.setPosition(sf::Vector2f(700, 150 + (130*(float)i)));
        result.setOrigin(sf::Vector2f(result.getTexture()->getSize() / 2u));
        m_menuButtons.push_back(result);
    }
    auto result = sf::Sprite(GameResources::getGameResources().getMenuTexture(8));
    result.setPosition(sf::Vector2f(700,400));
    result.setOrigin(sf::Vector2f(result.getTexture()->getSize() / 2u));
    result.setScale(1, 0.9);
    m_menuButtons.push_back(result);
    m_menuButtons[5].setPosition(sf::Vector2f(100, 700));
}

void Menu::drawMenu()
{
    m_window.draw(m_menuButtons[6]);
    //draw the menu on the window
    for (int i = 0; i < 6; i++)
        m_window.draw(m_menuButtons[i]);

    //draw the project creators names on the window 
   m_window.draw(GameResources::getGameResources().createText("Yehuda Keller Pacman Game", sf::Vector2f(700, 760), sf::Color::Yellow, 0));
}