#ifndef __CANNON_H__
#define __CANNON_H__

#include "Skill.h"
#include "cocos2d.h"

namespace astral_game
{
	class Cannon : public Skill
	{
	public:
		Cannon(cocos2d::Vec2 position, float rechargeTime);
		void update(float dt) override;
	public:
		void shot(cocos2d::Node * owner, cocos2d::Node * target);
		bool isReady() { return ready; }
		const cocos2d::Vec2 & getPosition() { return position; }
	private:
		Timer rechargeTimer;
		bool ready;
		cocos2d::Vec2 position;
	};
}

#endif //__CANNON_H__