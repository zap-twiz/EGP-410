#pragma once

#include <string>

/*Sprite - a logical portion of a GraphicsBuffer.

Dean Lawson
Champlain College
2015
*/

#include <Trackable.h>
#include <Vector2D.h>

class GraphicsBuffer;

class Sprite:public Trackable
{
public:
	Sprite(GraphicsBuffer* pBuffer, int srcX, int srcY, int width, int height);
	Sprite(GraphicsBuffer* pBuffer, const Vector2D& srcLoc, const Vector2D& size);

	~Sprite();

	inline int getWidth() const { return (int)mSize.getX(); };
	inline int getHeight() const { return (int)mSize.getY(); };
	inline const Vector2D& getSourceLoc() const { return mSrcLoc; };
	inline const Vector2D& getSize() const { return mSize; };
	inline GraphicsBuffer* getBuffer() const { return mpBuffer; };

private:
	GraphicsBuffer* mpBuffer;
	Vector2D mSrcLoc;
	Vector2D mSize;
};