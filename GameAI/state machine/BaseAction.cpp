#include <iostream>
#include "BaseAction.h"

using namespace std;

void BaseAction::doAction()
{
	cout << "Action found! id=" << getID() << endl;
}

DecisionTreeNode* BaseAction::makeDecision()
{
	return this;
}