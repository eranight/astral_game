#ifndef __TRACING_H__
#define __TRACING_H__

#include <functional>

#include "Controller.h"

namespace astral_game
{
	class Tracing : public Controller
	{
	protected:
		Tracing(float trackingRadius, float trackingAngle);
	public:
		static Tracing * create(float trackingRadius, float trackingAngle);
		bool init();
		void update(float dt) override;
	public:
		static const std::string NAME;
		std::function<void(cocos2d::Node *)> targetIsInTrakcingZoneReaction;
		std::function<void(cocos2d::Node *)> targetIsOutTrackingZoneReaction;
	public:
		void captureTarget(cocos2d::Node * target) { this->target = target; }
		void loseTarget() { target = nullptr; }
		float getTrackingRadius() { return trackingRadius; }
		float getTrackingAngle() { return trackingAngle; }
	private:
		cocos2d::Node * target;
		float trackingRadius;
		float trackingAngle;

		bool targetIsInTrackingZone;
		bool targetIsOutTrackingZone;
	};
}

#endif //__TRACING_H__