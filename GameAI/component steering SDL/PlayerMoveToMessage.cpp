#include "Game.h"
#include "GameMessageManager.h"
#include "PlayerMoveToMessage.h"
#include "UnitManager.h"

PlayerMoveToMessage::PlayerMoveToMessage( const Vector2D& pos )
:GameMessage(PLAYER_MOVETO_MESSAGE)
,mPos(pos)
{
}

PlayerMoveToMessage::~PlayerMoveToMessage()
{
}

void PlayerMoveToMessage::process()
{
	Unit* pPlayer = gpGame->getUnitManager()->getPlayerUnit();
	pPlayer->setSteering(Steering::SEEK, mPos);
}

