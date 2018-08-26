#include "Sprite.h"
#include "GraphicsBuffer.h"
#include "GraphicsSystem.h"

Sprite::Sprite(GraphicsBuffer* pBuffer, int sx, int sy, int sw, int sh) 
	:mSrcLoc(sx,sy)
	, mSize(sw,sh)
	, mpBuffer(pBuffer)
{
}

Sprite::Sprite(GraphicsBuffer* pBuffer, const Vector2D& srcLoc, const Vector2D& size)
	:mSrcLoc(srcLoc)
	, mSize(size)
	, mpBuffer(pBuffer)

{
}

Sprite::~Sprite()
{
}

