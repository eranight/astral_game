#ifndef __HITTABLE_H__
#define __HITTABLE_H__

#include <functional>

#include "Utils.h"
#include "Property.h"

namespace astral_game
{
	class Hittable : public Property
	{
	public:
		Hittable(int maxHp);
	public: //current hp interface
		int getCurrentHp() { return currentHp; }
		void impactDamage(int damage);
		void impactHealing(int healing);
		bool isDead() { return currentHp == 0; }
	public: //max hp interface
		int getMaxHp() { return maxHp; }
	public: //callbacks
		std::function<void()> onDead;
	private:
		int maxHp;
		int currentHp;
	};
}

#endif //__HITTABLE_H__