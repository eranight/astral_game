#ifndef __CLICKABLE_H__
#define __CLICKABLE_H__

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
	private:
		float radius;
	};
}

#endif //__CLICKABLE_H__