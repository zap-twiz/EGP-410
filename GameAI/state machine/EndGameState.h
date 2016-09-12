#pragma once

#include "StateMachine.h" 

class EndGameState : public StateMachineState
{
public:
	EndGameState( const SM_idType& id ):StateMachineState(id){};

	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update();
private:
};