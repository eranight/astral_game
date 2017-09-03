#ifndef __CLICKABLE_H__
#define __CLICKABLE_H__

#include <functional>

#include "Property.h"

namespace astral_game
{
	class Clickable : public Property
	{
	public:
		Clickable(float radius);
	public:
		float getRadius() { return radius; }
		bool click(const cocos2d::Vec2 & pos);
	public:
		std::function<void()> onClick;
	private:
		float radius;
	};
}

#endif //__CLICKABLE_H__