#include "ShipPlayer.h"
#include "Sector.h"
#include "Engine.h"
#include "SkillsSet.h"
#include "Cannon.h"
#include "Hittable.h"

USING_NS_CC;
using namespace astral_game;

bool ShipPlayer::initWithWard(Node * ward)
{
	this->ward = ward;
	engine = dynamic_cast<Engine *>(ward->getComponent(Engine::NAME));
	engine->edgeSectorCollisionReaction = [this](const Vec2 & pos)
	{
		this->engine->setCurrMovVelocity(0.0f);
	};

	skillsSet = dynamic_cast<SkillsSet *>(ward->getComponent(SkillsSet::NAME));

	return true;
}

void ShipPlayer::update(float dt)
{

}

//movement interface
float ShipPlayer::getVelocity()
{
	return engine->getCurrMovVelocity();
}

float ShipPlayer::getMaxVelocity()
{
	return engine->getMaxMovVelocity();
}

void ShipPlayer::setVelocity(float velocity)
{
	engine->setCurrMovVelocity(velocity);
}

//rotation interface
float ShipPlayer::getRotationDirection()
{
	return engine->getRotDirection();
}

void ShipPlayer::setLeftRotation()
{
	engine->setLeftRotDirection();
}

void ShipPlayer::setRightRotation()
{
	engine->setRightRotDirection();
}

void ShipPlayer::turnOnAngle(float angle)
{
	engine->turnToAngle(angle);
}

float ShipPlayer::getAngle()
{
	return engine->getRotAngle();
}

void ShipPlayer::resetRotDirection()
{
	engine->resetRotDirection();
}