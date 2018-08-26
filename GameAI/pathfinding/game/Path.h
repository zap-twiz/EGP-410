#pragma once

#include <vector>
#include <Trackable.h>

class Node;

class Path:public Trackable
{
public:
	Path();
	~Path();

	Node* peekNode( int index ) const;
	Node* peekNextNode() const;
	Node* getAndRemoveNextNode();
	bool containsNode( Node* pNode );
	int getNumNodes() const { return mNodes.size(); };

	void addNode( Node* pNode );

private:
	std::vector<Node*> mNodes;

};