#pragma once
#include "Actor.h"
#include "Transform2D.h"
#include "SpriteComponent.h"
#include "Engine.h"
#include "Agent1.h"
#include "Character.h"
#include <iostream>
#include "CircleCollider.h"

class Landmine :
	public Actor
{

public:
	Landmine(MathLibrary::Vector2 spawnLocation) : Actor::Actor(spawnLocation.x, spawnLocation.y, "Landmine")
	{
		getTransform()->setScale({ 50,50 });
		addComponent(new SpriteComponent("Images/bullet.png"));
		Engine::getCurrentScene()->addActor(this);
		setCollider(new CircleCollider(200, this));
	}

	Landmine(MathLibrary::Vector2 spawnLocation, Agent1* owner) : Actor::Actor(spawnLocation.x, spawnLocation.y, "Landmine")
	{
		getTransform()->setScale({ 50,50 });
		addComponent(new SpriteComponent("Images/bullet.png"));
		Engine::getCurrentScene()->addActor(this);
		m_owner = owner;
		owner->setCurrentMines(owner->getCurrentMines() + 1);
		setCollider(new CircleCollider(5000, this));
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

	void onCollision(Actor* actor) override
	{
		if (actor->getName() == "Ball" || actor->getName() == "LeftGoal" || actor->getName() == "RightGoal" || actor == m_owner)
			return;

		if (actor->getName() == "Landmine" && !m_isExploding)
			return;

		m_isExploding = true;

		if (actor == GameManager::getInstance()->getAgent2() || actor == GameManager::getInstance()->getAgent1())
		{
			Character* character = (Character*)actor;
			character->takeDamage();
			std::cout << "Took Damage";
		}
		else
		{
			Engine::destroy(actor);
		}

		for (int i = 0; i < Engine::getCurrentScene()->getActors().getLength(); i++)
		{
			checkForCollision(Engine::getCurrentScene()->getActor(i));
		}

		Engine::destroy(this);
	}

	bool checkForCollision(Actor* other) override
	{
		if ((other->getTransform()->getWorldPosition() - getTransform()->getWorldPosition()).getMagnitude() > 10 && !m_isExploding)
			return false;

		Actor::checkForCollision(other);
	}

private:
	bool m_isExploding = false;
	Agent1* m_owner;
	float m_timer = 0;
};

