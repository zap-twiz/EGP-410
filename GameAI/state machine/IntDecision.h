#pragma once

#include "DecisionTreeHelpers.h"

class IntDecision: public Decision
{
public:
	//constructor
	IntDecision( const DT_idType& id, int comparisonValue, DecisionTreeNode* pTrueNode = NULL, DecisionTreeNode* pFalseNode = NULL );

	//make the decision
    virtual bool getBranch();

	inline void setTestValue( int theValue ){ mTestValue = theValue; }; 

private:
	int mComparisonValue;
	int mTestValue;
};