#ifndef __STATE_H__
#define __STATE_H__

#include <vector>

#include "Updatable.h"
#include "Transition.h"

namespace astral_game
{

	class State : public Updatable
	{
	public:
		virtual void init() = 0; //entry point
		const std::vector<std::shared_ptr<Transition>> & getTransitions() { return transitions; }
	private:
		std::vector<std::shared_ptr<Transition>> transitions;
	};

}

#endif //__STATE_H__