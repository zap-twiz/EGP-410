#pragma once

#include <allegro5/allegro.h>
#include <vector>
#include <map>
#include "Trackable.h"
#include "GraphicsSystem.h"

class Grid;
class GraphicsBuffer;
class Sprite;

class GridVisualizer:public Trackable
{
public:
	GridVisualizer( Grid* pGrid );
	~GridVisualizer();

	void addColor( int index, const ALLEGRO_COLOR& color );
	void removeAllEntriesOfColor( const ALLEGRO_COLOR& color );
	void removeEntry( int index, const ALLEGRO_COLOR& color );
	void setModified() { mDirty = true; };
	void draw( GraphicsBuffer& dest );
	void clear();
private:
	void refresh();

	Grid* mpGrid;
	//key is color, vector contains all indices to be colored that color
	std::map< ALLEGRO_COLOR, std::vector<int>, AllegroColorCompare > mColormap;

	bool mDirty;
};