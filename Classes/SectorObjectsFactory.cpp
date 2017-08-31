#include "SectorObjectsFactory.h"
#include "Utils.h"
#include "Engine.h"
#include "Cannon.h"
#include "SkillsSet.h"
#include "Tracing.h"
#include "Hittable.h"
#include "Available.h"
#include "Descriptor.h"

#include <vector>

USING_NS_CC;
using namespace astral_game;

std::shared_ptr<SectorObjectsFactory> SectorObjectsFactory::factory = std::make_shared<SectorObjectsFactory>();

Node * SectorObjectsFactory::createShip()
{
	Node * ship = Node::create();
	Sprite * shipSprite = Sprite::create("ship.png");
	ship->addChild(shipSprite);
	Descriptor * descriptor = Descriptor::create(ship, SectorTag::SHIP);
	ship->setUserObject(descriptor);
	descriptor->addProperty<Hittable>(500);
	descriptor->addProperty<Available>();
	
	Engine * engine = Engine::create();
	engine->setMaxMovVelocity(SF(140.0f));
	engine->setRotVelocity(SF(70.0f));
	ship->addComponent(engine);

	SkillsSet * skillsSet = SkillsSet::create();
	ship->addComponent(skillsSet);

	std::vector<Vec2> vectorOfCanonsPos{ Vec2(SF(-10.0f), SF(14.0f)), Vec2(SF(10.0f), SF(14.0f)), Vec2(SF(-10.0f), SF(-14.0f)), Vec2(SF(10.0f), SF(-14.0f)) };
	for (auto & pos : vectorOfCanonsPos)
	{
		skillsSet->vectorOfSkills.push_back(std::dynamic_pointer_cast<Skill>(std::make_shared<Cannon>(pos, 2.0f)));
		auto canonPoint = DrawNode::create();
		canonPoint->drawPoint(Vec2::ZERO, 3.0f, Color4F::RED);
		canonPoint->setPosition(pos);
		ship->addChild(canonPoint);
	}

	return ship;
}

Node * SectorObjectsFactory::createMonster()
{
	auto monster = Node::create();
	auto monsterSprite = Sprite::create("monster.png");
	monster->addChild(monsterSprite);
	Descriptor * descriptor = Descriptor::create(monster, SectorTag::MONSTER);
	monster->setUserObject(descriptor);
	descriptor->addProperty<Hittable>(500);
	descriptor->addProperty<Available>();
	
	Engine * engine = Engine::create(); //FIXME: add max velocity as argument to the create method!
	engine->setMaxMovVelocity(SF(140.0f));
	engine->setRotVelocity(SF(70.0f));
	monster->addComponent(engine);

	SkillsSet * skillsSet = SkillsSet::create();
	monster->addComponent(skillsSet);

	Vec2 canonPos = Vec2(0.0f, monsterSprite->getContentSize().height * 0.5f);
	skillsSet->vectorOfSkills.push_back(std::dynamic_pointer_cast<Skill>(std::make_shared<Cannon>(canonPos, 2.0f)));

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

	Descriptor * descriptor = Descriptor::create(bullet, SectorTag::BULLET);
	bullet->setUserObject(descriptor);
	descriptor->addProperty<Available>();

	Engine * engine = Engine::create();
	engine->setMaxMovVelocity(SF(300.0f));
	engine->setRotVelocity(SF(70.0f));
	bullet->addComponent(engine);

	Tracing * tracing = Tracing::create(SF(20.0f), 0.0f);
	bullet->addComponent(tracing);

	return bullet;
}