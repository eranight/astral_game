#include "StateMachine.h"

using namespace astral_game;

void StateMachine::update(float dt) {
	std::shared_ptr<Transition> triggeredTransition = nullptr;
	for (auto & transition : currentState->getTransitions()) {
		if (transition->isTriggered()) {
			triggeredTransition = transition;
			break;
		}
	}
	if (triggeredTransition != nullptr) {
		currentState->exit();
		currentState = triggeredTransition->getTargetState();
		currentState->entry();
	}
	else {
		currentState->update(dt);
	}
}