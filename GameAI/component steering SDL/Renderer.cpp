#include "Renderer.h"
#include "GraphicsBuffer.h"

#include <SDL.h>
#include <cassert>


using namespace std;

GraphicsBuffer* Renderer::makeBackBuffer() const
{
	return new GraphicsBuffer(mpRenderer);
}

Renderer::Renderer(SDL_Window* pWindow)
{
	mpRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	if (mpRenderer == NULL)
	{
		//try again with a software renderer
		mpRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_SOFTWARE);
		if (mpRenderer == NULL)
		{
			printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
			assert(false);
		}
	}
}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(mpRenderer);
}