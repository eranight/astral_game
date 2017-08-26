#ifndef __UTILS_H__
#define __UTILS_H__

#define TAGINT(tag) static_cast<int>(tag)
#define SF(num) num / Director::getInstance()->getContentScaleFactor()

namespace astral_game
{
	enum class Notification
	{
		HITTABLE_DEAD,
		COUNT
	};

	enum class PropertyTag
	{
		HITTABLE,
		COUNT
	};

	enum class LayerTag
	{
		SECTOR,
		SHIP,
		COUNT
	};

	enum class SectorTag
	{
		SHIP,
		MONSTER,
		PORTAL,
		ISLAND,
		COUNT
	};

	class Timer
	{
	public:
		Timer() : time(0.0f), timer(0.0f) {}
		void tick(float dt) { if (timer < time) timer += dt; }
		bool isOver() { return timer >= time; }
		void reset(float time) { this->time = time; this->timer = 0.0f; }
	private:
		float time;
		float timer;
	};
}
	
#endif //__UTILS_H__