#pragma once

#include "Component.h"
#include <Vector2D.h>
#include <Trackable.h>
#include <cfloat>

class PositionComponent;

static const float MAX_ACC = 250.0f;
static const float MAX_SPEED = 220.0f;
static const float MAX_ROT_ACC = 1.0f;
static const float MAX_ROT_VEL = 5.0f;

struct PhysicsData : public Trackable
{
	PhysicsData(
		const Vector2D& theVel
		, const Vector2D& theAcc
		, float theRotVel
		, float theRotAcc
		, float theMaxSpeed = MAX_SPEED
		, float theMaxAcc = MAX_ACC
		, float theMaxRotVel = MAX_ROT_VEL
		, float theMaxRotAcc = MAX_ROT_ACC) 
		:vel(theVel)
		, acc(theAcc)
		, rotVel(theRotVel)
		, rotAcc(theRotAcc)
		, maxSpeed(theMaxSpeed)
		, maxAccMagnitude(theMaxAcc)
		, maxRotVel(theMaxRotVel)
		, maxRotAcc(theRotAcc)
	{};

	PhysicsData() 
		:vel(ZERO_VECTOR2D)
		, acc(ZERO_VECTOR2D)
		, rotVel(0.0f)
		, rotAcc(0.0f)
		, maxSpeed(MAX_SPEED)
		, maxAccMagnitude(MAX_ACC)
		, maxRotVel(MAX_ROT_VEL)
		, maxRotAcc(MAX_ROT_ACC)
	{};

	Vector2D vel;
	Vector2D acc;
	float rotVel;
	float rotAcc;
	float maxSpeed;
	float maxAccMagnitude;
	float maxRotVel;
	float maxRotAcc;
};

const PhysicsData ZERO_PHYSICS_DATA;

class PhysicsComponent :public Component
{
public:

	void setData(const PhysicsData& data){ mData = data; };
	void modData(const PhysicsData& data);
	const PhysicsData& getData() const { return mData; };
	const Vector2D& getVelocity() const { return mData.vel; };
	const Vector2D& getAcceleration() const { return mData.acc; };
	float getRotationalVelocity() const { return mData.rotVel; };
	float getRotationalAcceleration() const { return mData.rotAcc; };

private:
	PhysicsData mData;
	ComponentID mPositionComponentID;
	PositionComponent* mpPositionComponent=NULL;

	PhysicsComponent(const ComponentID& id, const ComponentID& posID) :Component(id), mPositionComponentID(posID){};
	~PhysicsComponent(){};

	void integrate(PositionComponent& posComponent, float elapsedTime);

	void setPositionComponent(PositionComponent* pComp) { mpPositionComponent = pComp; };

	friend class ComponentManager;
};