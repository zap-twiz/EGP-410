#pragma once

#include <map>
#include <Trackable.h>

/*Collection of base classes to implement a StateMachine.  Heavily borrowed from
	Millington text.

	Dean lawson
	Champlain College 
	2011
*/

class StateTransition;

enum TransitionType
{
	INVALID_TRANSITION_TYPE = -1,
	KABOOM_TRANSITION = 0,
	END_GAME_TRANSITION = 1
};

typedef int SM_idType;

class StateMachineState:public Trackable
{
public:
	StateMachineState( const SM_idType& id ):mID(id){};
	~StateMachineState();

	void addTransition( StateTransition* pTransition );
	inline const SM_idType& getID() const { return mID; };

	virtual void onEntrance()=0;//code to run when the state is entered
	virtual void onExit()=0;//code to run when the state is exitted
	virtual StateTransition* update()=0;//code to run each frame - returning NULL means no transition

protected:
	SM_idType mID;
	std::map<TransitionType, StateTransition*> mTransitions;
};

class StateTransition:public Trackable
{
public:
	StateTransition( TransitionType type, const SM_idType& targetID ):mType(type),mpTargetStateID(targetID){};
	~StateTransition(){};

	int getTargetStateID() const { return mpTargetStateID; };
	TransitionType getTransitionType() const { return mType; };

protected:
	SM_idType mpTargetStateID;//id of the state to transition to if this transition is taken
	TransitionType mType;
};

class StateMachine:public Trackable
{
public:
	StateMachine():mpCurrentState(NULL),mInitialStateID(-1){};
	~StateMachine(){};

	void addState( StateMachineState* pState );
	void setInitialStateID( const SM_idType& id ){ mInitialStateID = id; };

	void update();//give the current state a chance to run
	void start();//go to the initial state

protected:
	void transitionToState( const SM_idType& targetID );//call onExit for old state and onEntrance for the new state

	std::map<SM_idType, StateMachineState*> mStates;//all states indexed by stateID
	StateMachineState* mpCurrentState;//the current state that is running
	SM_idType mInitialStateID;//the id of the state which should run first
};