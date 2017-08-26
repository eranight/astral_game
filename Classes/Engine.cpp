#include "Engine.h"
#include "Sector.h"

USING_NS_CC;
using namespace astral_game;

const std::string Engine::NAME = "engine";

Engine::Engine() :
	edgeSectorCollisionReaction(nullptr),
	angle(0.0f),
	rotDirection(0.0f),
	rotVelocity(0.0f),
	movDirection(Vec2(0.0f, 1.0f)),
	maxMovVelocity(0.0f),
	currMovVelocity(0.0f)
{
	angle = CC_RADIANS_TO_DEGREES(movDirection.getAngle());
}

Engine * Engine::create()
{
	auto pRet = new (std::nothrow) Engine();
	if (pRet != nullptr && pRet->init())
		pRet->autorelease();
	else if (pRet != nullptr)
	{
		delete pRet;
		pRet = nullptr;
	}
	return pRet;
}

bool Engine::init()
{
	if (!Controller::init(NAME))
		return false;
	return true;
}

void Engine::update(float dt)
{
	if (rotDirection != 0.0f)
	{
		movDirection = movDirection.rotateByAngle(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(rotVelocity * dt * rotDirection));
		_owner->setRotation(-(CC_RADIANS_TO_DEGREES(movDirection.getAngle()) - angle));
	}
		//turnToAngle(angle + rotVelocity * dt * rotDirection);
	if (currMovVelocity != 0.0f)
	{
		auto nextPos = _owner->getPosition() + movDirection * currMovVelocity * dt;
		//if next pos is in sector we change user's position
		if (Sector::getSector()->checkValidPosition(nextPos))
			_owner->setPosition(nextPos);
		//if next pos is out of sector we call collision reaction lambda if it exist
		else if (edgeSectorCollisionReaction != nullptr)
			edgeSectorCollisionReaction(nextPos);
		//else we just stop movement
		else
			currMovVelocity = 0.0f;
	}
}

//rotation interface

float Engine::getRotAngle()
{
	return -(CC_RADIANS_TO_DEGREES(movDirection.getAngle()) - this->angle);
}

void Engine::turnToAngle(float angle)
{
	//in radian positiv angle - ccw, negative - cw
	//in dergees positiv angle - cw, negative - ccw
	//that is why it need minus!
	//movDirection = movDirection.rotateByAngle(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(angle));
	//_owner->setRotation(-(CC_RADIANS_TO_DEGREES(movDirection.getAngle()) - this->angle));
	movDirection = Vec2::forAngle(CC_DEGREES_TO_RADIANS(angle));
	_owner->setRotation(-(angle - this->angle));
}

//movement interface

void Engine::setMaxMovVelocity(float maxMovVelocity)
{
	CCASSERT(maxMovVelocity >= 0.0f, "maxMovVelocity shouldn't be nagative");

	//if current velocity equals max velocity but no equal zero, we need to reduce it
	if (this->maxMovVelocity < maxMovVelocity && currMovVelocity != 0.0f && currMovVelocity == this->maxMovVelocity)
	{
		currMovVelocity = maxMovVelocity;
	}
	this->maxMovVelocity = maxMovVelocity;
}

void Engine::setCurrMovVelocity(float currMovVelocity)
{
	CCASSERT(currMovVelocity >= 0.0f, "currMovVelocity shouldn't be nagative");

	//current velocity can't be greater max velocity
	if (currMovVelocity > maxMovVelocity)
		currMovVelocity = maxMovVelocity;
	this->currMovVelocity = currMovVelocity;
}

void Engine::setMovDirection(const Vec2 & movDirection)
{
	this->movDirection = movDirection.getNormalized();
}