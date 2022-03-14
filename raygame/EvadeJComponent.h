#pragma once
#include "SteeringComponent.h"
#include <Vector2.h>

class EvadeJComponent :
	public SteeringComponent
{
public:
	EvadeJComponent(Actor* target, float steeringForce) : SteeringComponent::SteeringComponent(target, steeringForce) {};
	~EvadeJComponent() {};

	void setVelocity(MathLibrary::Vector2 velocity) { m_velocity = velocity; }
	MathLibrary::Vector2 getVelocity() { return m_velocity; }

	MathLibrary::Vector2 calculateForce() override;
private:
	MathLibrary::Vector2 m_velocity;
	float m_speed = 200;
};
