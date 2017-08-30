#include "Descriptor.h"

USING_NS_CC;
using namespace astral_game;

Descriptor::Descriptor(Node * owner, SectorTag tag) :
	owner(owner),
	tag(tag)
{
}

Descriptor * Descriptor::create(Node * owner, SectorTag tag)
{
	Descriptor * pRet = new (std::nothrow) Descriptor(owner, tag);
	if (pRet != nullptr)
		pRet->autorelease();
	return pRet;
}

std::shared_ptr<Property> Descriptor::getProperty(PropertyTag tag)
{
	auto iter = find_if(properties.begin(), properties.end(),
		[tag](const std::shared_ptr<Property> & property) { return property->getPropertyTag() == tag; });
	if (iter != properties.end())
		return *iter;
	else
		return nullptr;
}

bool Descriptor::addProperty(Property * property)
{
	if (getProperty(property->getPropertyTag()) == nullptr)
	{
		auto propertyPtr = std::shared_ptr<Property>(property);
		propertyPtr->setOwner(owner);
		properties.push_back(std::shared_ptr<Property>(property));
		return true;
	}
	return false;
}