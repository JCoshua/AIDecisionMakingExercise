#pragma once
#include "Component.h"
#include "Actor.h"
#include "Agent.h"
#include "Transform2D.h"

class SteeringComponentKW :
	public Component
{
public:
	SteeringComponentKW() { m_target = nullptr; m_force = 0; }
	SteeringComponentKW(Actor* target, float force) { m_target = target; m_force = force; }

	virtual MathLibrary::Vector2 calculateForce() = 0;

	float getSteeringForce() { return m_force; }
	void setSteeringForce(float value) { m_force = value; }

	Actor* getTarget() { return m_target; }
	void setTarget(Actor* target) { m_target = target; }

	Agent* getAgent() { return (Agent*)getOwner(); }

private:
	float m_force = 0;
	Actor* m_target;
};

