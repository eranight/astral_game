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

Canon * Canon::create(Vec2 position, float rechargeTime)
{
	auto pRet = new (std::nothrow) Canon(position, rechargeTime);
	if (pRet != nullptr && pRet->init())
		pRet->autorelease();
	else if (pRet != nullptr)
	{
		delete pRet;
		pRet = nullptr;
	}
	return pRet;
}

bool Canon::init()
{
	if (!Controller::init(NAME))
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