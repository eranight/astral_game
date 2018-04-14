#include "SubStateMachine.h"

using namespace astral_game;

void SubStateMachine::entry() {
	currentState->entry();
}

void SubStateMachine::exit() {
	currentState->exit();
}