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

	Canon * canon = Canon::create(Vec2(0.0f, monster->getContentSize().height * 0.5f), 2.0f);
	monster->addComponent(canon);

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
	ps->setLife(0.3f);
	ps->setLifeVar(0.1f);
	ps->setTotalParticles(200);
	ps->setEmitterMode(ParticleSystem::Mode::RADIUS);
	ps->setPosition(Vec2::ZERO);
	bullet->addChild(ps);

	Engine * engine = Engine::create();
	engine->setMaxMovVelocity(SF(180.0f));
	engine->setRotVelocity(SF(70.0f));
	engine->edgeSectorCollisionReaction = [bullet](const Vec2 & pos)
	{
		bullet->runAction(RemoveSelf::create());
	};
	bullet->addComponent(engine);

	return bullet;
}