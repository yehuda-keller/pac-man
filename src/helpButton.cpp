#include "helpButton.h"
#include "Menu.h"

//constructor
helpButton::helpButton()
    :m_backToMenu(false)
{
    initSprites();
}

//wait until there is a click in the buttun
void helpButton::HandleMouseClick(sf::RenderWindow& window, Menu& menu) 
{
    while (window.isOpen() && !m_backToMenu)
    {
        window.clear(sf::Color::Black);
        drawHelpScreen(window);
        window.display();

        if (auto event = sf::Event{}; window.waitEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonReleased:
            {
                auto location = window.mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });
                if (m_Sprites[1].getGlobalBounds().contains(location))
                    m_backToMenu = true;
                break;
            }
            }
            
        }
    }
    m_backToMenu = false;
    menu.run();
}

void helpButton::drawHelpScreen(sf::RenderWindow& window)
{
    //draw the help screen on the window
    for (int i = 0; i < 2; i++)
        window.draw(m_Sprites[i]);
}

//initiliza the sprites for the help screen
void helpButton::initSprites()
{
    for (int i = 6; i < 8; i++)
    {
        auto result = sf::Sprite(GameResources::getGameResources().getMenuTexture(i));
        result.setOrigin(sf::Vector2f(result.getTexture()->getSize() / 2u));
        m_Sprites.push_back(result);
    }
    m_Sprites[0].setPosition(sf::Vector2f(700, 400));
    m_Sprites[1].setPosition(sf::Vector2f(80, 720));
}

