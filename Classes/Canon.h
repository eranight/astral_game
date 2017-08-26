#ifndef __CANON_H__
#define __CANON_H__

#include <functional>

#include "Controller.h"

namespace astral_game
{
	class Canon : public Controller
	{
	protected:
		Canon(cocos2d::Vec2 position, float rechargeTime);
	public:
		static Canon * create(cocos2d::Vec2 position, float rechargeTime);
		bool init();
		void update(float dt) override;
	public:
		static const std::string NAME;
		std::function<void()> rechargeComplete;
	public:
		void shot(cocos2d::Node * target); //FIXME: how does it work?
		bool isReady() { return ready; }
		float getRechargeTime() { return rechargeTime; }
		const cocos2d::Vec2 & getPosition() { return position; }
	private:
		float rechargeTime;
		float rechargeTimer;
	private:
		bool ready;
		cocos2d::Vec2 position;
	};
}

#endif //__CANON_H__