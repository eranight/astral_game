#include "Clickable.h"

USING_NS_CC;
using namespace astral_game;

Clickable::Clickable(float radius) :
	Property(PropertyTag::CLICKABLE),
	radius(radius)
{
	
}

bool Clickable::click(const Vec2 & pos)
{
	return (getOwner()->getPosition() - pos).length() <= radius;
}