#ifndef __SHIPPLAYER_H__
#define __SHIPPLAYER_H__

#include "cocos2d.h"
#include "Manager.h"

namespace astral_game
{
	class Engine;
	class SkillsSet;

	class ShipPlayer : public Manager
	{
	public:
		bool initWithWard(cocos2d::Node * ward) override;
		void receive(Notification notification, cocos2d::Node * sender) override {}//FIXME
		void update(float dt) override;
	public: //movement interface
		float getVelocity();
		float getMaxVelocity();
		void setVelocity(float velocity);
	public: //rotation interface
		float getRotationDirection();
		void setLeftRotation();
		void setRightRotation();
		void turnOnAngle(float angle);
		float getAngle();
		void resetRotDirection();
	private:
		Engine * engine;
		SkillsSet * skillsSet;
	};
}

#endif //__SHIPPLAYER_H__