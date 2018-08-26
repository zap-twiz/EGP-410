#include "DebugDisplay.h"
#include "GraphicsBuffer.h"
#include "DebugContent.h"
#include "Game.h"
#include "GraphicsSystem.h"
#include "Color.h"

using namespace std;

DebugDisplay::DebugDisplay( const Vector2D& pos, DebugContent* pContent )
	:mPos(pos)
	,mpContent(pContent)
{
}

DebugDisplay::~DebugDisplay()
{
	delete mpContent;
}

void DebugDisplay::draw( GraphicsBuffer* pBuffer )
{
	string toDisplay = mpContent->getDebugString();
	gpGame->getGraphicsSystem()->writeText(*pBuffer, *(gpGame->getFont()), mPos.getX(), mPos.getY(), toDisplay, BLACK_COLOR);

}
