#include "StateMachine.h"

using namespace std;

namespace Ass02_pong
{
	void StateMachine::AddState(StateRef newState, bool isReplacing)
	{
		this->_isAdding = true;
		this->_isReplacing = isReplacing;

		this->_newState = std::move(newState);
	}

	void StateMachine::RemoveSate()
	{
		this->_isRemoving = true;
	}

	void StateMachine::ProcessStateChanges()
	{
		// Remove state
		if (this->_isRemoving && !this->_states.empty())
		{
			this->_states.pop();
			if (!this->_states.empty())
			{
				this->_states.top()->Resume();
			}
			this->_isRemoving = false;
		}
		// Add state
		if (this->_isAdding)
		{
			if (!this->_states.empty())
			{
				if (this->_isReplacing)
				{
					this->_states.pop();
				}
				else
				{
					this->_states.top()->Pause();
				}
			}
			this->_states.push(std::move(this->_newState));
			this->_states.top()->Init();
			this->_isAdding = false;
		}
	}

	StateRef& StateMachine::GetActiveSate()
	{
		return this->_states.top();
	}
}