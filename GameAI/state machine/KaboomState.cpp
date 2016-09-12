 #include "Game.h"
#include "KaboomState.h"
#include <iostream>

using namespace std;

void KaboomState::onEntrance()
{
	cout << "\nEntering KaboomState id:" << mID << endl;
}

void KaboomState::onExit()
{
	cout << "\nexitting KaboomState id:" << mID << endl;
}

StateTransition* KaboomState::update()
{
	cout << "KABOOM!" << endl;

	//find the right transition
	map<TransitionType, StateTransition*>::iterator iter = mTransitions.find( END_GAME_TRANSITION );
	if( iter != mTransitions.end() )//found?
	{
		StateTransition* pTransition = iter->second;
		return pTransition;
	}

	return NULL;//no transition
}