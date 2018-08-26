#pragma once

#include "GameMessage.h"

#include "Vector2D.h"

class PathToMessage:public GameMessage
{
public:
	PathToMessage( const Vector2D& from, const Vector2D& to );
	~PathToMessage();

	const Vector2D& getFrom() const { return mFrom; };
	const Vector2D& getTo() const { return mTo; };

	void process();

private:
	Vector2D mFrom;
	Vector2D mTo;
};