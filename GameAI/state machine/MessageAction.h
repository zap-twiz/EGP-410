#pragma once

#include <string>
#include "BaseAction.h"

class MessageAction: public BaseAction
{
public:
	MessageAction( const DT_idType& id, const std::string& message );

	virtual void doAction();

private:
	std::string mMessage;

};