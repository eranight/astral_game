#include "Tracing.h"

USING_NS_CC;
using namespace astral_game;

const std::string Tracing::NAME = "tracing";

Tracing::Tracing(float trackingRadius, float trackingAngle) :
	trackingRadius(trackingRadius),
	trackingAngle(trackingAngle),
	targetIsInTrackingZone(false),
	targetIsOutTrackingZone(true)
{
}

Tracing * Tracing::create(Node * owner, float trackingRadius, float trackingAngle)
{
	auto pRet = new (std::nothrow) Tracing(trackingRadius, trackingAngle);
	if (pRet != nullptr && pRet->init(owner))
		pRet->autorelease();
	else if (pRet != nullptr)
	{
		delete pRet;
		pRet = nullptr;
	}
	return pRet;
}

bool Tracing::init(Node * owner)
{
	if (!Controller::init(owner, NAME))
		return false;
	return true;
}

void Tracing::update(float dt)
{
	if (target != nullptr)
	{
		float dist = target->getPosition().distance(_owner->getPosition());
		//FIXME: obtain the angle
		if (dist <= trackingRadius && !targetIsInTrackingZone)
		{
			if (targetIsInTrakcingZoneReaction != nullptr)
				targetIsInTrakcingZoneReaction(target);
			targetIsInTrackingZone = true;
			targetIsOutTrackingZone = false;
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
