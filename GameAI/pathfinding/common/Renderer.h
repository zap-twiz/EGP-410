#pragma once

#include "Trackable.h"
#include <string>

class GraphicsSystem;
class GraphicsBuffer;
struct SDL_Window;
struct SDL_Renderer;

class Renderer :public Trackable
{
public:

	GraphicsBuffer* makeBackBuffer() const;

	//Renderer(GraphicsBuffer* pBuffer);
	~Renderer();


private:
	SDL_Renderer* mpRenderer;


	friend class GraphicsSystem;

	Renderer(SDL_Window* pWindow);

	//invalidate copy constructor and assignment operator
	Renderer(const Renderer& rhs);
	Renderer& operator=(const Renderer& rhs);

};