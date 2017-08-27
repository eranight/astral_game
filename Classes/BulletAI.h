#ifndef __BULLETAI_H__
#define __BULLETAI_H__

#include "Manager.h"

namespace astral_game
{
	class BulletAI : public Manager
	{
	public:
		bool initWithWard(cocos2d::Node * ward) override;
		void receive(Notification notification, cocos2d::Node * sender) override {}
		void update(float dt) override;
	private:
		bool shouldBeDestroyed;
	};
}

#endif //__BULLETAI_H__