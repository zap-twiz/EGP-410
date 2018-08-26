#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

//#include "Game.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Renderer.h"
#include "Font.h"

GraphicsSystem::GraphicsSystem()
	:mpWindow(NULL)
	,mpRenderer(NULL)
	,mpBackBuffer(NULL)
	,mWidth(0)
	,mHeight(0)
	,mInitted(false)
{
}

GraphicsSystem::~GraphicsSystem()
{
	cleanup();
}

bool GraphicsSystem::init( int width, int height )
{
	mWidth = width;
	mHeight = height;

	//init SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	//create window
	mpWindow = SDL_CreateWindow("TEST APP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (mpWindow == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	mpRenderer = new Renderer(mpWindow);
	mpBackBuffer = mpRenderer->makeBackBuffer();

	//enable PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	//enable TTF support
	if (TTF_Init() < 0)
	{
		printf("SDL_TTF could not initialize! SDL_TTF Error: %s\n", TTF_GetError());
		return false;
	}

	mInitted = true;
	return true;
}

void GraphicsSystem::cleanup()
{
	if (mInitted)
	{
		delete mpBackBuffer;
		mpBackBuffer = NULL;

		delete mpRenderer;
		mpRenderer = NULL;

		SDL_DestroyWindow(mpWindow);
		mpWindow = NULL;

		//Quit SDL subsystems
		IMG_Quit();
		TTF_Quit();
		SDL_Quit();
		mInitted = false;
	}
}

void GraphicsSystem::swap()
{
	//present renderer
	SDL_RenderPresent(mpRenderer->mpRenderer);
}

void GraphicsSystem::wrapCoordinates( Vector2D& vector )
{
	if( vector.getX() < 0.0f )
	{
		vector.setX( getWidth() - 1.0f );
	}
	else if( vector.getX() >= getWidth() )
	{
		vector.setX( 0.0f );
	}

	if( vector.getY() < 0.0f )
	{
		vector.setY( getHeight() - 1.0f );
	}
	else if( vector.getY() >= getHeight() )
	{
		vector.setY( 0.0f );
	}
}

void GraphicsSystem::draw(const Sprite& aSprite, float dx, float dy, float rotationInRadians /*= 0*/, int flags /*= 0*/)
{
	draw( *getBackBuffer(), aSprite, dx, dy, rotationInRadians, flags);
}

void GraphicsSystem::draw(GraphicsBuffer& dest, const Sprite& aSprite, float dx, float dy, float rotationInRadians /*= 0*/, int flags /*= 0*/)
{
	SDL_Texture* pOldTarget = setRenderTarget(dest);

	SDL_Renderer* pRenderer = mpRenderer->mpRenderer;
	const Vector2D& srcSize = aSprite.getSize();
	const Vector2D& srcLoc = aSprite.getSourceLoc();
	SDL_Rect srcRect;
	srcRect.w = (int)srcSize.getX();
	srcRect.h = (int)srcSize.getY();
	srcRect.x = (int)srcLoc.getX();
	srcRect.y = (int)srcLoc.getY();
	SDL_Rect destRect;
	destRect.w = (int)srcRect.w;
	destRect.h = (int)srcRect.h;
	destRect.x = (int)dx;
	destRect.y = (int)dy;
	double rotationInDegrees = rotationInRadians * (180.0 / M_PI);
	SDL_RenderCopyEx(pRenderer, aSprite.getBuffer()->mpTexture, &srcRect, &destRect, rotationInDegrees, NULL, SDL_FLIP_NONE);

	restoreRenderTarget(pOldTarget);
}

void GraphicsSystem::writeText(Font& font, float dx, float dy, const std::string& text, const Color& color)
{
	writeText(*(getBackBuffer()), font, dx, dy, text, color);
}

void GraphicsSystem::writeText(GraphicsBuffer& dest, Font& font, float dx, float dy, const std::string& text, const Color& color)
{
	SDL_Color theSDLColor;
	theSDLColor.r = color.getR();
	theSDLColor.g = color.getG();
	theSDLColor.b = color.getB();
	theSDLColor.a = color.getA();

	SDL_Surface* pSurfaceText = TTF_RenderText_Solid(font.mpFont, text.c_str(), theSDLColor);
	SDL_Texture* pTextureText = SDL_CreateTextureFromSurface(mpRenderer->mpRenderer, pSurfaceText);//will be cleared by destructor of GraphicsBuffer

	{//to limit scope of textBuffer without doing dynamic allocation
		GraphicsBuffer textBuffer(pTextureText);

		int width, height;
		textBuffer.getDimensions(width, height);

		draw(dest, Sprite(&textBuffer, 0, 0, width, height), dx, dy);
	}
	SDL_FreeSurface(pSurfaceText);
}

void GraphicsSystem::clear(GraphicsBuffer& buffer, const Color& color)
{
	SDL_Texture* pOldTarget = setRenderTarget(buffer);

	SDL_Renderer* pRenderer = mpRenderer->mpRenderer;
	SDL_SetRenderTarget(pRenderer, buffer.mpTexture);
	SDL_SetRenderDrawColor(pRenderer, color.getR(), color.getG(), color.getB(), color.getA());
	SDL_RenderClear(pRenderer);

	restoreRenderTarget(pOldTarget);
}

void GraphicsSystem::fillRegion(GraphicsBuffer& buffer, const Vector2D& ul, const Vector2D& lr, const Color& color)
{
	SDL_Texture* pOldTarget = setRenderTarget(buffer);

	SDL_Renderer* pRenderer = mpRenderer->mpRenderer;
	Uint8 r, g, b, a;
	SDL_GetRenderDrawColor(pRenderer, &r, &g, &b, &a);

	SDL_SetRenderDrawColor(pRenderer, color.getR(), color.getG(), color.getB(), color.getA());
	
	SDL_Rect destRect;
	destRect.x = (int)ul.getX();
	destRect.y = (int)ul.getY();
	destRect.w = (int)lr.getX() - destRect.x;
	destRect.h = (int)lr.getY() - destRect.y;

	SDL_RenderFillRect(pRenderer, &destRect);

	SDL_SetRenderDrawColor(pRenderer,r,g,b,a);

	restoreRenderTarget(pOldTarget);
}

SDL_Texture* GraphicsSystem::loadTexture(const std::string& filename)
{
	SDL_Surface* pSurface = IMG_Load(filename.c_str());

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(mpRenderer->mpRenderer, pSurface);
	return pTexture;
}

SDL_Texture* GraphicsSystem::createTexture(int width, int height)
{
	SDL_Texture* pTexture = SDL_CreateTexture(mpRenderer->mpRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, width, height);
	return pTexture;
}

SDL_Texture* GraphicsSystem::setRenderTarget(GraphicsBuffer& buffer)
{
	SDL_Renderer* pRenderer = mpRenderer->mpRenderer;
	SDL_Texture* pOldTarget = SDL_GetRenderTarget(pRenderer);
	SDL_SetRenderTarget(pRenderer, buffer.mpTexture);
	return pOldTarget;
}

void GraphicsSystem::restoreRenderTarget(SDL_Texture* oldTarget)
{
	SDL_Renderer* pRenderer = mpRenderer->mpRenderer;
	SDL_SetRenderTarget(pRenderer, oldTarget);
}
