#pragma once
#include "Character.h"

class Agent1 :
    public Character
{
public:
    /// <param name="x">The x position of the character</param>
    /// <param name="y">The y position of the character</param>
    /// <param name="name">The name of the character</param>
    /// <param name="maxForce">The maximum amount of force that can be applied to this character</param>
    /// <param name="maxSpeed">How fast this actor can go</param>
    /// <param name="health">The amount of health this character has</param>
    Agent1(float x, float y, const char* name, float maxForce, float maxSpeed, float health);

    int getCurrentMines() { return m_currentMines; }
    void setCurrentMines(int mineCount) { m_currentMines = mineCount; }
    // Inherited from the Character class
    virtual void onCollision(Actor* actor) override;
    virtual void start() override;
    virtual void update(float deltaTime) override;
    virtual void onDeath();
    virtual void onDamageRecieved() {};
private:
    float m_mineTimer = 0;
    int m_maxMines = 20;
    int m_currentMines;
};

