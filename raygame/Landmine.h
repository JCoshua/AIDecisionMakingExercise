#pragma once
#include "Actor.h"
#include "Transform2D.h"
#include "SpriteComponent.h"
#include "Engine.h"
#include "Agent1.h"

class Landmine :
	public Actor
{
public:
	Landmine(MathLibrary::Vector2 spawnLocation, Agent1* owner) : Actor::Actor(spawnLocation.x, spawnLocation.y, "Landmine")
	{
		getTransform()->setScale({ 50,50 });
		addComponent(new SpriteComponent("Images/bullet.png"));
		Engine::getCurrentScene()->addActor(this);
		m_owner = owner;
		owner->setCurrentMines(owner->getCurrentMines() + 1);
	}

	~Landmine()
	{
		Engine::getCurrentScene()->removeActor(this);
		m_owner->setCurrentMines(m_owner->getCurrentMines() - 1);
	}

	void update(float deltaTime) override
	{
		m_timer += deltaTime;
		if (m_timer > 15)
		{
			Landmine::~Landmine();
		}

	}

private:
	Agent1* m_owner;
	float m_timer = 0;
};

