#pragma once

#include <Trackable.h>

/*The basic DecisionTree class heirarchy - Heavily borrowed from Millington text and example source code

Dean Lawson
2011
Champlain College

*/
typedef int DT_idType;

class DecisionTreeNode:public Trackable
{
public:
	DecisionTreeNode( const DT_idType& id ):mID(id){};

	//figure out where to go next in the tree
	virtual DecisionTreeNode* makeDecision() = 0;

	inline const DT_idType& getID(){ return mID; }; 

private:
	DT_idType mID;
};

class Decision : public DecisionTreeNode
{
public:
	Decision( const DT_idType& id, DecisionTreeNode* pTrueNode = NULL, DecisionTreeNode* pFalseNode = NULL );

    virtual bool getBranch() = 0;

    virtual DecisionTreeNode* makeDecision();

	inline void setTrueBranch( DecisionTreeNode* pNode ){ mpTrueBranch = pNode; };
	inline void setFalseBranch( DecisionTreeNode* pNode ){ mpFalseBranch = pNode; };

private:
	DecisionTreeNode* mpTrueBranch;
    DecisionTreeNode* mpFalseBranch;


};
