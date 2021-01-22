#pragma once

#include <memory>
#include <stack>

#include "State.h"

using namespace std;

namespace Ass02_pong
{
	typedef std::unique_ptr<State> StateRef;

	class StateMachine
	{
	public:
		StateMachine() {}
		~StateMachine() {}

		void AddState(StateRef newSate, bool isReplacing = true);
		void RemoveSate();

		void ProcessStateChanges();

		StateRef& GetActiveSate();

	private:
		std::stack<StateRef> _states;
		StateRef _newState;

		bool _isRemoving;
		bool _isAdding;
		bool _isReplacing;
	};
}