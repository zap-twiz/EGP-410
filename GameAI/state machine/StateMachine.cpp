#include <assert.h>
#include "StateMachine.h"

StateMachineState::~StateMachineState()
{
}

void StateMachineState::addTransition( StateTransition* pTransition )
{
	mTransitions[ pTransition->getTransitionType()] = pTransition;
}


void StateMachine::addState( StateMachineState* pState )
{
	mStates[ pState->getID() ] = pState;
}

void StateMachine::start()
{
	if( mInitialStateID != -1 )
	{
		transitionToState( mInitialStateID );
	}
}

void StateMachine::update()
{
	if( mpCurrentState == NULL )
	{
		start();
		assert( mpCurrentState != NULL );
	}

	StateTransition* pTransition = mpCurrentState->update();
	if( pTransition != NULL )
	{
		transitionToState( pTransition->getTargetStateID() );
	}
}

void StateMachine::transitionToState( const SM_idType& targetID )
{
	if( mpCurrentState != NULL )
	{
		mpCurrentState->onExit();
	}

	mpCurrentState = mStates[targetID];
	if( mpCurrentState != NULL )
	{
		mpCurrentState->onEntrance();
	}
}
