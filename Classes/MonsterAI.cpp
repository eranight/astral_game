#include "MonsterAI.h"
#include "Engine.h"
#include "Canon.h"
#include "Tracing.h"

USING_NS_CC;
using namespace astral_game;

bool MonsterAI::initWithWard(Node * ward)
{
	this->ward = ward;
	scriptMode = 1;
	auto engine = dynamic_cast<Engine *>(ward->getComponent(Engine::NAME));
	auto canon = dynamic_cast<Canon *>(ward->getComponent(Canon::NAME));
	auto tracing = dynamic_cast<Tracing *>(ward->getComponent(Tracing::NAME));
	calmScript = std::make_shared<CalmBehaviorScript>(engine);
	agressiveScript = std::make_shared<AgressiveBehaviorScript>(engine, canon, tracing);
	switchScriptMode(1);
	return true;
}

void MonsterAI::update(float dt)
{
	if (scriptMode == 1)
		calmScript->update(dt);
	else if (scriptMode == 2)
		agressiveScript->update(dt);
}

void MonsterAI::switchScriptMode(int scriptMode)
{
	this->scriptMode = scriptMode;
	if (this->scriptMode == 1)
	{
		agressiveScript->stop();
		calmScript->start();
		auto tracing = dynamic_cast<Tracing *>(ward->getComponent(Tracing::NAME));
		tracing->setTrackingRadius(SF(300.0f));
		tracing->targetIsInTrakcingZoneReaction = [this](Node * target)
		{
			this->switchScriptMode(2);
		};
	}
	else if (this->scriptMode == 2)
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

MonsterAI::AgressiveBehaviorScript::AgressiveBehaviorScript(Engine * engine, Canon * canon, Tracing * tracing) :
	engine(engine),
	canon(canon),
	tracing(tracing),
	mode(1)
{
}

void MonsterAI::AgressiveBehaviorScript::update(float dt)
{
	Vec2 ownpos = engine->getOwner()->getPosition();
	Vec2 shppos = tracing->getTarget()->getPosition();
	float faceangle = -CC_RADIANS_TO_DEGREES((shppos - ownpos).getAngle());
	engine->turnToAngle(faceangle);
	if (mode == 2)
	{
		//shot
	}
}

void MonsterAI::AgressiveBehaviorScript::start()
{
	mode = 1;
	tracing->setTrackingRadius(SF(200.0f));
	tracing->targetIsInTrakcingZoneReaction = [this](Node * target)
	{
		this->mode = 2;
		this->engine->setCurrMovVelocity(0.0f);
	};
	tracing->targetIsOutTrackingZoneReaction = [this](Node * target)
	{
		this->mode = 1;
		this->engine->setCurrMovVelocity(this->engine->getMaxMovVelocity());
	};
}

void MonsterAI::AgressiveBehaviorScript::stop()
{
	tracing->targetIsInTrakcingZoneReaction = nullptr;
	tracing->targetIsOutTrackingZoneReaction = nullptr;
}