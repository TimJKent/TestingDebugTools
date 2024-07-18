#pragma once
#include <cstdint>

typedef std::uint32_t StateID;

class State
{
    public:
    State(StateID id);
    ~State();

        virtual void OnStateEnter ();
        virtual void OnStateUpdate();
        virtual void OnStateExit  ();
        virtual StateID GetNextState () = 0;

        const StateID GetStateID() const;
    protected:
        StateID stateID;
};