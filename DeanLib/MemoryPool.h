#pragma once

#include <forward_list>
#include "DeanLibDefines.h"
#include "Trackable.h"


class MemoryPool: public Trackable
{
public:
	MemoryPool(unsigned int maxNumObjects, unsigned int objectSize);
	~MemoryPool(){ free(mMemory); };

	Byte* allocateObject();
	void freeObject(Byte* ptr);

	inline unsigned int getMaxObjectSize(){ return mObjectSize; };
	inline unsigned int getNumFreeObjects(){ return mMaxNumObjects - mNumAllocatedObjects; };

private:
	Byte* mMemory;
	Byte* mHighestValidAddress;
	unsigned int mMaxNumObjects;
	unsigned int mNumAllocatedObjects;
	unsigned int mObjectSize;
	std::forward_list<Byte*> mFreeList;
};