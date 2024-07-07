#pragma once

#include "PacmanState.h"
#include "DataBoard.h"
#include "Door.h"

class SuperState : public PacmanState
{
public:
	SuperState() {}
	~SuperState() = default;

	void handleCollision(Demon& gameObject, Player& player) override;
	void handleCollision(Door& gameObject, Player& player) override;
};