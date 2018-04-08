#ifndef __CONDITION_H__
#define __CONDITION_H__

namespace astral_game
{

	class Condition
	{
	public:
		virtual bool test() = 0;
	};

}

#endif //__CONDITION_H__