#include "Available.h"

using namespace astral_game;

Available::Available() :
	Property(PropertyTag::AVAILABLE)
{
}

void Available::setEnable()
{
	notify(Notification::AVAILABLE_ENABLE, getOwner());
}

void Available::setDisable()
{
	notify(Notification::AVAILABLE_DISABLE, getOwner());
}

void Available::setInvalid()
{
	notify(Notification::AVAILABLE_INVALID, getOwner());
}