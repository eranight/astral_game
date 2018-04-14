#ifndef __SUB_STATE_MACHINE_H__
#define __SUB_STATE_MACHINE_H__

#include "StateMachine.h"

namespace astral_game {

	class SubStateMachine : public StateMachine, public State 
	{
	public:
		virtual void entry() override;
		virtual void exit() override;
	};

}

#endif //__SUB_STATE_MACHINE_H__