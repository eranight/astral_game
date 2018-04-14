#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__

#include <vector>
#include <memory>

#include "State.h"

namespace astral_game
{

	class StateMachine : public Updatable
	{
	public:
		virtual void update(float dt) override;
	protected:
		std::vector<std::shared_ptr<State>> states;
		std::shared_ptr<State> currentState;
		std::shared_ptr<State> initialState;
	};

}

#endif //__STATE_MACHINE_H__