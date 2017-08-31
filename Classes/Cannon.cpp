#include "Cannon.h"
#include "SectorScene.h"

USING_NS_CC;
using namespace astral_game;

Cannon::Cannon(Vec2 position, float rechargeTime) :
	Skill(SkillTag::CANNON),
	position(position),
	ready(true)
{
	rechargeTimer.reset(rechargeTime);
}

void Cannon::update(float dt)
{
	if (!ready)
	{
		rechargeTimer.tick(dt);
		if (rechargeTimer.isOver())
		{
			ready = true;
			rechargeTimer.reset();
		}
	}
}

void Cannon::shot(Node * owner, Node * target)
{
	auto sectorScene = dynamic_cast<SectorScene *>(Director::getInstance()->getRunningScene()->getChildByName(SectorScene::NAME));
	sectorScene->createBullet(owner);

	/*auto bullet = SectorObjectsFactory::getInstance()->createBullet();
	bullet->setPosition(_owner->getParent()->convertToNodeSpace(_owner->convertToWorldSpace(position)));
	bullet->setCameraMask((unsigned short)CameraFlag::USER1, true);
	auto engine = dynamic_cast<Engine *>(bullet->getComponent(Engine::NAME));
	engine->setMovDirection((target->getPosition() - _owner->getPosition()).getNormalized());
	engine->setCurrMovVelocity(engine->getMaxMovVelocity());

	auto tracing = dynamic_cast<Tracing *>(bullet->getComponent(Tracing::NAME));
	tracing->captureTarget(target);

	_owner->getParent()->addChild(bullet);*/

	ready = false;
}