#pragma once

#include "StateMachine.h"

class TickState : public StateMachineState
{
public:
	TickState( const SM_idType& id, int fireCount ):StateMachineState(id),mFireCount(fireCount){};

	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update();
private:
	int mFireCount;//how many frames need to pass from start until transition
	int mStartingCount;//when did we start?
};