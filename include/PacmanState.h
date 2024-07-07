#pragma once

class Player;
class Demon;
class Door;

class PacmanState
{
public:
	PacmanState() {}
	~PacmanState() = default;
	
	virtual void handleCollision(Demon& gameObject, Player& player) = 0;
	virtual void handleCollision(Door& gameObject, Player& player) = 0;

};