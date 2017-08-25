#include "Controller.h"

USING_NS_CC;
using namespace astral_game;

bool Controller::init(const std::string & name)
{
	if (!Component::init())
		return false;
	setName(name);
	return true;
}