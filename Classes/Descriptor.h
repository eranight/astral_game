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
	class Descriptor : public cocos2d::Ref
	{
	private:
		Descriptor(cocos2d::Node * owner, SectorTag tag);
	public:
		static Descriptor * create(cocos2d::Node * owner, SectorTag tag);
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
		template<typename T, typename... Args>
		bool addProperty(Args && ... args)
		{
			auto propPtr = std::make_shared<T>(args...);
			if (getProperty(propPtr->getPropertyTag()) == nullptr)
			{
				properties.push_back(propPtr);
				propPtr->setOwner(owner);
				return true;
			}
			return false;
		}
		SectorTag getTag() { return tag; }
	private:
		std::vector<std::shared_ptr<Property>> properties;
		cocos2d::Node * owner;
		SectorTag tag;
	};
}

#endif //__DESCRIPTOR_H__