#pragma once

#include "State.hpp"
#include <iostream>
#include <stack>
#include <cassert>

class State;

class StateManager {
private:
    std::stack<std::unique_ptr<State>> _states;
    std::unique_ptr<State> _newState;
    bool _isAdding = false;
    bool _isRemoving = false;
    bool _isReplacing = false;
public:
    StateManager();
    ~StateManager();

    bool isEmpty() const;
    void addState(std::unique_ptr<State> newState, bool isReplacing);
    void popState();
    void changeState();
    State* peekState();
};