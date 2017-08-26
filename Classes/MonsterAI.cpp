#include "MonsterAI.h"
#include "Engine.h"

USING_NS_CC;
using namespace astral_game;

bool MonsterAI::initWithWard(Node * ward)
{
	this->ward = ward;
	scriptMode = 1;
	auto engine = dynamic_cast<Engine *>(ward->getComponent(Engine::NAME));
	calmScript = std::make_shared<CalmBehaviorScript>(engine);

	return true;
}

void MonsterAI::update(float dt)
{
	if (scriptMode == 1)
		calmScript->update(dt);
	//else if (scriptMode == 2) ...
}

MonsterAI::CalmBehaviorScript::CalmBehaviorScript(Engine * engine) :
	engine(engine),
	mode(1)
{
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