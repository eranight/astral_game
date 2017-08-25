#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <string>

#include "cocos2d.h"
#include "Notifier.h"

namespace astral_game
{
	class Controller : public cocos2d::Component, public Notifier
	{
	public:
		bool init(const std::string & name);
	};
}

#endif //__CONTROLLER_H__