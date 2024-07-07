#include "TimeManger.h"

TimeManger& TimeManger::getTimeMangerInstance()
{
	static TimeManger tmange;
	return tmange;
}

//get the clock of the level
sf::Clock& TimeManger::getLevelTime()
{
	return m_levelTime;
}

//get the clock for movment
sf::Clock& TimeManger::getTimeMovment()
{
	return m_timeMovment;
}

//set the minutes member 
void TimeManger::setTimeLimitMin(int time)
{
	m_timeLimitMin = --time;
}

//update the remaning time with seconds
//called when the player take time present
void TimeManger::setTimeLimitSec(int time)
{
	m_TimeLimitSec += time;
	if (m_TimeLimitSec >= 60)
	{
		m_timeLimitMin++;
		m_TimeLimitSec -= 60;
	}
}

//timer for the level
void TimeManger::countDownTimer()
{
	if ((int)m_TimeLimitSec == 0)
	{
		m_timeLimitMin--;
		m_TimeLimitSec = 60.0;
	}

	sf::Time elapsed = TimeManger::getTimeMangerInstance().getLevelTime().restart();
	m_TimeLimitSec -= (elapsed.asSeconds() / 1.5);
}

//get the clock for super
sf::Clock& TimeManger::getSuperTime()
{
	 return m_superTime;
}

//get the clock for freeze
sf::Clock& TimeManger::getFreezeTime()
{
	return m_FreezeTime;
}

//get the minutes
int TimeManger::getMinute() const
{
	return m_timeLimitMin;
}

//get seconds
float TimeManger::getSeconds() const
{
	return m_TimeLimitSec;
}

//count down for super mode
void TimeManger::countDownforSuper()
{
	sf::Time elapsed = getSuperTime().restart();
	m_timeLimitForSuper -= (elapsed.asSeconds() / 1.5);
}

//check if the super mode over
bool TimeManger::isSuperModeOver()
{
	if ((int)m_timeLimitForSuper == 0)
	{
		m_timeLimitForSuper = 30;
		return true;
	}

	return false;
}

//check if game over(times up)
bool TimeManger::gameOver()
{
	if ((int(m_TimeLimitSec) == 0 && m_timeLimitMin == 0))//if time is over
		return true;

	return false;
}

//get the super timer
float TimeManger::getRemainingTimeForSuper() const
{
	return m_timeLimitForSuper;
}

//count down for 
void TimeManger::countDownforFreeze()
{
	sf::Time elapsed = getFreezeTime().restart();
	m_timeLimitForFreeze -= (elapsed.asSeconds() / 1.5);
}

//check if the freeze mode over
bool TimeManger::isFreezeModeOver()
{
	if ((int)m_timeLimitForFreeze == 0)
	{
		m_timeLimitForFreeze = 10;
		return true;
	}

	return false;
}

//get the freeze timer
float TimeManger::getRemainingTimeForFreeze() const
{
	return m_timeLimitForFreeze;
}

//reset tumers and members
void TimeManger::restart()
{
	m_TimeLimitSec = 60.f;
	m_timeLimitForSuper = 30.f;
	m_timeLimitForFreeze = 10.f;
}

//constructor
TimeManger::TimeManger()
	: m_TimeLimitSec(60), m_timeLimitMin(0), m_timeLimitForSuper(30), m_timeLimitForFreeze(10)
{}
