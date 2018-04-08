#include "MonsterAI.h"
#include "Engine.h"
#include "SkillsSet.h"
#include "Cannon.h"
#include "Tracking.h"
#include "Descriptor.h"
#include "Clickable.h"

USING_NS_CC;
using namespace astral_game;

void MonsterAI::receive(Notification notification, cocos2d::Node * sender)
{
	switch (notification)
	{
	case Notification::HITTABLE_DEAD:
	case Notification::AVAILABLE_DISABLE:
	case Notification::AVAILABLE_INVALID:
	{
														 auto tracing = dynamic_cast<Tracking *>(ward->getComponent(Tracking::NAME));
														 if (tracing->getTarget() == sender)
														 {
															 tracing->loseTarget();
															 switchedScriptMode = 1;
														 }
	}
		break;
	case Notification::AVAILABLE_ENABLE:
		break;
	default:
		break;
	}
}

bool MonsterAI::initWithWard(Node * ward)
{
	this->ward = ward;
	switchedScriptMode = 1;
	auto engine = dynamic_cast<Engine *>(ward->getComponent(Engine::NAME));
	auto skillsset = dynamic_cast<SkillsSet *>(ward->getComponent(SkillsSet::NAME));
	auto tracking = dynamic_cast<Tracking *>(ward->getComponent(Tracking::NAME));
	calmScript = std::make_shared<CalmBehaviorScript>(engine);
	agressiveScript = std::make_shared<AgressiveBehaviorScript>(engine, skillsset->getSkill<Cannon>(SkillTag::CANNON), tracking);

	auto descriptor = dynamic_cast<Descriptor *>(ward->getUserObject());
	auto clickable = descriptor->getProperty<Clickable>(PropertyTag::CLICKABLE);
	clickable->onClick = [ward]()
	{
		auto targetChild = ward->getChildByName("target");
		if (targetChild != nullptr) 
		{
			ward->removeChild(targetChild);
		}
		else
		{
			targetChild = Sprite::create("target.png");
			targetChild->setName("target");
			targetChild->setCameraMask(ward->getCameraMask());
			ward->addChild(targetChild);
		}
	};

	switchScriptMode();
	return true;
}

void MonsterAI::update(float dt)
{
	if (scriptMode != switchedScriptMode)
		switchScriptMode();
	if (scriptMode == 1)
		calmScript->update(dt);
	else if (scriptMode == 2)
		agressiveScript->update(dt);
}

void MonsterAI::switchScriptMode()
{
	scriptMode = switchedScriptMode;
	if (scriptMode == 1)
	{
		agressiveScript->stop();
		calmScript->start();
		auto tracing = dynamic_cast<Tracking *>(ward->getComponent(Tracking::NAME));
		tracing->setTrackingRadius(SF(300.0f));
		tracing->targetIsInTrakcingZoneReaction = [this](Node * target)
		{
			switchedScriptMode = 2;
		};
	}
	else if (scriptMode == 2)
	{
		calmScript->stop();
		agressiveScript->start();
	}
}

MonsterAI::CalmBehaviorScript::CalmBehaviorScript(Engine * engine) :
	engine(engine),
	mode(1)
{
}

void MonsterAI::CalmBehaviorScript::update(float dt)
{
	currTimer->tick(dt);
	if (currTimer->isOver())
	{
		if (mode == 1)
		{
			mode = 2;
			randimizeTimer(movTimer);
			engine->turnToAngle(RandomHelper::random_real(0.0f, 359.0f));
			engine->setCurrMovVelocity(engine->getMaxMovVelocity() * 0.5f);
			currTimer = &movTimer;
		}
		else if (mode == 2)
		{
			mode = 1;
			randimizeTimer(relaxTimer);
			engine->setCurrMovVelocity(0.0f);
			currTimer = &relaxTimer;
		}
	}
}

void MonsterAI::CalmBehaviorScript::randimizeTimer(astral_game::Timer & timer)
{
	timer.reset(RandomHelper::random_real<float>(1.0f, 2.0f));
}

void MonsterAI::CalmBehaviorScript::start()
{
	mode = 1;
	randimizeTimer(relaxTimer);
	currTimer = &relaxTimer;
	engine->setCurrMovVelocity(0.0f);
	engine->edgeSectorCollisionReaction = [this](const Vec2 & nextPos)
	{
		if (this->mode == 2)
		{
			this->engine->turnToAngle(this->engine->getRotAngle() + 180.0f);
		}
	};
}

void MonsterAI::CalmBehaviorScript::stop()
{
	engine->edgeSectorCollisionReaction = nullptr;
}

MonsterAI::AgressiveBehaviorScript::AgressiveBehaviorScript(Engine * engine, std::shared_ptr<Cannon> cannon, Tracking * tracking) :
	engine(engine),
	cannon(cannon),
	tracking(tracking),
	mode(1)
{
}

void MonsterAI::AgressiveBehaviorScript::update(float dt)
{
	Vec2 ownpos = engine->getOwner()->getPosition();
	Vec2 shppos = tracking->getTarget()->getPosition();
	float faceangle = CC_RADIANS_TO_DEGREES((shppos - ownpos).getAngle());
	//engine->getRotAngle();
	engine->turnToAngle(faceangle);
	if (mode == 2)
	{
		if (cannon->isReady())
		{
			cannon->shot(engine->getOwner(), tracking->getTarget());
		}
	}
}

void MonsterAI::AgressiveBehaviorScript::start()
{
	mode = 1;
	tracking->setTrackingRadius(SF(200.0f));
	tracking->resetTracking();
	engine->setCurrMovVelocity(engine->getMaxMovVelocity());
	CCLOG("AgressiveBehaviorScript::start");
	tracking->targetIsInTrakcingZoneReaction = [this](Node * target)
	{
		this->mode = 2;
		this->engine->setCurrMovVelocity(0.0f);
		this->tracking->setTrackingRadius(SF(250.0f));
	};
	tracking->targetIsOutTrackingZoneReaction = [this](Node * target)
	{
		this->mode = 1;
		this->engine->setCurrMovVelocity(this->engine->getMaxMovVelocity());
		tracking->setTrackingRadius(SF(200.0f));
	};
}

void MonsterAI::AgressiveBehaviorScript::stop()
{
	tracking->targetIsInTrakcingZoneReaction = nullptr;
	tracking->targetIsOutTrackingZoneReaction = nullptr;
}