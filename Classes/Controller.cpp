#include "Controller.h"

USING_NS_CC;
using namespace astral_game;

bool Controller::init(Node * owner, const std::string & name)
{
	if (!Component::init())
		return false;
	setOwner(owner);
	setName(name);
	return true;
}