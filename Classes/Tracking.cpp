#include "Tracking.h"

USING_NS_CC;
using namespace astral_game;

const std::string Tracking::NAME = "tracing";

Tracking::Tracking(float trackingRadius, float trackingAngle) :
	trackingRadius(trackingRadius),
	trackingAngle(trackingAngle),
	targetIsInTrackingZone(false),
	targetIsOutTrackingZone(true),
	target(nullptr)
{
}

Tracking * Tracking::create(float trackingRadius, float trackingAngle)
{
	auto pRet = new (std::nothrow) Tracking(trackingRadius, trackingAngle);
	if (pRet != nullptr && pRet->init())
		pRet->autorelease();
	else if (pRet != nullptr)
	{
		delete pRet;
		pRet = nullptr;
	}
	return pRet;
}

bool Tracking::init()
{
	if (!Controller::init(NAME))
		return false;
	return true;
}

void Tracking::update(float dt)
{
	if (target != nullptr)
	{
		float dist = target->getPosition().distance(_owner->getPosition());
		//FIXME: obtain the angle
		if (dist <= trackingRadius)
		{
			if (!targetIsInTrackingZone)
			{
				if (targetIsInTrakcingZoneReaction != nullptr)
					targetIsInTrakcingZoneReaction(target);
				targetIsInTrackingZone = true;
				targetIsOutTrackingZone = false;
			}
		}
		else if (!targetIsOutTrackingZone)
		{
			if (targetIsOutTrackingZoneReaction != nullptr)
				targetIsOutTrackingZoneReaction(target);
			targetIsInTrackingZone = false;
			targetIsOutTrackingZone = true;
		}
	}
}

void Tracking::resetTracking()
{
	targetIsInTrackingZone = false;
	targetIsOutTrackingZone = true;
}