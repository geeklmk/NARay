/*
 * Project:    NARay
 * File:       SStateMachine.ixx
 * Author:     Luca 'aXon' Marchetti
 *
 * Description:
 *   A simple State Machine manager
 * 
 * 
 * License: LGPL 2.1
 *
 */

#include<map>
export module StateMachine;

namespace NARay
{
	export class State
	{
	public: 
		virtual void OnStateEnter() {}
		virtual void OnStateExit() {}
		virtual void OnStateUpdate(float delta) {}
	};

	export class StateMachine
	{
	public:

		StateMachine& RegisterState(int id, State* state)
		{
			states[id] = state;
			return *this;
		}

		StateMachine& ActivateState(int id)
		{
			if (states.contains(id))
			{
				if (currentState != nullptr)
					currentState->OnStateExit();
				currentState = states[id];
				currentState->OnStateEnter();
			}
			return *this;
		}

		StateMachine& Update(float delta)
		{
			if (currentState != nullptr)
				currentState->OnStateUpdate(delta);
			return *this;
		}

	private:

		std::map<int, State*> states;
		State* currentState = nullptr;
	};
}