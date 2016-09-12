#include <string>
#include <iostream>
#include <conio.h>

#include "DecisionTreeHelpers.h"
#include "IntDecision.h"
#include "MessageAction.h"

#include "Game.h"
#include "StateMachine.h"
#include "TickState.h"
#include "KaboomState.h"
#include "EndGameState.h"
#include "MemoryTracker.h"

using namespace std;

Game* gpGame = NULL;

void main()
{
	//create the game
	gpGame = new Game;

	//create the state machine
	StateMachine* pStateMachine1 = new StateMachine();

	//create the states
	StateMachineState* pTickState = new TickState(0,10);
	StateMachineState* pKaboomState = new KaboomState(1);
	StateMachineState* pEndGameState = new EndGameState(2);

	//create the transitions
	StateTransition* pToKaboomTrans = new StateTransition( KABOOM_TRANSITION, 1 );
	StateTransition* pToEndGameTrans = new StateTransition( END_GAME_TRANSITION, 2 );

	//add the transitions to the states
	pTickState->addTransition( pToKaboomTrans );
	pKaboomState->addTransition( pToEndGameTrans );

	//add the states to the state machine
	pStateMachine1->addState( pTickState );
	pStateMachine1->addState( pKaboomState );
	pStateMachine1->addState( pEndGameState );

	//set the initial state
	pStateMachine1->setInitialStateID(0);

	bool exitting = false;
	bool machineRunning = false;

	while( !exitting )
	{
		if( !machineRunning )
		{
			cout << "\npress any key to start the countdown!";
		}

		if( _kbhit() )
		{
			machineRunning = true;
		}

		if( machineRunning )
		{
			cout << "SM1:";
			pStateMachine1->update();
			
		}

		exitting = gpGame->update();
	}

	delete pStateMachine1;
	delete pTickState;
	delete pKaboomState;
	delete pEndGameState;
	delete pToKaboomTrans;
	delete pToEndGameTrans;
	delete gpGame;
	gpGame = NULL;

	gMemoryTracker.reportAllocations( cout );

	system("pause");

	//DecisionTree stuff!!!
	//create a bunch of nodes
	IntDecision* pDecision0 = new IntDecision( 0, 10 ); 
	IntDecision* pDecision1 = new IntDecision( 1, 20 ); 
	IntDecision* pDecision2 = new IntDecision( 2, 30 ); 
	MessageAction* pAction0 = new MessageAction( 3, "pAction0" );
	MessageAction* pAction1 = new MessageAction( 4, "pAction1" );
	MessageAction* pAction2 = new MessageAction( 5, "pAction2" );
	MessageAction* pAction3 = new MessageAction( 6, "pAction3" );

	//add nodes to tree
	Decision* start = pDecision0;
	start->setTrueBranch( pAction0 );
	start->setFalseBranch( pDecision1 );
	pDecision1->setTrueBranch( pAction1 );
	pDecision1->setFalseBranch( pDecision2 );
	pDecision2->setTrueBranch( pAction2 );
	pDecision2->setFalseBranch( pAction3);

	pDecision0->setTestValue( 30 );
	pDecision1->setTestValue( 30 );
	pDecision2->setTestValue( 30 );

	DecisionTreeNode* pDecision = start->makeDecision();
	BaseAction* pAction = dynamic_cast<BaseAction*>(pDecision);
	pAction->doAction();

	delete pDecision0;
	delete pDecision1;
	delete pDecision2;
	delete pAction0;
	delete pAction1;
	delete pAction2;
	delete pAction3;

	delete gpGame;
	gMemoryTracker.reportAllocations( cout );

	system("pause");

}