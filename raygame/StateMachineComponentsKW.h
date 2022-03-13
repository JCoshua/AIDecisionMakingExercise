#pragma once
#include "Component.h"

class SeekComponentKW;

enum State
{
    SEEKBALL,
    SEEKGOAL,
    ATTACKENEMY
};

class StateMachineComponentsKW :
    public Component
{
public:
    State getCurrentState() { return m_currentState; }
    void setCurrentState(State newState) { m_currentState = newState; }

    void start() override;
    void update(float deltaTime) override;
private:
    State m_currentState;
    SeekComponentKW* m_seekComponent;
    float m_seekForce;
    float m_seekRange = 300;
};

