#pragma once

#include <Trackable.h>
#include <Vector2D.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

class DebugContent;
class GraphicsBuffer;

class DebugDisplay:public Trackable
{
public:
	DebugDisplay( const Vector2D& pos, DebugContent* pContent );
	~DebugDisplay();

	void draw( GraphicsBuffer* pBuffer );

private:
	ALLEGRO_FONT* mpFont;
	DebugContent* mpContent;
	Vector2D mPos;

};