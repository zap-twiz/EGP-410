#include "DebugDisplay.h"
#include <allegro5/allegro_ttf.h>
#include "GraphicsBuffer.h"
#include "DebugContent.h"

using namespace std;

DebugDisplay::DebugDisplay( const Vector2D& pos, DebugContent* pContent )
	:mPos(pos)
	,mpContent(pContent)
{
	//actually load the font
	mpFont = al_load_ttf_font( "cour.ttf", 12, 0 );
	if( mpFont == NULL )
	{
		printf( "ttf font file not loaded properly!\n" ); 
		assert(0);
	}
}

DebugDisplay::~DebugDisplay()
{
	al_destroy_font(mpFont);
	delete mpContent;
}

void DebugDisplay::draw( GraphicsBuffer* pBuffer )
{
	string toDisplay = mpContent->getDebugString();
	al_draw_text( mpFont, al_map_rgb( 0, 0, 0 ), mPos.getX(), mPos.getY(), ALLEGRO_ALIGN_LEFT, toDisplay.c_str() );

}
