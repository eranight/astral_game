#include "ShipPlayer.h"
#include "Sector.h"
#include "Engine.h"
#include "Hittable.h"

USING_NS_CC;
using namespace astral_game;

#define GET_ENGINE dynamic_cast<Engine *>(ward->getComponent(Engine::NAME))

bool ShipPlayer::initWithWard(Node * ward)
{
	auto engine = GET_ENGINE;
	engine->edgeSectorCollisionReaction = [engine](const Vec2 & pos)
	{
		engine->setCurrMovVelocity(0.0f);
	};
	return true;
}

//movement interface
float ShipPlayer::getVelocity()
{
	return GET_ENGINE->getCurrMovVelocity();
}

float ShipPlayer::getMaxVelocity()
{
	return GET_ENGINE->getMaxMovVelocity();
}

void ShipPlayer::setVelocity(float velocity)
{
	GET_ENGINE->setCurrMovVelocity(velocity);
}

//rotation interface
float ShipPlayer::getRotationDirection()
{
	return GET_ENGINE->getRotDirection();
}

void ShipPlayer::setLeftRotation()
{
	GET_ENGINE->setLeftRotDirection();
}

void ShipPlayer::setRightRotation()
{
	GET_ENGINE->setRightRotDirection();
}

void ShipPlayer::turnOnAngle(float angle)
{
	GET_ENGINE->turnToAngle(angle);
}