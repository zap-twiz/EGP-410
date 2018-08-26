#include <cassert>
#include "Game.h"
#include "GameMessageManager.h"
#include "GameMessage.h"

using namespace std;

GameMessageManager::GameMessageManager(Uint32 size)
{
	mMessages = new CircularQueue<GameMessage *>(size);
}

GameMessageManager::~GameMessageManager()
{
	GameMessage* pMessage;
	while( mMessages->popFront(pMessage))
	{
		delete pMessage;
	}

	delete mMessages;
}

void GameMessageManager::processMessagesForThisframe()
{
	GameMessage* pMessage;

	while(mMessages->popFront(pMessage))
	{
		double currentTime = gpGame->getCurrentTime();

		if( pMessage->getScheduledTime() <= currentTime )
		{
			pMessage->process();
			delete pMessage;
		}
		else
		{
			//not time to process yet - push to back
			mMessages->pushBack(pMessage);
		}
	}
}

void GameMessageManager::addMessage( GameMessage* pMessage, int delay )
{
	double currentTime = gpGame->getCurrentTime();

	//set frame numbers
	pMessage->mSubmittedTime = currentTime;
	pMessage->mScheduledTime = currentTime + delay;

	//put it in the message list
	bool success = mMessages->pushBack( pMessage );
	assert(success);
}