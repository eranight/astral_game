#ifndef __TIMER_H__
#define __TIMER_H__

namespace astral_game
{

	class Timer
	{
	public:
		Timer() : time(0.0f), timer(0.0f) {}
		void tick(float dt) { if (timer < time) timer += dt; }
		bool isOver() { return timer >= time; }
		void reset() { this->timer = 0.0f; }
		void reset(float time) { this->time = time; this->timer = 0.0f; }
	private:
		float time;
		float timer;
	};

}

#endif //__TIMER_H__