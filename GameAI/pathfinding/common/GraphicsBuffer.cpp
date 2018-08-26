#include <SDL.h>
#include <SDL_image.h>
#include <Vector2D.h>
#include <assert.h>

#include "GraphicsBuffer.h"
#include "GraphicsSystem.h"
#include "Renderer.h"
#include "Color.h"

using namespace std;

//used to create the back buffer
GraphicsBuffer::GraphicsBuffer(SDL_Renderer* pRenderer)
{
	mpTexture = SDL_GetRenderTarget(pRenderer);
	if (mpTexture != NULL)
	{
		mValid = true;
	}

}

GraphicsBuffer::GraphicsBuffer(SDL_Texture* pTexture)
	:mpTexture(pTexture)
{
	if (pTexture != NULL)
	{
		mValid = true;
	}
}

GraphicsBuffer::~GraphicsBuffer()
{
	if (mValid)
	{
		SDL_DestroyTexture(mpTexture);
	}
}

void GraphicsBuffer::getDimensions(int& width, int& height) const
{
	if (mValid)
	{
		SDL_QueryTexture(mpTexture, NULL, NULL, &width, &height);
	}
	else
	{
		width = INVALID_DIMENSION;
		height = INVALID_DIMENSION;
	}
}

int GraphicsBuffer::getWidth() const
{
	int width, height;

	getDimensions(width, height);

	return width;
}

int GraphicsBuffer::getHeight() const
{
	int width, height;

	getDimensions(width, height);

	return height;
}