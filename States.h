#pragma once
#include 
#include "skills.h"

#define implements public

namespace MyStrategy
{
	class State
	{
		State();
		virtual ~State() {};
		virtual void Enter() = 0;
		virtual State* checkState(BeliefState *state) {};

	private:
		State * _state;
	};
}
