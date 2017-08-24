#ifndef __PROPERTY_H__
#define __PROPERTY_H__

#include "Utils.h"
#include "Notifier.h"
#include "cocos2d.h"

namespace astral_game
{
	class Property : public Notifier
	{
	protected:
		Property(PropertyTag tag) : tag(tag) {}
	public:
		virtual ~Property() = default;
		PropertyTag getPropertyTag() const { return tag; }
		cocos2d::Node * getOwner() { return owner; }
		void setOwner(cocos2d::Node * owner) { this->owner = owner; }
	private:
		cocos2d::Node * owner;
		PropertyTag tag;
	};
}

#endif //__PROPERTY_H__