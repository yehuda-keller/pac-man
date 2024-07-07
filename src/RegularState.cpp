#include "RegularState.h"
#include "Player.h"
#include "DataBoard.h"
#include "GameResources.h"

//handle collision when the pacman in regular state
void RegularState::handleCollision(Demon& gameObject, Player& player) 
{
	player.deacreseLife();
	player.getObject().setPosition(player.getFirstLocation());
	GameResources::getGameResources().Playaffect(REGCOLDEM_S);
}
//handle collision when the pacman in regular state
void RegularState::handleCollision(Door& gameObject, Player& player)
{
	player.getObject().setPosition(player.getLastLocation());
	GameResources::getGameResources().Playaffect(DOOR_S);
}
