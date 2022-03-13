#pragma once
#include "SteeringComponent.h"
class SeekComponentKW :
    public SteeringComponent
{
public:
    MathLibrary::Vector2 calculateForce() override;
};

