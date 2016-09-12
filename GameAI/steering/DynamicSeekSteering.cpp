#include "DynamicSeekSteering.h"
#include "KinematicUnit.h"

DynamicSeekSteering::DynamicSeekSteering(KinematicUnit *pMover, KinematicUnit* pTarget, bool shouldFlee)
:mpMover(pMover)
,mpTarget(pTarget)
,mShouldFlee(shouldFlee)
{
	mApplyDirectly = false;
}

Steering* DynamicSeekSteering::getSteering()
{
	if( !mShouldFlee )
	{
		mLinear = mpTarget->getPosition() - mpMover->getPosition();
	}
	else
	{
		mLinear = mpMover->getPosition() - mpTarget->getPosition();
	}

	mLinear.normalize();
	mLinear *= mpMover->getMaxVelocity();
	mAngular = 0;
	return this;
}