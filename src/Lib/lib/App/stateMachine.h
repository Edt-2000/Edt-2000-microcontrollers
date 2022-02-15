#pragma once

#include "State.h"

namespace App
{
class StateMachine
{
public:
	StateMachine() : _state(State::begin){};

	inline State current()
	{
		return _state;
	}

	inline void step()
	{
		State newState;

		switch (_state)
		{
		case State::begin:
			newState = State::networking;
			break;
		case State::networking:
			newState = State::specifics;
			break;
		case State::specifics:
			newState = State::initialized;
			break;
		case State::initialized:
			newState = State::run;
			break;
		case State::run:
			newState = State::run;
			break;
		default:
			newState = State::begin;
			break;
		}

		_state = newState;
	};

private:
	State _state;
};
} // namespace App