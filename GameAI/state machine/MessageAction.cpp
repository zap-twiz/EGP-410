#include <iostream>
#include "MessageAction.h"

using namespace std;

MessageAction::MessageAction( const DT_idType& id, const string& message )
:BaseAction(id)
,mMessage(message)
{
}

void MessageAction::doAction()
{
	cout << mMessage << endl;
}