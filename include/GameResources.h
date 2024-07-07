#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/audio.hpp>
class GameResources
{
public:
	static GameResources& getGameResources();
	GameResources(const GameResources&) = delete;//disable copy constructor
	GameResources operator=(const GameResources&) = delete;//disable assimenget operator
	sf::Texture& getMenuTexture(int index);
	sf::Texture& getObjectTexture(int index) ;
	sf::Texture& getDataButtuns(int index) ;
	sf::Texture& getTransitionScreens(int index) ;
	sf::Font& getFont(int index);
	sf::Sound& Playaffect(int index);
	sf::Text& createText(std::string, sf::Vector2f, sf::Color, int);
private:
	//constructor/ distructor
	GameResources();
	~GameResources() = default;

	//members
	std::vector <sf::Texture > m_menuTexture;
	std::vector <sf::Texture > m_objectTexture;
	std::vector <sf::Texture > m_transitionScreens;
	std::vector <sf::Texture > m_databuttons;
	std::vector <sf::Font> m_font;
	std::vector <sf::SoundBuffer> m_affects;

	sf::Sound m_affect;
	sf::Text m_text;
	//func
	void initTextures();
	void initFonts();
	void initSounds();
};


enum object_t {PACMAN, DEMON, WALL, KEY, DOOR , GIFT, COOKIE, LIFE, FREEZE, TIME, SUPER, SMART};
enum data_t {BACK, RESTART, EXIT};
enum screens_t {BACKGROUND, GAMEOVER, NEXTLEVEL, ENDGAME};
enum sounds_t {EATCOOKIE_S, GAMEOVER_S, LIFE_S, INTRO_S, DOOR_S, KEY_S, NEXTLEVEL_S, SUPER_S, TIME_S, WALL_S, FREEZE_S, REGCOLDEM_S,SUPCOLDEM_S, SUPCOLDOOR_S };