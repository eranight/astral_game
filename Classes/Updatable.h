#ifndef __UPDATABLE_H__
#define __UPDATABLE_H__

namespace astral_game 
{
	
	class Updatable
	{
	public:
		virtual void update(float dt) = 0;
	};

}

#endif //__UPDATABLE_H__