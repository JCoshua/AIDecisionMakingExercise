#include "Agent1.h"
#include "SpriteComponent.h"
#include "SeekJComponent.h"
#include "EvadeJComponent.h"
#include "MoveComponent.h"
#include "Transform2D.h"
#include "Goal.h"
#include "GameManager.h"
#include "CircleCollider.h"
#include "Landmine.h"

Agent1::Agent1(float x, float y, const char* name, float maxForce, float maxSpeed, float health) : Character(x, y, name, maxForce, maxSpeed, health)
{
	addComponent(new SpriteComponent("Images/player.png"));
}

void Agent1::onCollision(Actor* actor)
{
	Character::onCollision(actor);
}

void Agent1::start()
{
	Character::start();

	//Evasion Radius
	m_flareActor = new Actor();
	m_flareActor->getTransform()->setWorldPostion(getTransform()->getWorldPosition());
	getTransform()->addChild(m_flareActor->getTransform());
	m_flareActor->setCollider(new CircleCollider(200, m_flareActor));

	//add steering behaviours here
	addComponent(new SeekJComponent(GameManager::getInstance()->getBall(), 75));
	addComponent(new EvadeJComponent(nullptr, 0));
}

void Agent1::update(float deltaTime)
{
	Character::update(deltaTime);

	GameManager* gameState = GameManager::getInstance();

	if (getHasBall())
	{
		if (m_mineTimer > 0.3f)
		{
			MathLibrary::Vector2 mineLocation = gameState->getRightGoal()->getTransform()->getWorldPosition() - getTransform()->getWorldPosition();
			mineLocation = (mineLocation.getNormalized() * (mineLocation.getMagnitude() / 10)) + getTransform()->getWorldPosition();
			float randNum = rand();
			MathLibrary::Vector2 randPosition = MathLibrary::Vector2(sin(randNum), cos(randNum)).getNormalized() * 50;
			mineLocation = mineLocation + randPosition;

			Landmine* landmine = new Landmine(mineLocation, this);
			m_mineTimer = 0;
		}
		getComponent<SeekJComponent>()->setTarget(gameState->getRightGoal());
		getComponent<EvadeJComponent>()->setSteeringForce(0);
	}
	else if (gameState->getAgent2()->getHasBall() && m_currentMines < m_maxMines && m_mineTimer > 0.7f)
	{
		MathLibrary::Vector2 mineLocation = gameState->getLeftGoal()->getTransform()->getWorldPosition() - gameState->getAgent2()->getTransform()->getWorldPosition();
		mineLocation = (mineLocation.getNormalized() / (mineLocation.getMagnitude())) + gameState->getAgent2()->getTransform()->getWorldPosition();
		float randNum = rand();
		MathLibrary::Vector2 randPosition = MathLibrary::Vector2(sin(randNum), cos(randNum)).getNormalized() * 10;
		mineLocation = mineLocation + randPosition;

		Landmine* landmine = new Landmine(mineLocation, this);
		m_mineTimer = 0;
		getComponent<EvadeJComponent>()->setSteeringForce(0);
	}
	else if(m_mineTimer > 1)
	{
		MathLibrary::Vector2 mineLocation;
		bool minePlaced = false;
		for (int i = 0; i < Engine::getCurrentScene()->getActors().getLength(); i++)
		{
			minePlaced = m_flareActor->checkForCollision(Engine::getCurrentScene()->getActor(i));
			if (minePlaced)
			{
				getComponent<EvadeJComponent>()->setTarget(Engine::getCurrentScene()->getActor(i));
				getComponent<EvadeJComponent>()->setSteeringForce(30);
				mineLocation = Engine::getCurrentScene()->getActor(i)->getTransform()->getWorldPosition();
			}
		}

		if (!minePlaced)
		{
			mineLocation = gameState->getBall()->getTransform()->getWorldPosition() - gameState->getAgent2()->getTransform()->getWorldPosition();
			mineLocation = (mineLocation.getNormalized() * (mineLocation.getMagnitude() / 3)) + gameState->getAgent2()->getTransform()->getWorldPosition();

			float randNum = rand();
			MathLibrary::Vector2 randPosition = MathLibrary::Vector2(sin(randNum), cos(randNum)).getNormalized() * 50;
			mineLocation = mineLocation + randPosition;
			getComponent<EvadeJComponent>()->setSteeringForce(0);
		}

		Landmine* landmine = new Landmine(mineLocation, this);
		m_mineTimer = 0;
	}

	if (gameState->getAgent2Points() == 2)
	{
		getComponent<MoveComponent>()->setMaxSpeed(75);
		m_mineTimer += deltaTime;
	}
	m_mineTimer += deltaTime;
}

void Agent1::onDeath()
{
	Character::onDeath();

}
