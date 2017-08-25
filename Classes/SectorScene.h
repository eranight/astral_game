#ifndef __SECTORSCENE_H__
#define __SECTORSCENE_H__

#include <vector>
#include <memory>

#include "cocos2d.h"

namespace astral_game
{
	class Sector;
	class Manager;

	class SectorScene : public cocos2d::Layer
	{
	public:
		static cocos2d::Scene* createScene();
		bool init() override;
		CREATE_FUNC(SectorScene);
	public:
		Sector * getSector();
	private:
		std::vector<std::shared_ptr<Manager>> managers;
		void createShip();
	};
}


#endif //__SECTORSCENE_H__