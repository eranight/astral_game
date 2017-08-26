#ifndef __MANAGER_H__
#define __MANAGER_H__

#include "cocos2d.h"
#include "Utils.h"

namespace astral_game
{
	class Manager
	{
	public:
		Manager() = default;
		virtual ~Manager() = default;
	public:
		cocos2d::Node * getWard() { return ward; }
		virtual bool initWithWard(cocos2d::Node * ward) = 0;
		virtual void receive(Notification notification, cocos2d::Node * sender) = 0;
		virtual void update(float dt) {}
	protected:
		cocos2d::Node * ward;
	};
}

#endif //__MANAGER_H__