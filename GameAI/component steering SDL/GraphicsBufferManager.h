#pragma once

#include <map>
#include <string>
#include <Trackable.h>
#include "Defines.h"
#include "Color.h"

class GraphicsBuffer;
class GraphicsSystem;


class GraphicsBufferManager:public Trackable
{
public:
	GraphicsBufferManager(GraphicsSystem* pSystem);
	~GraphicsBufferManager();

	void init();
	void clear();

	GraphicsBuffer* loadBuffer( const GraphicsBufferID& id, const std::string& filename );
	GraphicsBuffer* manageBuffer(const GraphicsBufferID& id, GraphicsBuffer* pBuffer );//do this next
	GraphicsBuffer* createGraphicsBuffer(const GraphicsBufferID& id, int width, int height, const Color& color = BLACK_COLOR);//create blank with given size

	void deleteBuffer( const GraphicsBufferID& id );

	GraphicsBuffer* getBuffer( const GraphicsBufferID& id );

private:
	GraphicsSystem* mpGraphicsSystem;
	std::map<GraphicsBufferID, GraphicsBuffer*> mBuffers;
};