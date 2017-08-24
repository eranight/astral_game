#include "Sector.h"

USING_NS_CC;
using namespace astral_game;

Sector * Sector::currentSector = nullptr;

Sector::Sector(float radius) :
	radius(radius)
{
}

Sector * Sector::create(float radius)
{
	auto ret = new (std::nothrow) Sector(radius);
	if (ret != nullptr && ret->init())
		ret->autorelease();
	else
		CC_SAFE_DELETE(ret);
	return ret;
}

bool Sector::init()
{
	if (!Node::init())
		return false;
	currentSector = this;
	
	auto background = Sprite::create("wall4.png");
	background->setPosition(Vec2::ZERO);
	this->addChild(background);

	auto circleBorder = DrawNode::create();
	circleBorder->drawCircle(Vec2::ZERO, radius, 0.0f, 36, false, Color4F::GREEN);
	circleBorder->setPosition(Vec2::ZERO);
	this->addChild(circleBorder);
	
	return true;
}

void Sector::update(float dt)
{

}

bool Sector::checkValidPosition(const cocos2d::Vec2 & pos)
{
	return pos.length() < radius;
}