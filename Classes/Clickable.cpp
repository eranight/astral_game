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
	bool clickResult = (getOwner()->getPosition() - pos).length() <= radius;
	if (clickResult && onClick != nullptr)
		onClick();
	return clickResult;
}