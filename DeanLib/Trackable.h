#pragma once

#include <iostream>

class Trackable
{
public:
	void* operator new( std::size_t size );
	void operator delete( void *ptr );	
	void* operator new[]( std::size_t size );
	void operator delete[]( void *ptr );
};
