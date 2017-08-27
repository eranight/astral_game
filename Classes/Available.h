#ifndef __AVAILABLE_H__
#define __AVAILABLE_H__

#include "Property.h"

namespace astral_game
{
	class Available : public Property
	{
	public:
		Available();
		void setEnable();  //the owner can be a target
		void setDisable(); //the owner can't be a target, but it still exists in the sector
		void setInvalid(); //the owner can't be a target and should be destroyed
	};
}

#endif //__AVAILABLE_H__