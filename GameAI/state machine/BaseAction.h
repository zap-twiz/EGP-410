#pragma once

#include "DecisionTreeHelpers.h"

class BaseAction: public DecisionTreeNode
{
public:
	BaseAction( const DT_idType& id ):DecisionTreeNode(id){};

	virtual DecisionTreeNode* makeDecision();
	virtual void doAction();
};