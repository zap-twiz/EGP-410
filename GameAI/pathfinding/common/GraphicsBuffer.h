#pragma once

#include "Trackable.h"
#include <string>

class Vector2D;
class GraphicsSystem;
class GraphicsBufferManager;
class Color;
class Renderer;
struct SDL_Texture;
struct SDL_Renderer;

const int INVALID_DIMENSION = -1;

class GraphicsBuffer:public Trackable
{
public:

	//accessors
	int getWidth() const;
	int getHeight() const;
	void getDimensions(int& width, int& height) const;
	bool isValid() const { return mValid; };

private:
	SDL_Texture* mpTexture;
	bool mValid=false;

	GraphicsBuffer(SDL_Renderer* pRenderer);//used to create the back buffer
	GraphicsBuffer(SDL_Texture* pTexture);
	~GraphicsBuffer();

	friend class GraphicsSystem;
	friend class Renderer;
	friend class GraphicsBufferManager;

	//invalidate copy constructor and assignment operator
	GraphicsBuffer(const GraphicsBuffer& rhs);
	GraphicsBuffer& operator=(const GraphicsBuffer& rhs);

};