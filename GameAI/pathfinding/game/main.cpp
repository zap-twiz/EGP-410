/*main.cpp
	*
	*	Dean Lawson
	*	Champlain College
	*	2011
	*
	*/
#include <cstdlib>
#include <ctime>
#include <crtdbg.h>

#include <SDL.h>

#include "Game.h"
#include "GameApp.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Defines.h"
#include <Timer.h>
#include <MemoryTracker.h>
#include <PerformanceTracker.h>

PerformanceTracker* gpPerformanceTracker = NULL;

int main(int argc, char **argv)
{
	gpPerformanceTracker = new PerformanceTracker();

	gpGame = new GameApp();

	gpGame->init();

	bool shouldExit = false;

	while( !shouldExit )
	{
		gpGame->beginLoop();
		gpGame->processLoop();
		shouldExit = gpGame->endLoop();
	}

	//cleanup
	gpGame->cleanup();
	delete gpGame;
	delete gpPerformanceTracker;

	gMemoryTracker.reportAllocations( std::cout );

	system("pause");

	return 0;
}

