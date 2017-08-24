#ifndef __NOTIFIER_H__
#define __NOTIFIER_H__

#include "Utils.h"
#include "cocos2d.h"

namespace astral_game
{
	class Notifier
	{
	public:
		void notify(Notification notification, cocos2d::Node * node);
	};
}

#endif //__NOTIFIER_H__