#ifndef __SECTORSCENE_H__
#define __SECTORSCENE_H__

#include <vector>
#include <memory>

#include "cocos2d.h"
#include "Utils.h"

namespace astral_game
{
	class Sector;
	class Manager;

	class SectorScene : public cocos2d::Layer
	{
	public:
		static cocos2d::Scene* createScene();
		bool init() override;
		void update(float dt) override;
		bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event) override;
		void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event) override;
		CREATE_FUNC(SectorScene);
	public:
		Sector * getSector();
		static std::string NAME;
		void receiveNotification(Notification notification, cocos2d::Node * sender);
		void createBullet(cocos2d::Node * sender, const cocos2d::Vec2 & position);
	private:
		std::vector<std::shared_ptr<Manager>> managers;
		void createShip();
		void createMonster();
	};
}


#endif //__SECTORSCENE_H__