#pragma once

#include "StateMachine.h"

class KaboomState : public StateMachineState
{
public:
	KaboomState( const SM_idType& id ):StateMachineState(id){};

	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update();
private:
};