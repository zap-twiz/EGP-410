#include "IntDecision.h"

IntDecision::IntDecision( const DT_idType& id, int comparisonValue, DecisionTreeNode* pTrueNode , DecisionTreeNode* pFalseNode )
:Decision(id,pTrueNode,pFalseNode)
,mComparisonValue(comparisonValue)
,mTestValue(0)
{
}

bool IntDecision::getBranch()
{
	if( mTestValue == mComparisonValue )
	{
		return true;
	}
	else
	{
		return false;
	}
}