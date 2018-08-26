#pragma once

#include "Trackable.h"
#include "Vector2D.h"
#include "Color.h"

class GraphicsBuffer;
class GraphicsBufferManager;
class Sprite;
class Renderer;
class Font;
struct SDL_Window;
struct SDL_Texture;


class GraphicsSystem:public Trackable
{
public:
	GraphicsSystem();
	~GraphicsSystem();

	bool init( int width, int height );
	void cleanup();

	void swap();
	void wrapCoordinates( Vector2D& vector );//change the x and y values in the vector to keep them on the visible screen

	//accessors
	int getWidth() const { return mWidth; };
	int getHeight() const { return mHeight; };
	inline GraphicsBuffer* getBackBuffer() { return mpBackBuffer; };
	inline Renderer* getRenderer() { return mpRenderer; };

	//draw the contents of the sprite to the Backbuffer - may be rotated
	void draw(const Sprite& aSprite, float dx, float dy, float rotationInRadians = 0, int flags = 0);
	//draw the contents of the sprite to a GraphicsBuffer - may be rotated
	void draw(GraphicsBuffer& dest, const Sprite& aSprite, float dx, float dy, float rotationInRadians = 0, int flags = 0);
	//writeText
	void writeText(Font& font, float dx, float dy, const std::string& text, const Color& color);
	//writeText
	void writeText(GraphicsBuffer& dest, Font& font, float dx, float dy, const std::string& text, const Color& color);
	//set entire buffer to given color
	void clear(GraphicsBuffer& buffer, const Color& color = BLACK_COLOR);
	//set a rectangular region to a color
	void fillRegion(GraphicsBuffer& buffer, const Vector2D& ul, const Vector2D& lr, const Color& color);
private:
	SDL_Window* mpWindow;
	Renderer* mpRenderer;
	GraphicsBuffer* mpBackBuffer;
	int mWidth;
	int mHeight;
	bool mInitted;

	friend class GraphicsBufferManager;
	SDL_Texture* loadTexture(const std::string& filename);
	SDL_Texture* createTexture(int width, int height);
	SDL_Texture* setRenderTarget(GraphicsBuffer& pBuffer);//returns previous render target texture
	void restoreRenderTarget(SDL_Texture* oldTarget);
};