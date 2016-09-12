#include "Graph.h"
#include "Connection.h"

Graph::Graph()
{
}

Graph::~Graph()
{
	for( unsigned int i=0; i<mNodes.size(); i++ )
	{
		delete mNodes[i];
	}

	for( unsigned int i=0; i<mConnections.size(); i++ )
	{
		delete mConnections[i];
	}
}

void Graph::init()
{
}

std::vector<Connection*> Graph::getConnections( const Node& from )
{
	return getConnections( from.getId() );
}

std::vector<Connection*> Graph::getConnections( const NODE_ID& fromId )
{
	static std::vector<Connection*> sEmpty;
	
	std::map< NODE_ID, std::vector<Connection*> >::iterator iter = mConnectionMap.find( fromId );
	if( iter == mConnectionMap.end() )
	{
		return sEmpty;
	}
	else
	{
		return iter->second;
	}
}

Node* Graph::getNode( int index )
{
	if( index < (int)mNodes.size() )
	{
		return mNodes[index];
	}
	else
	{
		return NULL;
	}
}