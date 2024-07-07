#include "GameResources.h"

//constructor
GameResources::GameResources()
{
    initTextures();
    initFonts();
    initSounds();
}

//static func - singelton class
//return intance to the class
GameResources& GameResources::getGameResources()
{
    static GameResources resources;
    return resources;
}

//get the textures for the menu window
sf::Texture& GameResources::getMenuTexture(int index) 
{
    if (index < 9 && index >= 0)
        return m_menuTexture[index];
}

//get the textures for the game objects
sf::Texture& GameResources::getObjectTexture(int index) 
{
    if (index < 19 && index >= 0)
        return m_objectTexture[index];
}

//get the textures for the data board buttons
sf::Texture& GameResources::getDataButtuns(int index)
{
    if (index < 3 && index >= 0)
        return m_databuttons[index];
}

//get the textures for the transitions screens
sf::Texture& GameResources::getTransitionScreens(int index)
{
    if (index < 4 && index >= 0)
        return m_transitionScreens[index];
}

//get font
sf::Font& GameResources::getFont(int index) 
{
    if (index < 2 && index >= 0)
        return m_font[index];
}

//play a wanted affect
sf::Sound& GameResources::Playaffect(int index)
{
    if (index < 14 && index >= 0)
    {
        m_affect.setBuffer(m_affects[index]);
        m_affect.play();
        return m_affect;
    }
}

//create the text 
sf::Text& GameResources::createText(std::string dataName, sf::Vector2f position , sf::Color color , int font)
{
    m_text.setString(dataName);
    m_text.setFont(getFont(font));
    m_text.setPosition(position);
    const auto rect = m_text.getLocalBounds();
    m_text.setOrigin(rect.width / 2, rect.height / 2);
    m_text.setCharacterSize(30);
    m_text.setFillColor(color);
    m_text.setStyle(sf::Text::Bold);
    return m_text;
}



//load the texture for the game
void GameResources::initTextures()
{
    //---------------------------menu textures-----------------------------
    //all the texture images names for menu
    char menuTextureNames[9][50] = { "../../../../resources/pacmanTitle.png",
                                     "../../../../resources/pacmanEmoji.png",
                                     "../../../../resources/playButton.png",
                                     "../../../../resources/helpButton.png",
        "../../../../resources/exitButton.png",
        "../../../../resources/musicButton.png",
        "../../../../resources/help.png",
        "../../../../resources/backButton.png",
        "../../../../resources/MenuBackground.png"};

    //init texture vector for menu
    for (int i = 0; i < 9; i++)
    {
        sf::Texture name;
        name.loadFromFile(menuTextureNames[i]);
        m_menuTexture.push_back(name);
    }
    //---------------------------gameObject textures-----------------------------
    //all the texture images names for game objects
    char objectTextureNames[12][50] = { "../../../../resources/pacman.png",
                                        "../../../../resources/ghost.png",
                                        "../../../../resources/wall.png",
                                        "../../../../resources/key.png",
                                        "../../../../resources/door.png",
                                        "../../../../resources/gift.png",
                                        "../../../../resources/cookie.png",
                                        "../../../../resources/Life.png",
                                        "../../../../resources/freeze.png",
                                        "../../../../resources/time.png",
                                        "../../../../resources/superPacman.png",
                                        "../../../../resources/smartDemon.png"};

    //init texture vector for menu
    for (int i = 0; i < 12; i++)
    {
        sf::Texture name;
        name.loadFromFile(objectTextureNames[i]);
        m_objectTexture.push_back(name);
    }
    //---------------------------screens textures-----------------------------
    //all the texture images names for transition screens
    char screenTextureNames[4][50] = {"../../../../resources/pacmanBackground.png",
                                      "../../../../resources/GameOver.png",
                                      "../../../../resources/NextLevel.png",
                                      "../../../../resources/endGame.png"};

    //init texture vector for menu
    for (int i = 0; i < 4; i++)
    {
        sf::Texture name;
        name.loadFromFile(screenTextureNames[i]);
        m_transitionScreens.push_back(name);
    }
    //---------------------------dataButtuns textures-----------------------------
    //all the texture images names for game objects
    char dataButtunsNames[3][50] = { "../../../../resources/backToMenu.png" ,
                                     "../../../../resources/restartButtun.png" ,
                                     "../../../../resources/exitFromLevel.png" };
                                        
    //init texture vector for menu
    for (int i = 0; i < 3; i++)
    {
        sf::Texture name;
        name.loadFromFile(dataButtunsNames[i]);
        m_databuttons.push_back(name);
    }
}

//load the fonts for the game
void GameResources::initFonts()
{
    char fontsPath[2][50] = { "../../../../resources/Arial.ttf" ,"../../../../resources/Arial.ttf" };
    for (int i = 0; i < 2; i++)
    {
        sf::Font temp;
        temp.loadFromFile(fontsPath[i]);
        m_font.push_back(temp);
    }
}

//load the sounds for the game
void GameResources::initSounds()
{
    char affectsNames[14][50] = { "../../../../resources/pacmanEatingCookie.wav" ,
                                  "../../../../resources/pacmanGameOver.wav" ,
                                  "../../../../resources/pacmanGetingLife.wav" ,
                                  "../../../../resources/pacmanOpening.wav",
                                  "../../../../resources/door.wav" ,
                                  "../../../../resources/key.wav",
                                  "../../../../resources/NextLevel.wav",
                                  "../../../../resources/superGift.wav" ,
                                  "../../../../resources/timeGift.wav",
                                  "../../../../resources/wall.wav",
                                  "../../../../resources/freezeTime.wav" ,
                                   "../../../../resources/playerColideWithDemon.wav",
                                   "../../../../resources/superColideWithDemon.wav" ,
                                   "../../../../resources/superColideWithDoor.wav" };
    for (int i = 0; i < 14; i++)
    {
        sf::SoundBuffer temp;
        temp.loadFromFile(affectsNames[i]);
        m_affects.push_back(temp);
    }
}