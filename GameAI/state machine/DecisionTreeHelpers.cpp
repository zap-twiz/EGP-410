#include "DecisionTreeHelpers.h"


Decision::Decision( const DT_idType& id, DecisionTreeNode* pTrueNode, DecisionTreeNode* pFalseNode )
:DecisionTreeNode(id)
,mpTrueBranch(pTrueNode)
,mpFalseBranch(pFalseNode)
{
}

DecisionTreeNode* Decision::makeDecision()
{
	if( getBranch() )
	{
		return mpTrueBranch->makeDecision();
	}
	else
	{
		return mpFalseBranch->makeDecision();
	}
}