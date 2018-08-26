#include "Steering.h"


void Steering::update()
{
	Steering* pTemp = getSteering();
	if (pTemp != NULL)
	{
		mData = pTemp->getData();
	}
}
