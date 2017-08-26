#ifndef __SECTOROBJECTSFACTORY_H__
#define __SECTOROBJECTSFACTORY_H__

#include <memory>

#include "cocos2d.h"

namespace astral_game
{
	class SectorObjectsFactory
	{
	private:
		SectorObjectsFactory() = default;
	public:
		static std::shared_ptr<SectorObjectsFactory> getInstance() { return factory; }
	public: //this methods should get some stream with a description of the object that they should return
		cocos2d::Node * createShip();
		cocos2d::Node * createMonster();
		cocos2d::Node * createBullet();
	private:
		static std::shared_ptr<SectorObjectsFactory> factory;
	};
}

#endif //__SECTOROBJECTSFACTORY_H__