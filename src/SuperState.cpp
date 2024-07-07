#include "SuperState.h"
#include "Player.h"
#include "DataBoard.h"
#include "Demon.h"
#include "Door.h"
#include "GameResources.h"

//handle collision when the pacman in super state
void SuperState::handleCollision(Demon& gameObject, Player& player)
{
	gameObject.getObject().setPosition(gameObject.getFirstLocation());
	GameResources::getGameResources().Playaffect(SUPCOLDEM_S);
}

//handle collision when the pacman in super state
void SuperState::handleCollision(Door& gameObject, Player& player)
{
	gameObject.setToDelete();
	GameResources::getGameResources().Playaffect(SUPCOLDOOR_S);
}