#include "ShipPlayer.h"
#include "Sector.h"
#include "Engine.h"
#include "Hittable.h"

USING_NS_CC;
using namespace astral_game;

bool ShipPlayer::initWithWard(Node * ward)
{
	auto engine = dynamic_cast<Engine *>(ward->getComponent(Engine::NAME));
	engine->edgeSectorCollisionReaction = [engine](const Vec2 & pos)
	{
		engine->setCurrMovVelocity(0.0f);
	};
}