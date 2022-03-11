#include "Agent1.h"
#include "SpriteComponent.h"
#include "SeekJComponent.h"
#include "Transform2D.h"
#include "Goal.h"
#include "GameManager.h"

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
	//add steering behaviours here
	Actor* ball = new Actor();
	ball->getTransform()->setWorldPostion(GameManager::getInstance()->getBallPosition());
	addComponent(new SeekJComponent(ball, 500));
}

void Agent1::update(float deltaTime)
{
	Character::update(deltaTime);

}

void Agent1::onDeath()
{
	Character::onDeath();

}
