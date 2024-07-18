#pragma once
#include <State.h>
#include <memory>
#include <map>

class StateMachine
{
public:
    StateMachine() = default;

    void ChangeState(StateID stateID)
    {
        #ifdef _BUILD_DEBUG
                DEBUG_ASSERT(states.count(stateID) != 0, "STATE DOES NOT EXIST");
        #endif
        if(currentState != nullptr)
        {
            currentState->OnStateExit();
        }

        currentState = states[stateID].get();
        currentState->OnStateEnter();
    }

    void AddState(std::unique_ptr<State> state)
    {
        #ifdef _BUILD_DEBUG
            DEBUG_ASSERT(states.count(state->GetStateID()) == 0, "DUPLICATE STATE ADDED");
        #endif

        states[state->GetStateID()] = std::move(state);
    }

    void Update()
    {
        if(currentState != nullptr)
        {
            currentState->OnStateUpdate();
        }

        StateID nextState = currentState->GetNextState();
        if(nextState != currentState->GetStateID())
        {
            ChangeState(nextState);
        }
    }

private:
    State* currentState;
    std::map<int, std::unique_ptr<State>> states;
};