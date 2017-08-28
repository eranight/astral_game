#ifndef __SECTOR_H__
#define __SECTOR_H__

#include "cocos2d.h"

namespace astral_game
{
	class Sector : public cocos2d::Node
	{
	protected:
		Sector(float radius);
	public:
		static Sector * create(float radius);
		bool init() override;
		void update(float dt) override;
	public: //sector math interface
		bool checkValidPosition(const cocos2d::Vec2 & pos);
	public: //sector data interface
		float getRadius() { return radius; }
		cocos2d::Camera * getShipCamera() { return shipCamera; }
		void setShipCamera(cocos2d::Camera * camera);
		cocos2d::Node * getShip() { return ship; }
	public:
		static Sector * getSector() { return currentSector; }
	private:
		static Sector * currentSector;
	private:
		float radius;
		cocos2d::Camera * shipCamera;
		cocos2d::Node * ship;
	};
}

#endif //__SECTOR_H__