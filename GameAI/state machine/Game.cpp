#include "Game.h"
#include "Timer.h"

Game::Game()
:mFrameCount(0)
,mShouldExit(false)
{
	mpTimer = new Timer;
}

Game::~Game()
{
	delete mpTimer;
}

bool Game::update()
{
	mpTimer->start();

	mFrameCount++;

	mpTimer->sleepUntilElapsed( LOOP_TARGET_TIME );
	return mShouldExit;
}