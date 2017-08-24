#ifndef __SECTOR_H__
#define __SECTOR_H__

#include "cocos2d.h"

#define SF(num) num / Director::getInstance()->getContentScaleFactor()

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
	public:
		static Sector * getSector() { return currentSector; }
	private:
		static Sector * currentSector;
	private:
		float radius;
	};
}

#endif //__SECTOR_H__