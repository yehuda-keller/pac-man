#pragma once

#include "PacmanState.h"

class RegularState : public PacmanState
{
public:
	RegularState() {}
	~RegularState() = default;

	void handleCollision(Demon& gameObject, Player& player) override;
	void handleCollision(Door& gameObject, Player& player) override;
};