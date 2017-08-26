#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <functional>

#include "Controller.h"

namespace astral_game
{
	class Engine : public Controller
	{
	protected:
		Engine();
	public:
		static Engine * create();
		bool init();
		void update(float dt) override;
	public:
		static const std::string NAME;
		std::function<void(const cocos2d::Vec2 &)> edgeSectorCollisionReaction;
	public:		//rotation interface
		float getRotVelocity() { return rotVelocity; }
		float getRotDirection() { return rotDirection; }
		float getRotAngle();
		void  setRotVelocity(float rotVelocity) { this->rotVelocity = rotVelocity; }
		void  setRightRotDirection() { rotDirection = 1.0f; }
		void  setLeftRotDirection()  { rotDirection = -1.0f; }
		void  resetRotDirection() { rotDirection = 0.0f; }
		void  turnToAngle(float angle);
	public:		//movement interface
		float getMaxMovVelocity()  { return maxMovVelocity; }
		float getCurrMovVelocity() { return currMovVelocity; }
		const cocos2d::Vec2 & getMovDirection() { return movDirection; }
		//currMovVelocity can't be grater maxMovVelocity
		void setMaxMovVelocity(float maxMovVelocity);
		void setCurrMovVelocity(float currMovVelocity);
		void setMovDirection(const cocos2d::Vec2 & movDirection);
	private:	//rotation implementation
		float angle; //current angle in degrees
		float rotDirection; //1.0f - cw-rotation, -1.0f - ccw-rotation
		float rotVelocity;
	private:	//movement implementation
		cocos2d::Vec2 movDirection;
		float maxMovVelocity;
		float currMovVelocity;
	};
}


#endif //__ENGINE_H__