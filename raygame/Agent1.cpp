#include "Agent1.h"
#include "SpriteComponent.h"
#include "SeekJComponent.h"
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
	Actor* evasiveRadius = new Actor();
	evasiveRadius->getTransform()->setWorldPostion(getTransform()->getWorldPosition());
	getTransform()->addChild(evasiveRadius->getTransform());
	evasiveRadius->setCollider(new CircleCollider(200, evasiveRadius));

	//add steering behaviours here
	Actor* ball = new Actor();
	ball->getTransform()->setWorldPostion(GameManager::getInstance()->getBallPosition());
	addComponent(new SeekJComponent(ball, 500));
	
}

void Agent1::update(float deltaTime)
{
	Character::update(deltaTime);

	GameManager* gameState = GameManager::getInstance();

	if (getHasBall())
		getComponent<SeekJComponent>()->setTarget(gameState->getRightGoal());

	else if (m_currentMines < m_maxMines && m_mineTimer > 2)
	{
		float randNum = rand();
		MathLibrary::Vector2 randPosition = MathLibrary::Vector2(sin(randNum), cos(randNum)).getNormalized() * 100;
		randPosition = gameState->getAgent2()->getTransform()->getWorldPosition() + randPosition;

		Landmine* landmine = new Landmine(randPosition, this);
		m_mineTimer = 0;
	}

	m_mineTimer += deltaTime;
}

void Agent1::onDeath()
{
	Character::onDeath();

}
