#ifndef __MONSTER_AI__
#define __MONSTER_AI__

#include <memory>

#include "cocos2d.h"
#include "Manager.h"
#include "Utils.h"

namespace astral_game
{
	class Engine;

	class MonsterAI : public Manager
	{
	public:
		bool initWithWard(cocos2d::Node * ward) override;
		void receive(Notification notification, cocos2d::Node * sender) override {} //FIXME
		void update(float dt) override;
	private:

		class CalmBehaviorScript
		{
		public:
			CalmBehaviorScript(Engine * engine);
			void update(float dt);
		private:
			//1 - relax, 2 - movement
			int mode;
			Engine * engine;
			Timer relaxTimer;
			Timer movTimer;
			Timer * currTimer;
			void randimizeTimer(Timer & timer);
		};
		std::shared_ptr<CalmBehaviorScript> calmScript;
		int scriptMode; //1 - calm, 2 - agressive
	};
}

#endif //__MONSTER_AI__