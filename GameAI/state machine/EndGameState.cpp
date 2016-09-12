#include "Game.h"
#include "EndGameState.h"
#include <iostream>

using namespace std;

void EndGameState::onEntrance()
{
	cout << "\nEntering EndGameState id:" << mID << endl;
}

void EndGameState::onExit()
{
	cout << "\nexitting EndGameState id:" << mID << endl;
}

StateTransition* EndGameState::update()
{
	cout << "\nGame Over!\n";
	gpGame->markShouldExit();
	return NULL;//no transition as the world is about to end!
}