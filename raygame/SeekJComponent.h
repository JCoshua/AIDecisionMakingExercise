#pragma once
#include "SteeringComponent.h"

class SeekJComponent :
	public SteeringComponent
{

public:
	SeekJComponent(Actor* target, float steeringForce) : SteeringComponent::SteeringComponent(target, steeringForce) {};
	~SeekJComponent() {};

	MathLibrary::Vector2 calculateForce() override;
private:
	float m_speed = 200;
};

