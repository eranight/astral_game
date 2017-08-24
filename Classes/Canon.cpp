#include "Canon.h"

USING_NS_CC;
using namespace astral_game;

const std::string Canon::NAME = "canon";

Canon::Canon(Vec2 position, float rechargeTime) :
	position(position),
	rechargeTime(rechargeTime),
	rechargeTimer(0.0f),
	rechargeComplete(nullptr),
	ready(true)
{
}

Canon * Canon::create(Node * owner, Vec2 position, float rechargeTime)
{
	auto pRet = new (std::nothrow) Canon(position, rechargeTime);
	if (pRet != nullptr && pRet->init(owner))
		pRet->autorelease();
	else if (pRet != nullptr)
	{
		delete pRet;
		pRet = nullptr;
	}
	return pRet;
}

bool Canon::init(Node * owner)
{
	if (!Controller::init(owner, NAME))
		return false;
	return true;
}

void Canon::update(float dt)
{
	if (!ready)
	{
		if ((rechargeTimer += dt) >= rechargeTime)
		{
			ready = true;
			rechargeTimer = 0.0f;
			if (rechargeComplete != nullptr) rechargeComplete();
		}
	}
}

void Canon::shot()
{

}