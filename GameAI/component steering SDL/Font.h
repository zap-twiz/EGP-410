#pragma once

#include "Trackable.h"
#include <string>
#include <SDL_ttf.h>

class GraphicsSystem;

class Font :public Trackable
{
	friend class GraphicsSystem;
public:
	Font(const std::string& filename, int size);
	~Font();

	//accessors
	int getSize() const { return mSize; };

private:
	TTF_Font* mpFont;
	int mSize;

	//invalidate copy constructor and assignment operator
	Font(const Font& rhs);
	Font& operator=(const Font& rhs);

};