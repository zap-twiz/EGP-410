#include <iostream>
#include <map>
#include "MemoryTracker.h"

using namespace std;

int MemoryTracker::msAllocationNum = 0;
MemoryTracker* MemoryTracker::mpInstance = NULL;

MemoryTracker::MemoryTracker()
{
}

MemoryTracker::~MemoryTracker()
{
	cout << "MemoryTracker being deleted: final allocations follow:\n";
	reportAllocations( cout );
}

MemoryTracker* MemoryTracker::getInstance()
{
	if (mpInstance == NULL)
	{
		mpInstance = new MemoryTracker;
	}
	return mpInstance;
}

void MemoryTracker::addAllocation( void* ptr, size_t size )
{
	//make sure it's not already in the map
	unordered_map<void*, AllocationRecord>::iterator iter = mAllocations.find( ptr );
	if( iter != mAllocations.end() )
	{
		//already exists - problem!
	}
	else
	{
		AllocationRecord theRec( msAllocationNum, size );
		pair<void*,AllocationRecord> thePair(ptr,theRec);
		mAllocations.insert( thePair );
		msAllocationNum++;
	}
}

void MemoryTracker::removeAllocation( void* ptr )
{
	//find it in the map!
	unordered_map<void*, AllocationRecord>::iterator iter = mAllocations.find( ptr );
	if( iter == mAllocations.end() )
	{
		//problem!!!!
	}
	else
	{
		mAllocations.erase( iter );
	}
}

void MemoryTracker::reportAllocations( std::ostream& stream )
{
	stream << "Current memory allocations:\n";

	//add each allocation to a map so it will be sorted by num
	struct TempStruct
	{
		TempStruct(void* anAddr, size_t aSize) :addr(anAddr), size(aSize) {};
		TempStruct() {};
		void* addr;
		size_t size;
	};

	map<int, TempStruct> aMap;

	unordered_map<void*, AllocationRecord>::iterator iter;
	for( iter = mAllocations.begin(); iter != mAllocations.end(); ++iter )
	{
		//build map for sorting
		TempStruct temp(iter->first, iter->second.size);
		aMap[iter->second.num] = temp;
	}

	//report based on sorted map
	map<int, TempStruct>::iterator iter2;
	for (iter2 = aMap.begin(); iter2 != aMap.end(); ++iter2)
	{
		stream << "address:" << iter2->second.addr << " size:" << iter2->second.size << " num:" << iter2->first << endl;
	}

}
