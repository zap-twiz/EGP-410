#include "MemoryPool.h"
#include <cstdlib>
#include <assert.h>

//got this algorithm from: http://www.exploringbinary.com/ten-ways-to-check-if-an-integer-is-a-power-of-two-in-c/
int isPowerOfTwo(unsigned int x)
{
	return ((x != 0) && !(x & (x - 1)));
}

unsigned int getClosestPowerOf2LargerThan(unsigned int num)
{
	static unsigned int powersOf2[32];
	static bool arrayInitted = false;

	if (!arrayInitted)
	{
		for (unsigned int i = 0; i < 32; i++)
		{
			powersOf2[i] = 1 << i;
		}
	}

	for (unsigned int i = 0; i < 32; i++)
	{
		if ( powersOf2[i] >= num )
			return powersOf2[i];
	}

	//failsafe
	return 0;
	
}

MemoryPool::MemoryPool(unsigned int maxNumObjects, unsigned int objectSize)
{
	//make objectSize a power of 2 - used for padding
	objectSize = getClosestPowerOf2LargerThan(objectSize);
	if (objectSize < 4)
	{
		objectSize = 4;
	}

	//allocate the memory
	mMemory = (Byte*)malloc(objectSize * maxNumObjects);

	//create the free list
	for (unsigned int i = 0; i < maxNumObjects; i++)
	{
		mFreeList.push_front(mMemory + (i * objectSize));
	}

	//set member variables
	mMaxNumObjects = maxNumObjects;
	mNumAllocatedObjects = 0;
	mObjectSize = objectSize;
	mHighestValidAddress = mMemory + ((maxNumObjects - 1) * objectSize);
}

Byte* MemoryPool::allocateObject()
{
	if (mNumAllocatedObjects >= mMaxNumObjects)
	{
		return NULL;
	}

	mNumAllocatedObjects++;
	Byte* ptr = *(mFreeList.begin());
	mFreeList.pop_front();
	return ptr;
}

void MemoryPool::freeObject(Byte* ptr)
{
	//make sure that the address passed in is actually one managed by this pool
	assert(ptr >= mMemory && ptr <= mHighestValidAddress);

	//add address back to free list
	mFreeList.push_front(ptr);

	mNumAllocatedObjects--;
}
