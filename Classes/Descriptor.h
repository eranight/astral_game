#ifndef __DESCRIPTOR_H__
#define __DESCRIPTOR_H__

#include <vector>
#include <memory>
#include <algorithm>

#include "Utils.h"
#include "Property.h"
#include "cocos2d.h"

namespace astral_game
{
	class Property;

	class Descriptor : public cocos2d::Ref
	{
	private:
		Descriptor(cocos2d::Node * owner);
	public:
		static Descriptor * create(cocos2d::Node * owner);
	public: //Properties interface
		std::shared_ptr<Property> getProperty(PropertyTag tag);
		template<typename T>
		std::shared_ptr<T> getProperty(PropertyTag tag)
		{
			auto iter = std::find_if(properties.begin(), properties.end(),
				[tag](const std::shared_ptr<Property> & property) { return property->getPropertyTag() == tag; }
			);
			if (iter != properties.end())
				return std::dynamic_pointer_cast<T>(*iter);
			else
				return nullptr;
		}
		bool addProperty(Property * property);
	private:
		std::vector<std::shared_ptr<Property>> properties;
		cocos2d::Node * owner;
	};
}

#endif //__DESCRIPTOR_H__