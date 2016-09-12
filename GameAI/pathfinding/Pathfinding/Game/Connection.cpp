#include "Node.h"
#include "Connection.h"

Connection::Connection( Node* pFrom, Node* pTo, float cost )
:mpFrom(pFrom)
,mpTo(pTo)
,mCost(cost)
{
}

Connection::~Connection()
{
}