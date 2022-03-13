#include "SeekComponentKW.h"
#include "Actor.h"
#include "Agent.h"
#include "MoveComponent.h"
#include "Transform2D.h"

MathLibrary::Vector2 SeekComponentKW::calculateForce()
{
	if (!getTarget())
		return { 0,0 };

	MathLibrary::Vector2 targetDir = getTarget()->getTransform()->getWorldPosition() -
		getOwner()->getTransform()->getWorldPosition();

	MathLibrary::Vector2 desiredVel = targetDir.getNormalized() * getSteeringForce();
	MathLibrary::Vector2 seekForce = desiredVel - getAgent()->getMoveComponent()->getVelocity();
	return seekForce;
}
