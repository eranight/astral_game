#include "SectorObjectsFactory.h"
#include "Utils.h"
#include "Engine.h"
#include "Canon.h"
#include "Tracing.h"
#include "Hittable.h"
#include "Descriptor.h"
#include "ShipPlayer.h"
#include "MonsterAI.h"

USING_NS_CC;
using namespace astral_game;

std::shared_ptr<SectorObjectsFactory> SectorObjectsFactory::factory = std::make_shared<SectorObjectsFactory>();

Node * SectorObjectsFactory::createShip()
{
	Node * ship = Node::create();
	Sprite * shipSprite = Sprite::create("ship.png");
	ship->addChild(shipSprite);
	Descriptor * descriptor = Descriptor::create(ship);
	ship->setUserObject(descriptor);
	descriptor->addProperty<Hittable>(500);
	Engine * engine = Engine::create();
	engine->setMaxMovVelocity(SF(140.0f));
	engine->setRotVelocity(SF(70.0f));
	ship->addComponent(engine);

	return ship;
}

Node * SectorObjectsFactory::createMonster()
{
	auto monster = Node::create();
	auto monsterSprite = Sprite::create("monster.png");
	monster->addChild(monsterSprite);
	Descriptor * descriptor = Descriptor::create(monster);
	monster->setUserObject(descriptor);
	descriptor->addProperty<Hittable>(500);
	Engine * engine = Engine::create(); //FIXME: add max velocity as argument to the create method!
	engine->setMaxMovVelocity(SF(140.0f));
	engine->setRotVelocity(SF(70.0f));
	monster->addComponent(engine);

	Vec2 canonPos = Vec2(0.0f, monsterSprite->getContentSize().height * 0.5f);

	Canon * canon = Canon::create(canonPos, 2.0f);
	monster->addComponent(canon);

	auto canonPoint = DrawNode::create();
	canonPoint->drawPoint(Vec2::ZERO, 3.0f, Color4F::RED);
	canonPoint->setPosition(canonPos);
	monster->addChild(canonPoint);

	Tracing * tracing = Tracing::create(SF(300.0f), 0.0f);
	monster->addComponent(tracing);

	return monster;
}

Node * SectorObjectsFactory::createBullet()
{
	auto bullet = Node::create();
	auto ps = ParticleFire::create();
	ps->setStartSize(SF(15.0f));
	ps->setEndSize(SF(1.0f));
	ps->setLife(0.15f);
	ps->setLifeVar(0.1f);
	ps->setTotalParticles(200);
	ps->setEmitterMode(ParticleSystem::Mode::RADIUS);
	ps->setPosition(Vec2::ZERO);
	bullet->addChild(ps);

	Engine * engine = Engine::create();
	engine->setMaxMovVelocity(SF(300.0f));
	engine->setRotVelocity(SF(70.0f));
	engine->edgeSectorCollisionReaction = [bullet](const Vec2 & pos)
	{
		auto exp = ParticleSun::create();
		exp->setCameraMask((unsigned short)CameraFlag::USER1, true);
		exp->setAutoRemoveOnFinish(true);
		exp->setScale(0.1f);
		exp->setDuration(0.3f);
		exp->setPosition(bullet->getPosition());
		bullet->getParent()->addChild(exp, 3);
		exp->runAction(ScaleTo::create(0.16f, 0.75f));

		bullet->runAction(RemoveSelf::create());
	};
	bullet->addComponent(engine);

	Tracing * tracing = Tracing::create(SF(20.0f), 0.0f);
	tracing->targetIsInTrakcingZoneReaction = [bullet](Node * target)
	{
		auto exp = ParticleSun::create();
		exp->setCameraMask((unsigned short)CameraFlag::USER1, true);
		exp->setAutoRemoveOnFinish(true);
		exp->setScale(0.1f);
		exp->setDuration(0.3f);
		exp->setPosition(bullet->getPosition());
		bullet->getParent()->addChild(exp, 3);
		exp->runAction(ScaleTo::create(0.16f, 0.75f));

		bullet->runAction(RemoveSelf::create());
	};
	bullet->addComponent(tracing);

	return bullet;
}