#pragma once

#include <SFML/Graphics.hpp>

class TimeManger
{
private:
public:
	static TimeManger& getTimeMangerInstance();
	TimeManger(const TimeManger&) = delete;//disable copy constructor
	TimeManger operator=(const TimeManger&) = delete;//disable assimenget operator

	sf::Clock& getLevelTime(); 
	sf::Clock& getTimeMovment();
	//--------LevelTime-------------
	void setTimeLimitMin(int time);
	void setTimeLimitSec(int time);
	void countDownTimer();
	bool gameOver();
	int getMinute() const;
	float getSeconds() const;
	//--------SuperMode-------------
	sf::Clock& getSuperTime();
	void countDownforSuper();
	float getRemainingTimeForSuper() const;
	bool isSuperModeOver();
	//---------FreezeMode------------
	sf::Clock& getFreezeTime();
	void countDownforFreeze();
	float getRemainingTimeForFreeze() const;
	bool isFreezeModeOver();
	void restart();
private:
	//constructor/ distructor
	TimeManger();
	~TimeManger() = default;

	//members
	sf::Clock m_levelTime;
	sf::Clock m_timeMovment;
	sf::Clock m_superTime;//time limit for super pacman
	sf::Clock m_FreezeTime;
	float m_TimeLimitSec;
	int m_timeLimitMin;
	float m_timeLimitForSuper;
	float m_timeLimitForFreeze;

};