#include "GameController.h"
#include "TimeManger.h"

//check if player take a key, if it happend set a random dorr to delete
void GameController::syncBetweenDoorToKey()
{
    bool key = false;
    for (auto& unmovable : m_staticObject)
    {
        if (typeid(Key) == typeid(*unmovable))
            if (unmovable->getToDelete())
            {
                key = true;
                break;
            }
    }
    if (key)//if the player take a key
    {
        for (auto& unmovable : m_staticObject)
        {
            if (typeid(Door) == typeid(*unmovable))
            {
                unmovable->setToDelete();
                break;
            }
        }
    }
}

//this function responsible to execute the operation of gifts types
void GameController::checkGiftMode()
{
    if (TimeManger::getTimeMangerInstance().isSuperModeOver())
    {
        m_pacman->resetToRegular();
        DataBoard::getDataBoardInstance().setSuperMode();
    }
    for (auto& movable : m_Demons)
    {
        if (DataBoard::getDataBoardInstance().getFreezeMode())
            movable.get()->getObject().setPosition(movable.get()->getLastLocation());
        if (TimeManger::getTimeMangerInstance().isFreezeModeOver())
            DataBoard::getDataBoardInstance().setFreezeMode();
    }
}



