#include "StateManager.hpp"

StateManager::StateManager() {}

StateManager::~StateManager() {}

bool StateManager::isEmpty() const
{
    return this->_states.empty();
}

void StateManager::addState(std::unique_ptr<State> newState, bool isReplacing)
{
    this->_isAdding = true;
    this->_isReplacing = isReplacing;
    this->_newState = std::move(newState);
}

void StateManager::popState()
{
    this->_isRemoving = true;
}

void StateManager::changeState()
{
    if (this->_isRemoving && !this->_states.empty())
    {
        this->_states.pop();

        if (!this->_states.empty())
        {
            this->_states.top()->resume();
        }

        this->_isRemoving = false;
    }

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
                this->_states.top()->pause();
            }
        }

        this->_states.push(std::move(this->_newState));
        this->_states.top()->init();
        this->_isAdding = false;
    }
}

State* StateManager::peekState()
{
    if (_states.empty())
    {
        return nullptr;
    }

    return this->_states.top().get();
}