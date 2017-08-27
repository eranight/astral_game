#include "Canon.h"
#include "Engine.h"
#include "Tracing.h"
#include "SectorObjectsFactory.h"

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

void Canon::shot(Node * target)
{
	auto bullet = SectorObjectsFactory::getInstance()->createBullet();
	bullet->setPosition(_owner->getParent()->convertToNodeSpace(_owner->convertToWorldSpace(position)));
	bullet->setCameraMask((unsigned short)CameraFlag::USER1, true);
	auto engine = dynamic_cast<Engine *>(bullet->getComponent(Engine::NAME));
	engine->setMovDirection((target->getPosition() - _owner->getPosition()).getNormalized());
	engine->setCurrMovVelocity(engine->getMaxMovVelocity());
	
	auto tracing = dynamic_cast<Tracing *>(bullet->getComponent(Tracing::NAME));
	tracing->captureTarget(target);

	_owner->getParent()->addChild(bullet);

	ready = false;
}