#include "BulletAI.h"
#include "Engine.h"
#include "Tracing.h"
#include "Descriptor.h"
#include "Available.h"

USING_NS_CC;
using namespace astral_game;

bool BulletAI::initWithWard(Node * ward)
{
	this->ward = ward;
	shouldBeDestroyed = false;
	auto engine = dynamic_cast<Engine *>(ward->getComponent(Engine::NAME));
	engine->edgeSectorCollisionReaction = [this](const Vec2 & pos)
	{
		this->shouldBeDestroyed = true;
	};
	auto tracing = dynamic_cast<Tracing *>(ward->getComponent(Tracing::NAME));
	tracing->targetIsInTrakcingZoneReaction = [this](Node * target)
	{
		this->shouldBeDestroyed = true;
	};

	return true;
}

void BulletAI::update(float dt)
{
	if (shouldBeDestroyed)
	{
		auto engine = dynamic_cast<Engine *>(ward->getComponent(Engine::NAME));
		engine->setCurrMovVelocity(0.0f);
		
		auto exp = ParticleSun::create();
		exp->setCameraMask((unsigned short)CameraFlag::USER1, true);
		exp->setAutoRemoveOnFinish(true);
		exp->setScale(0.1f);
		exp->setDuration(0.3f);
		exp->setPosition(ward->getPosition());
		ward->getParent()->addChild(exp, 3);
		exp->runAction(ScaleTo::create(0.16f, 0.75f));

		dynamic_cast<Descriptor *>(ward->getUserObject())->getProperty<Available>(PropertyTag::AVAILABLE)->setInvalid();
	}
}