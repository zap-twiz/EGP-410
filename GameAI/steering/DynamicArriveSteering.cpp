#include "DynamicArriveSteering.h"
#include "KinematicUnit.h"

DynamicArriveSteering::DynamicArriveSteering(KinematicUnit *pMover, KinematicUnit* pTarget, float targetRadius, float slowRadius, float timeToTarget)
:mpMover(pMover)
,mpTarget(pTarget)
,mTargetRadius(targetRadius)
,mSlowRadius(slowRadius)
,mTimeToTarget(timeToTarget)
{
	mApplyDirectly = true;
}

Steering* DynamicArriveSteering::getSteering()
{
	Vector2D direction = mpTarget->getPosition() - mpMover->getPosition();
	float distance = direction.getLength();

	//are we there?
	if( distance < mTargetRadius )
	{
		mLinear = gZeroVector2D;
		mAngular = 0.0f;

		return this;
	}

	float targetSpeed = 0.0f;

	//are we outside slow radius?
	if( distance > mSlowRadius )
	{
		targetSpeed = mpMover->getMaxVelocity();
	}
	else
	{
		targetSpeed = ( mpMover->getMaxVelocity() * distance ) / mSlowRadius;
	}

	//combine speed and direction to get targetVelocity
	Vector2D targetVelocity = direction;
	targetVelocity.normalize();
	targetVelocity *= targetSpeed;

	//set acceleration
	mLinear = targetVelocity - mpMover->getVelocity();
	mLinear /= mTimeToTarget;

	//check if too fast
	if( mLinear.getLength() > mpMover->getMaxAcceleration() )
	{
		//cut down to max
		mLinear.normalize();
		mLinear*= mpMover->getMaxAcceleration();
	}

	mAngular = 0.0f;

	return this;
}