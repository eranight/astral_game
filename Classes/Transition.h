#ifndef __TRANSITION_H__
#define __TRANSITION_H__

#include <memory>
#include "Condition.h"

namespace astral_game
{
	class State;

	class Transition
	{
	public:
		Transition(std::shared_ptr<Condition> condition, std::shared_ptr<State> targetState) : condition(condition), targetState(targetState) {};
	public:
		bool isTriggered() { return condition->test(); }
		std::shared_ptr<State> getTargetState() { return targetState; }
	private:
		std::shared_ptr<Condition> condition;
		std::shared_ptr<State> targetState;
	};

}

#endif //__TRANSITION_H__