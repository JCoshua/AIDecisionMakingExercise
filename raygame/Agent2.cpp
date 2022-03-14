#include "Agent2.h"
#include <string.h>
#include "SpriteComponent.h"
#include "StateMachineComponentsKW.h"
#include "GameManager.h"
#include "Goal.h"
#include "SeekComponentKW.h"

Agent2::Agent2(float x, float y, const char* name, float maxForce, float maxSpeed, float health) : Character(x, y, name, maxForce, maxSpeed, health)
{
	addComponent(new SpriteComponent("Images/enemy.png"));
}

void Agent2::onCollision(Actor* actor)
{
	Character::onCollision(actor);
}

void Agent2::start()
{
	Character::start();

	//add seek component
	addComponent<SeekComponentKW>();
	getComponent<SeekComponentKW>()->setTarget(GameManager::getInstance()->getBall());
	getComponent<SeekComponentKW>()->setSteeringForce(500);
	getComponent<SeekComponentKW>()->start();

	addComponent<StateMachineComponentsKW>();
	getComponent<StateMachineComponentsKW>()->start();
}

void Agent2::update(float deltaTime)
{
	Character::update(deltaTime);
	if (getHasBall())
	{
		getComponent<SeekComponentKW>()->setTarget(GameManager::getInstance()->getRightGoal());
	}
	getComponent<StateMachineComponentsKW>()->update(deltaTime);
}

void Agent2::onDeath()
{
	Character::onDeath();
}